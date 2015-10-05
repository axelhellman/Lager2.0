#include "tree.h"
#include <assert.h>


struct tree_s
{
  node *top_node; //tree är top-node
};

struct node_s
{
  struct ware_s
  {
    char* name;
    char* description;
    int price;

    list *shelf_list;
  } ware;

  node *left_node;
  node *right_node; 
};


struct list_s
{
  int total_amount;
  shelf_node *first;
  shelf_node *last;
};

struct shelf_node_s
{
  char* shelf_name;
  int amount;
  shelf_node *next_shelf;
};

char * get_name(node *node)
{
  return (node.ware -> name);
}

#DEFINE ARGS_WARE char* name, char* description, int price, char*shelf_name, int amount

node * create_new_node(ARGS_WARE) // TODO: void? 
{
  node *node = (node*) calloc(1, sizeof(node));
  assert(node != NULL);

  node -> left_node = NULL;
  node -> right_node = NULL;
  
  node -> ware.name = name; // (*ware).name
  node -> ware.description = description;
  node -> ware.price = price; //ska det va punkt här istället för pil?
  
  list *list = (list*) calloc(1, sizeof(list));
  assert(list != NULL);

  total_amount = amount;
  node -> ware.list = list;
  
  shelf_node *shelf_node = (shelf_node*) calloc(1, sizeof(shelf_node));
  assert(shelf_node != NULL);
  
  list -> first = shelf_node;
  list -> last = shelf_node;
  
  shelf_node -> shelf_name = shelf_name;
  shelf_node -> amount = amount;
  shelf_node -> next_shelf = NULL;
  
  return node;
}

node* find_node(node* node, char* name)
{
  char* crnt_node_name = get_name(node);

  if (strcmp(name, crnt_node_name) == 0)
    {
      return node;
    }
  else if (strcmp(name, crnt_node_name) > 0)
    {
      return find_node(node -> right_node, name);
    }
  else //(strcmp(name, crnt_node_name) < 0)
    {
      return find_node( node -> left_node, name);
    }
    
  return NULL;
}

void insert_or_update(tree* tree, WARE_ARGS)
{
  if (find_node(tree -> top_node, WARE_ARGS) == NULL)
    {
      insert_new_node(tree, WARE_ARGS);
    }
  else // find_node == node
    {
      update_node;
    }
}

void update_node()
{
  puts"hej";
}

node * find_place_to_insert(tree* tree, char *name) // TODO: ta med trädet?
{
  
  char* crnt_node_name = get_name(node);  
  if (strcmp(name, crnt_node_name) > 0)
    {
      return find_node(node -> right_node, name);
    }
  else (strcmp(name, crnt_node_name) < 0)
    {
      return find_node( node -> left_node, name);
    } 
  
}

void insert_new_node(tree* tree, WARE_ARGS) //TODO ta med trädet?
{
  node* parent = find_place_to_insert(tree, name); //parent??
  parent -> left_node = create_new_node(WARE_ARGS); //fel pekare
  char* name = get_name(new_node);
  
  
}


bool tree_is_empty(tree *tree)
{
  if (tree -> top_node == NULL)
    {
      return true;
    }
  else
    {
      return false;
    }
}

tree* create_new_tree()
{
  tree *tree = (tree*) calloc(1, sizeof(tree));
  tree -> top_node = NULL;
  return (tree);
}






/*
// TOBIAS KOD FRÅN FÖRELÄSNINGEN

void tree_insert(tree_t *node, int value)
{
  if (t->root)
    {
      node_insert(t->root, value);
    }
  else
    {
      t->root = node_new(value, NULL, NULL);
    }
}

void node_insert(node_t *node, int value)
{
  if (node->value == value)
    {
      // This not is already in the tree -- what to do? (application-specific)
    }
  else
  if (node->value < value)
    {
      if (node->right)
        {
          node_insert(node->right, value);
        }
      else
        {
          node->right = node_new(value, NULL, NULL);
        }
    }
  else
    {
      if (node->left)
        {
          node_insert(node->left, value);
        }
      else
        {
          node->left = node_new(value, NULL, NULL);
        }
    }
}
*/

 void tree_print(node *n) 
 {
   if(n)
     {
       tree_print (n->left_node);
       printf("%s ", n->ware.name); //TODO kanske
       tree_print (n->right_node);
     }
 }



 
 int main (void)
 {
   printf("Hej hej");
 }
