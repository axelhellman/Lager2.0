#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "tree.h"


#ifndef SMALLFUNC_H 
#define SMALLFUNC_H

#define AskName ask_str_q("Name:")

node * ask_item(tree_root *tree); 

//int ask_index(warehouse* warehouse_list, int page);

char* ask_str_q (char *question);

int ask_int_q (char *question, int low, int high);

bool ask_yn(char* question);

char ask_alt(char* question, char* alternatives);

void print_line(void);

//char* ask_name();

char* ask_description();

int ask_price();

char* ask_shelf_name(tree_root *tree, node* n);

void* ask_shelf(tree_root* tree, node* n);

int ask_amount();



#endif /* SMALLFUNC_H */
