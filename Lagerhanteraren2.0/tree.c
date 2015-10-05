#include "tree.h"


struct tree_s
{
  node *top_node; //tree är top-node
  //  cart *cart;
};

struct node_s
{
  struct ware_s
  {
    char* name;
    char* description;
    int price;

    list *list;
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
/*
struct cart_s
{
  struct item_s
  {
    char* name;
    int* price;
    int* amount;
    int* total_price;
  }item;

  cart_s *next_cart;
  
  }; */

char * get_name(node *node)
{
  return (node -> ware.name);
}


node * create_new_node(char* name, char* description, int price, char* shelf_name, int amount)
{
  node *node = calloc(1, sizeof(node));
  assert(node != NULL);

  node -> left_node = NULL;
  node -> right_node = NULL;
  
  node -> ware.name = name; // (*ware).name
  node -> ware.description = description;
  node -> ware.price = price; //ska det va punkt här istället för pil?
  
  list *list = calloc(1, sizeof(list));
  assert(list != NULL);

  node -> ware.list -> total_amount = amount;
  node -> ware.list = list;
  
  shelf_node *shelf_node = calloc(1, sizeof(shelf_node));
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
      return find_node(node -> left_node, name);
    }
    
  return NULL;
}


void update_node()
{
  puts("hej");
}

void insert_or_update(tree* tree, char* name, char* description, int price, char* shelf_name, int amount)
{
  if (find_node(tree -> top_node, name) == NULL)
    {
      insert_new_node(tree, name, description, price, shelf_name, amount);
    }
  else // find_node == any node
    {
      update_node();
    }
}

void insert_new_node(tree * tree, char* name, char* description, int price, char* shelf_name, int amount) // TODO: ta med trädet?
{
node* new_node = create_new_node(name, description, price, shelf_name, amount);
// char* name = get_name(new_node);
  if (tree_is_empty(tree))
    {
      tree -> top_node = new_node;
      return;
    }
  
  while (true)
    {
      node* crnt_node = tree -> top_node;
      char* crnt_node_name = get_name(crnt_node);  

      if (strcmp(name, crnt_node_name) > 0)
	{
	  if (crnt_node -> right_node != NULL)
	    {
	      crnt_node = crnt_node -> right_node;
	      continue;
	    }
	  crnt_node -> right_node = new_node;
	  return;
	}
      else if (strcmp(name, crnt_node_name) < 0)
	{
	  if (crnt_node -> left_node != NULL)
	    {
	      crnt_node = crnt_node -> left_node;
	      continue;
	    }
	  crnt_node -> left_node = new_node;
	  return;
	} 
    }
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
  tree *tree = calloc(1, sizeof(tree));
  tree -> top_node = NULL;
  return (tree);
}


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
   tree *tree = create_new_tree();
   printf("hej igen");
   //insert_new_node(tree, "Gurka", "Grön och skön", 12, "A23", 2);
 }
