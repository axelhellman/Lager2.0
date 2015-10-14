#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


#ifndef TREE_H
#define TREE_H

#define TreeRoot get_root(tree)
#define ArgsWare char* name, char* description, int price, char* shelf_name, int amount
#define N_Content_eq_Ware ware* ware = node -> n_content
#define printAll print_tree(TreeRoot, 0, 0 ,0)

typedef struct tree_root_s tree_root;
typedef struct node_s node;
typedef struct ware_s ware;
typedef struct list_s list;
typedef struct linked_list_node_s linked_list_node;
typedef struct shelf_s shelf;
typedef struct cart_item_s cart_item;


node * create_new_node(ArgsWare);

void destroy_tree(tree_root* tree); //argument?

// skickar in ett namn på en vara och trädet. Returnerar true om varan redan finns. Annars returernar den false
bool node_exists(tree_root* tree, char* name);

void insert_new_node(tree_root* tree, node* node);
  
bool tree_is_empty(tree_root* tree);

void insert_or_update(tree_root* tree, ArgsWare);
  
node * find_node(node* node, char* name);

tree_root * create_new_tree();

char * get_name(node *node);
char * get_description(node *node);
int get_price(node *node);
char * get_shelf_name(node *node);
int get_amount(node *node);
node* get_root(tree_root *tree);
list *get_list (node * n);

bool shelf_is_taken(node* node, char* shelf_name);
void print_shelfs(linked_list_node * ll_node);
linked_list_node* get_ll_node(list* l);
void printtest(node* n);
void remove_node(tree_root *tree, node* n);
int print_tree(node *n, int i, int low, int high);
void print_line();
void print_warehouse(tree_root *tree, int i, int low, int high);
int total_items(node* n, int i);

#endif /* TREE_H */
