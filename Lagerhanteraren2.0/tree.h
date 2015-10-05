#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// #DEFINE ARGS_WARE (char* name, char* description, int price, char* shelf_name, int amount)

typedef struct tree_s tree;
typedef struct node_s node;
typedef struct list_s list;
typedef struct shelf_node_s shelf_node;
//typedef struct cart_s cart;

node * create_new_node(char* name, char* description, int price, char* shelf_name, int amount);

void destroy_tree(node* node); //argument?

// skickar in ett namn på en vara och trädet. Returnerar true om varan redan finns. Annars returernar den false
bool existing_node(node* node, char* name);

void insert_new_node(tree * tree, char* name, char* description, int price, char* shelf_name, int amount);
  
bool tree_is_empty(tree* tree);
  
