#include "list.h"
#ifndef TREE_H
#define TREE_H

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


#define Warehouse get_warehouse(root)
#define Cart get_cart(root)
#define Top(tree) get_topnode(tree)

#define printWarehouse() print_tree(root, Warehouse, 0 ,0)
#define printCart() print_tree(root, Cart, 0, 0)
#define WithNumbers true
#define WithoutNumbers false

#define ArgsWare char* name, char* description, int price, char* shelf_name, int amount

//---------------------------------------------------
//---------------------------------------------------

typedef struct root_s root;
typedef struct tree_root_s tree_root;
typedef struct node_s node;
typedef struct ware_s ware;
typedef struct cart_item_s cart_item;

//---------------------------------------------------
//---------------------------------------------------

tree_root* get_warehouse(root* root);
tree_root* get_cart(root* root);

node* get_topnode(tree_root *tree);
node* getLeft(node* node);
node* getRight(node* node);

char * get_key(node *node);
char * get_description(node *node);
int get_price(node *node);
void* get_list(node * n);
int get_cart_amount(node* node);

//---------------------------------------------------
//---------------------------------------------------

node* create_new_cart_item(node* item, int amount);
root* create_new_root();

void change_name(root *root, node *n, char *new_name);
void change_description(node* n, char* new_description);
void change_price(root* root, node* n, int new_price);
void change_cart_amount(node* cart_node, int add_amount);

bool tree_is_empty(tree_root* tree);

node* find_node(node* node, char* name);
bool node_exists(tree_root* tree, char* name);

void insert_new_ware(tree_root* tree, ArgsWare);
void insert_node(tree_root* tree, node* node);

void update_cart_amount(root* root, char* name, int limit);

void remove_node(root *root, node* n);
void check_out_cart(root* root);

int total_price(node* n, int total);
int total_items(node* n, int i);
void print_tree(root* root, tree_root* tree, int low, int high);

void destroy_nodes_aux(root* root, tree_root* tree, node* n);
void destroy_nodes(root* root, tree_root* tree, node* n);
void destroy_tree(root* root, tree_root* tree);
void destroy_all(root* root);

#endif /* TREE_H */
