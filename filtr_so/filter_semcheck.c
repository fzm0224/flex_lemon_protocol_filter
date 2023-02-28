#include "filter_semcheck.h"

gboolean semcheck(dfwork_t *dfw, stnode_t *st_node);

test_op_t flip_op(test_op_t op)
{
    switch(op) {
        case TEST_OP_EQ:
            return TEST_OP_EQ;
        case TEST_OP_NE:
            return TEST_OP_NE;
        case TEST_OP_CONTAINS:
            return TEST_OP_CONTAINS;
        case TEST_OP_GT:
            return TEST_OP_LT;
        case TEST_OP_GE:
            return TEST_OP_LE;
        case TEST_OP_LT:
            return TEST_OP_GT;
        case TEST_OP_LE:
            return TEST_OP_GE;
        default:
            g_assert_not_reached();
            break;
    }

    return op;
}

gboolean check_proto_value(stnode_t *keynode, stnode_t *valuenode)
{
    proto_value_t pv;
    char* proto_name = stnode_data(keynode);

    if(proto_type_getbyname(proto_name, &pv) == TRUE) {
        sttype_id_t tp = stnode_type_id(valuenode);
        switch(pv) {
            case PROTO_VALUE_STRING:
                return ((tp == STTYPE_STRING)
                        || (tp == STTYPE_UNPARSED)
                        || (tp == STTYPE_FVALUE));
            case PROTO_VALUE_INTEGER:
                return tp == STTYPE_INTEGER;
            default:
                break;
        }
    }

    return FALSE;
}

/* exchange st_arg1 st_arg2 of st_node if st_arg2 is FIELD*/
gboolean check_relation(dfwork_t *dfw, test_op_t st_op, stnode_t *st_node, stnode_t *st_arg1, stnode_t *st_arg2)
{
    gboolean ret = FALSE;

    if((stnode_type_id(st_arg1) == STTYPE_FIELD)
        && (stnode_type_id(st_arg2) != STTYPE_FIELD)) {
        ret = check_proto_value(st_arg1, st_arg2);
    } else if((stnode_type_id(st_arg1) != STTYPE_FIELD)
            && (stnode_type_id(st_arg2) == STTYPE_FIELD)) {
        if(check_proto_value(st_arg2, st_arg1) == TRUE) {
            test_op_t exOp;
            exOp = flip_op(st_op);
            sttype_test_set2(st_node, exOp, st_arg2, st_arg1);
            ret = TRUE;
        }
    } else {
        ret = FALSE;
    }

    return ret;
}

gboolean check_test(dfwork_t *dfw, stnode_t *st_node)
{
    test_op_t st_op, stArgOp;
	stnode_t *st_arg1, *st_arg2;
    gboolean ret = FALSE;

    sttype_test_get(st_node, &st_op, &st_arg1, &st_arg2);

    switch(st_op) {
        case TEST_OP_AND:
        case TEST_OP_OR:
            if(semcheck(dfw, st_arg1) == TRUE) {
                ret = semcheck(dfw, st_arg2);
            }
            break;
        case TEST_OP_EQ:
        case TEST_OP_NE:
        case TEST_OP_GT:
        case TEST_OP_GE:
        case TEST_OP_LT:
        case TEST_OP_LE:
        case TEST_OP_CONTAINS:
            ret = check_relation(dfw, st_op, st_node, st_arg1, st_arg2);
            break;
        case TEST_OP_NOT:
            ret = semcheck(dfw, st_arg1);
            break;
        case TEST_OP_EXISTS:
            ret = TRUE;
            break;
        default:
            g_assert_not_reached();
            break;
    }

    return ret;
}

gboolean semcheck(dfwork_t *dfw, stnode_t *st_node)
{
    gboolean ret = FALSE;

    switch(stnode_type_id(st_node)) {
        case STTYPE_TEST:
            ret = check_test(dfw, st_node);
            break;
        default:
            break;
    }

    return ret;
}

gboolean dfw_semcheck(dfwork_t *dfw)
{
    return semcheck(dfw, dfw->st_root);
}

