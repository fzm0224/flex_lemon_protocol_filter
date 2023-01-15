/*
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 2001 Gerald Combs
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef STTYPE_TEST_H
#define STTYPE_TEST_H

#include "libfilter.h"
#include "filter_gstring.h"
#include "filter_syntax_tree.h"


gpointer test_new(gpointer junk);
gpointer test_dup(gconstpointer data);
void test_free(gpointer value);
int num_operands(test_op_t op);
char* operandname(test_op_t op);

void sttype_test_set1(stnode_t *node, test_op_t op, stnode_t *val1);
void sttype_test_set2(stnode_t *node, test_op_t op, stnode_t *val1, stnode_t *val2);
void sttype_test_set2_args(stnode_t *node, stnode_t *val1, stnode_t *val2);
void sttype_test_get(stnode_t *node, test_op_t *p_op, stnode_t **p_val1, stnode_t **p_val2);


#endif
