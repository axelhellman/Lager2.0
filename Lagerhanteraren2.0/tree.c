#include "tree.h"
#ifdef LIST_H
#include "list.h"
#endif /* LIST_H */


node* separate_node(tree_root *tree, node* rn);
int print_tree_aux(node* n, int i, int low, int high);

struct root_s
{
  tree_root* warehouse;
  tree_root* cart;
};

struct tree_root_s
{
  node *top_node; //tree är top-node
};

typedef void(*destructor)(void*);

struct node_s
{
  char* key;
  void *n_content;
  node *left_node;
  node *right_node;
  // destructor free_content;
};

struct ware_s
{
  char* name;
  char* description;
  int price;
  list *list;
};

struct cart_item_s
{
  char* name; //behövs egentligen inte
  int price; //behövs inte
  int amount;
  int total_price;
};
//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

tree_root* get_warehouse(root* root)
{
  return (root -> warehouse);
}
tree_root* get_cart(root* root)
{
  return (root -> cart);
}
node* get_topnode(tree_root* tree)
{
  return (tree -> top_node);
}
//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

node* getLeft(node* node)
{
  return (node -> left_node);
}

node* getRight(node* node)
{
  return (node -> right_node);
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

char * get_name(node *node)
{
  return (node -> key);
}
char * get_description(node *node)
{
  return (((ware*) node -> n_content) -> description);
}
int get_price(node *node) //endast wh
{
  return (((ware*) node -> n_content) -> price);
}

void* get_list(node* n) //endast wh
{
  return (((ware*)n -> n_content) -> list);
}
//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------



ware* create_new_ware(char* name, char* description, int price)
{
  ware* ware = calloc(1, sizeof(struct ware_s));
  assert (ware != NULL);

  ware -> name = name;
  ware -> description = description;
  ware -> price = price;
  return ware;
}


// gör en funktion som heter Create_new_content
node * create_new_node(char* name, char* description, int price, char* shelf_name, int amount)
{
  node *node = calloc(1, sizeof(struct node_s));
  assert(node != NULL);
  node -> key = name;

  ware* ware = create_new_ware(name, description, price);
  node -> n_content = ware;

  shelf * shelf = create_new_shelf(shelf_name, amount);
  linked_list_node * ll_node = create_new_ll(shelf);
  list* list = create_new_list(amount, ll_node); //lägg till &destroy_shelf

  ware -> list = list;
 
  return node;
}

tree_root* create_new_tree()
{
  tree_root* tree = calloc(1, sizeof(struct tree_root_s));
  tree -> top_node = NULL;
  return tree;
}

root* create_new_root()
{
  root * r = calloc(1, sizeof(struct root_s));
  assert(r != NULL);
  tree_root* w = create_new_tree();
  tree_root* c = create_new_tree();
  r -> warehouse = w;
  r -> cart = c;
  return r;
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

void change_name(root* root, node* n, char* new_name)
{
  char* old_name = get_name(n);
  n = separate_node(Warehouse, n);
  n -> key = new_name;
  ((ware*) n -> n_content) -> name = n -> key;
  insert_node(Warehouse, n);

  if (node_exists(Cart, old_name))
    {
      node* tmp_node_cart = separate_node(Cart, n);
      tmp_node_cart -> key = new_name;
      ((cart_item*) tmp_node_cart -> n_content) -> name = tmp_node_cart -> key;
      insert_node(Cart, tmp_node_cart);
    }
  print_tree_aux(Top(Warehouse), 0,0,0);
  return;
}

void change_description(node* n, char* new_description)
{
  ((ware*)n -> n_content) -> description = new_description;
}

void change_price(root* root, node* n, int new_price)
{
  ((ware*)n -> n_content) -> price = new_price;
  if (node_exists(Cart, get_name(n)))
    {
      ((cart_item*)n -> n_content) -> price = new_price;
      //((cart_item*)n -> n_content) -> total_price = ; uppdatera total pris
    }
}


//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

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
    
  //return NULL;
}


bool node_exists(tree_root* tree, char* name)
{
  if (find_node(Top(tree), name) != NULL) return true;
  return false;
}

void insert_new_node(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount)
{
  node * node = find_node(Top(tree), name);
  if (node == NULL)
    {
      node = create_new_node(name, description, price, shelf_name, amount);
      insert_node(tree, node);
      return;
    }
  else // find_node == any node
    {
      add_shelf(node, shelf_name, amount); //ska det va såhär
      return;
    }
}


void insert_node(tree_root* tree, node* new_node)
{  
  if (tree_is_empty(tree))
    {
      tree -> top_node = new_node;
      return;
    }
  node* crnt_node = tree -> top_node;
  char* name = get_name(new_node);

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
      else if (strcmp(name, crnt_node_name) == 0)
	{
	  puts("Trying to insert an already existing item");
	  return;
	}
    }
}


bool node_is_leaf(node* n)
{
  if (n->right_node == NULL && n->left_node == NULL) return true;
  else return false;
}

