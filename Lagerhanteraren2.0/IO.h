#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "tree.h"
#include "smallfunc.h"
#include "list.h"

#ifndef IO_H 
#define IO_H

#define ItemsPerPage 20


void add_ware_IO(root* root);

void remove_item_IO(root* root);

void edit_item_IO(root* root);

void show_warehouse_IO(root* root, tree_root * tree);

void add_item_to_cart_IO(root* root);

bool exit_warehouse();

#endif /* IO_H */

