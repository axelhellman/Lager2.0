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

#define ItemsPerPage 8

//funktioner som menu kallar på
 

void add_ware_IO(root* root);

void remove_item_IO(root* root);

void add_item_to_cart_IO(root* root);


void edit_item_IO(root* root);
/*
void undo_action_IO(warehouse * warehouse_list); */

bool exit_warehouse();

int ask_int_q(char* question, int low, int high);

void show_warehouse_IO(root* root, tree_root * tree);

void print_shelf_names(node *node, bool numbers);
#endif /* IO_H */