bool tree_is_empty(tree_root *tree)
{
  if (tree -> top_node == NULL) return true;
  else return false;
}


node* find_prev_node(tree_root* tree, node* n, char* name)
{
  node* tmp_node = find_node(Top(tree), name);
  if (n == NULL) return NULL;
  char* crnt_node_name = get_name(n);
  
  
  if (n -> right_node == tmp_node) return n;
  if (n -> left_node == tmp_node) return n;

  if (strcmp(name, crnt_node_name) > 0)
    {
      return find_prev_node(tree, n -> right_node, name);
    }
  else if (strcmp(name, crnt_node_name) < 0)
    {
      return find_prev_node(tree, n -> left_node, name); 
    }
  else
    {
      puts("else i find_prev_node");
      return NULL;
    }
}


node* child(node* n)
{
  if (n -> left_node == NULL && n -> right_node != NULL) return (n -> right_node);
  else if (n -> right_node == NULL && n -> left_node != NULL) return (n -> left_node);
  else return NULL;
}

void connect_child(node* prev_node, node* n, node* child)
{
   if (prev_node -> right_node == n) prev_node -> right_node = child;

   else prev_node -> left_node = child;

   n -> right_node = NULL;
   n -> left_node = NULL;
   return;
}

void re_insert_nodes(tree_root* tree, tree_root* tmp_tree)
{ 
  if (tmp_tree == NULL) return;

  insert_node(tree, tmp_tree -> top_node -> left_node);
  insert_node(tree, tmp_tree -> top_node -> right_node);
}

void remove_node(root* root, node* n)
{
  n = separate_node(Warehouse, n);
  if (node_exists(Cart, get_name(n)))
    {
      node* tmp_node_cart = separate_node(Cart, n);
      //destroy_node(tmp_node_cart);
    }
  printf("destroys node (%s) soon\n", get_name(n));
  //destroy_node(n);

}

node* separate_node(tree_root* tree, node* rn)
{
  bool leaf = node_is_leaf(rn);
  node* prev_node = find_prev_node(tree, Top(tree), get_name(rn));
  
  if (leaf)
    {
      if(Top(tree) == rn) tree -> top_node = NULL;
      if (prev_node -> right_node == rn) prev_node -> right_node = NULL; 
      if (prev_node -> left_node == rn) prev_node -> left_node = NULL;
    }
  else if (child(rn)) //node has one child
    {
      if (Top(tree) == rn) tree -> top_node  = child(rn);
      else connect_child(prev_node, rn, child(rn));
    }
  else //node has two_children
    {
      tree_root* tmp_tree = create_new_tree();
      tmp_tree -> top_node = rn;

      if (Top(tree) == rn) tree -> top_node = NULL;	
      else
	{
	  if (prev_node -> right_node == rn) prev_node -> right_node = NULL;
	  else prev_node -> left_node = NULL;
	}
      
      re_insert_nodes(tree, tmp_tree);
      rn -> right_node = NULL;
      rn -> left_node = NULL;
      tmp_tree -> top_node = NULL;
      //destroy tmp_tree
    }
  print_line();
  return rn;
}






/*
-----------------------------------------------------------------------
-----------------------------------------------------------------------
-------------- D E S T R O Y ------------------------------------------
-----------------------------------------------------------------------
-----------------------------------------------------------------------
 */

/*

void destroy_cart_item(void * ci)
{
  free(ci);
}
  



void destroy_cart(cart* c)
{
  destroy_cart_item(cart_item* ci);
  destroy_list(list* l);
}

void destroy_tree(tree_root* tree)
{

  destroy_shelf(shelf* s);
  destroy_list(list* l); //and ll_nodes
  destroy_ware(ware* w);
  destroy_node(node* n);
  destroy_cart(cart* c);
} 
*/

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

int total_items(node *n, int total)
{
  if(n)
    {
      total = total_items (n->left_node, total);
      total = total_items (n->right_node, total);
      return (total +1);
    }
  return(total);
}

int print_tree_aux(node* n, int i, int low, int high) 
 {
   if(n)
     {
       i = print_tree_aux(n->left_node, i, low, high);
       if ((low < i && i <= high) || (low == high))
	 printf("%d. %s\n", i, get_name(n));
       i = print_tree_aux(n->right_node, i, low, high);
       return (i);
     }
   return(i+1);
 }

void print_tree(root* root, tree_root *tree, int low, int high)
{
  bool warehouse = true;
  if (root -> warehouse == tree) warehouse = true;
  else warehouse = false;
  print_line();

  if (tree_is_empty(tree))
    {
      if (warehouse == true) printf("The warehouse is empty!\n");
      else if (warehouse == false) printf("Your cart is empty!\n");
      print_line();
      return;
    }
  if (low == 0 && warehouse) printf("----- Items in warehouse ------\n");
  else if (low == 0) printf("----- Items in cart ------\n");
  
  print_tree_aux(Top(tree), 0, low, high);
  print_line();
}


