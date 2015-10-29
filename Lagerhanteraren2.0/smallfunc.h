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


node* ask_item(tree_root *tree); 
char* ask_description(node* n);
int ask_price(node* n);
void* ask_shelf(tree_root* tree, node* n);
char* ask_shelf_name(tree_root *tree, node* n);
int ask_amount();


char* ask_str_q (char* question);
int ask_int_q (char* question, int low, int high);
bool ask_yn(char* question);
char ask_alt(char* question, char* alternatives);


void print_line(void);
void print_box(node* node, bool numbers);
void print_name(node *node, bool number);
void print_description(node *node, bool number);	    
void print_price(node *node, bool number);
void print_shelf_names(node *node, bool number);
void print_amount(node *node, bool number);


#endif /* SMALLFUNC_H */
