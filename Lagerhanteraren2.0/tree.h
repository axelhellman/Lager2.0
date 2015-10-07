#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef TREE_H
#define TREE_H

typedef struct tree_root_s tree_root;
typedef struct node_s node;
typedef struct list_s list;
typedef struct shelf_node_s shelf_node;

//typedef struct cart_s cart;

// #DEFINE ARGS_WARE (char* name, char* description, int price, char* shelf_name, int amount)

void print_tree(node* node);

node * create_new_node(char* name, char* description, int price, char* shelf_name, int amount);

void destroy_tree(node* node); //argument?

// skickar in ett namn på en vara och trädet. Returnerar true om varan redan finns. Annars returernar den false
bool node_exists(tree_root* tree, char* name);

void insert_new_node(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount);
  
bool tree_is_empty(tree_root* tree);

void insert_or_update(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount);
  
node * find_node(node* node, char* name);

char * get_name(node *node);
char * get_description(node *node);
int get_price(node *node);
char * get_shelf_name(node *node);
int get_amount(node *node);

#endif /* TREE_H */