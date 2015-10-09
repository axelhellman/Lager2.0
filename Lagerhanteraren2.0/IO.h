#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "tree.h"
#include "smallfunc.h"

#ifndef IO_H 
#define IO_H


//funktioner som menu kallar på

void add_ware_IO(tree_root * tree);

void remove_shelf_IO(tree_root * tree);

void add_item_to_cart_IO();


void edit_shelf_IO(tree_root * tree);
/*
void undo_action_IO(warehouse * warehouse_list); */

bool exit_warehouse();

int ask_int_q(char* question, int low, int high);

//void print_warehouse(warehouse *warehouse_list);


#endif /* IO_H */

