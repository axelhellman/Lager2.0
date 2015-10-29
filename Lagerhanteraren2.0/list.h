
#ifndef LIST_H
#define LIST_H

#include "tree.h"

typedef struct list_s list;
typedef struct linked_list_node_s linked_list_node;
typedef struct shelf_s shelf;

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

int get_amount(node* node);

char* get_shelf_name1(shelf* s);
//char* get_shelf_name2(linked_list_node *crnt_ll_node);

int get_shelf_amount1(shelf* s);
//int get_shelf_amount2(linked_list_node *crnt_ll_node);

linked_list_node* get_first(list* l);
shelf* get_shelf(node* n, char* shelf_name);

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

list* create_new_list(int total, linked_list_node* ll_node);
linked_list_node* create_new_ll(); 
shelf* create_new_shelf(char* shelf_name, int amount);

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

bool list_is_empty(node* n);

void add_shelf(node* node, char* shelf_name, int amount);
void remove_shelf(node* n, shelf* s);

node* add_amount(node* n, int amount);
node* remove_amount(node* n, int amount);

bool shelf_is_taken_list(list* list, char* shelf_name);
bool shelf_is_taken(node* node, char* shelf_name);

void print_check_out(root* root, node* n);
void shelf_names(linked_list_node *crnt_ll_node);

void destroy_list(list* l);

#endif /* LIST_H */
