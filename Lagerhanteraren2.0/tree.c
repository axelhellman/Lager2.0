#include "tree.h"


struct tree_root_s
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
char * get_description(node *node)
{
  return (node -> ware.description);
}
int get_price(node *node)
{
  return (node -> ware.price);
}
char * get_shelf_name(node *node)
{
  return (node -> ware.list -> first -> shelf_name);
}
int get_amount(node *node)
{
  return (node -> ware.list -> total_amount);
}
node* get_root(tree_root *tree)
{
  return (tree -> top_node);
}

node * create_new_node(char* name, char* description, int price, char* shelf_name, int amount)
{
  node *node = calloc(1, sizeof(struct node_s));
  assert(node != NULL);

  node -> left_node = NULL;
  node -> right_node = NULL;
  
  node -> ware.name = name; // (*ware).name
  node -> ware.description = description;
  node -> ware.price = price; //ska det va punkt här istället för pil?
  
  list *list = calloc(1, sizeof(struct list_s));
  assert(list != NULL);

  node -> ware.list = list;
  node -> ware.list -> total_amount = amount;
  
  shelf_node *shelf_node = calloc(1, sizeof(struct shelf_node_s));
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
  if (node == NULL) return NULL;
  
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

void remove_node(node* node, char* name)
{
  puts("TODO");
}


bool node_exists(tree_root* tree, char* name)
{
  if (find_node(tree -> top_node, name) != NULL) return true;
  return false;
}

void update_node(node* node, char* shelf_name, int amount)
{
  puts("hej");
}

void insert_or_update(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount)
{
  node * node = find_node(tree -> top_node, name);
  if (node == NULL)
    {
      insert_new_node(tree, name, description, price, shelf_name, amount);
      return;
    }
  else // find_node == any node
    {
      update_node(node, shelf_name, amount);
      return;
    }
}


void insert_new_node(tree_root * tree, char* name, char* description, int price, char* shelf_name, int amount) // TODO: ta med trädet?
{
  node* new_node = create_new_node(name, description, price, shelf_name, amount);
  print_tree(new_node);
  
  if (tree_is_empty(tree))
    {
      tree -> top_node = new_node;
      return;
    }
  node* crnt_node = tree -> top_node;

  while (true)
    {
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


bool tree_is_empty(tree_root *tree)
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

tree_root* create_new_tree()
{
  tree_root *tree_root = calloc(1, sizeof(struct tree_root_s));
  tree_root -> top_node = NULL;
  return (tree_root);
}


void print_tree(node *n) 
 { 
   if(n)
     {
       print_tree (n->left_node);
       printf("-%s\n", n->ware.name); //TODO kanske
       print_tree (n->right_node);
      
     }
 }

/*
 int main (void)
 {
   printf("Hej hej");
   print_tree(tree -> top_node);
   printf("hej igen");
   insert_or_update(tree, "Gurka", "Grön och skön", 12, "A23", 2);
   
 }
*/







// remove node
// 
