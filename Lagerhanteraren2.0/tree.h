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

typedef struct tree_root_s tree_root;
typedef struct node_s node;
typedef struct ware_s ware;
typedef struct list_s list;
typedef struct linked_list_node_s linked_list_node;
typedef struct shelf_s shelf;

//typedef struct cart_s cart;

// #DEFINE ARGS_WARE (char* name, char* description, int price, char* shelf_name, int amount)

void print_tree(node* node);

node * create_new_node(ArgsWare;

void destroy_tree(node* node); //argument?

// skickar in ett namn på en vara och trädet. Returnerar true om varan redan finns. Annars returernar den false
bool node_exists(tree_root* tree, char* name);

void insert_new_node(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount);
  
bool tree_is_empty(tree_root* tree);

void insert_or_update(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount);
  
node * find_node(node* node, char* name);

tree_root * create_new_tree();

char * get_name(node *node);
char * get_description(node *node);
int get_price(node *node);
char * get_shelf_name(node *node);
int get_amount(node *node);
node* get_root(tree_root *tree);

#endif /* TREE_H */
