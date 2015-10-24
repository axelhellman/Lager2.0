
#ifndef LIST_H
#define LIST_H

#include "tree.h"

typedef struct list_s list;
typedef struct linked_list_node_s linked_list_node;
typedef struct shelf_s shelf;

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------


//char * get_shelf_name(node *node)
int get_amount(node* node);
char* get_shelf_name2(linked_list_node *crnt_ll_node);
int get_shelf_amount(linked_list_node *crnt_ll_node);
linked_list_node* get_first(list* l);
shelf* get_shelf(node* n, char* shelf_name);
void change_shelf_name(node* n, shelf* shelf, char* newname);

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

list* create_new_list(int total, linked_list_node* ll_node);
linked_list_node* create_new_ll(); 
shelf* create_new_shelf(char* shelf_name, int amount);

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------


void insert_shelf(list *list, shelf *new_shelf);

void add_shelf(node* node, char* shelf_name, int amount);


bool node_has_shelf(node* node, char* shelf_name);
bool shelf_is_taken_list(list* list, char* shelf_name);
bool shelf_is_taken(node* node, char* shelf_name);
void shelf_names(linked_list_node *crnt_ll_node);
void print_shelfs(linked_list_node *crnt_ll_node);

#endif /* LIST_H */
