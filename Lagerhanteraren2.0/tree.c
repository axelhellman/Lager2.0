#include "tree.h"
#ifdef LIST_H
#include "list.h"
#endif /* LIST_H */
#include "smallfunc.h"

// ----- HIDDEN FUNCTIONS ------------------------

bool node_is_leaf(node* n);
node* child(node* n);
void connect_child(node* prev_node, node* n, node* child);
void re_insert_nodes(tree_root* tree, tree_root* tmp_tree);
node* separate_node(root* root, tree_root* tree, node* rn);
int print_tree_aux(node* n, int i, int low, int high, bool warehouse);
void check_out_cart_aux(root* root, node* n);
	    
//---------------------------------------------------
//---------------------------------------------------

struct root_s
{
  tree_root* warehouse;
  tree_root* cart;
};

struct tree_root_s
{
  node *top_node;
};

struct node_s
{
  char* key;
  void *n_content;
  node *left_node;
  node *right_node;
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
  char* name;
  int price; 
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

char * get_key(node *node)
{
  return (node -> key);
}

char * get_ware_name(node *node)
{
  return (((ware*) node -> n_content) -> name);
}

char * get_cart_name(node *node)
{
  return (((cart_item*) node -> n_content) -> name);
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

int get_cart_amount(node *cart_node)
{
  cart_item* ci = cart_node -> n_content;
  return(ci -> amount);
}

int get_cart_price(node* cart_node)
{
  cart_item* ci = cart_node -> n_content;
  return (ci -> total_price);
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------


node * create_new_node(char* name)
{
  node *node = calloc(1, sizeof(struct node_s));
  assert(node != NULL);
  node -> key = strdup(name);
 
  return node;
}

node* create_new_ware(ArgsWare)
{
  ware* ware = calloc(1, sizeof(struct ware_s));
 
  assert (ware != NULL);
 
  ware -> name = strdup(name);
  ware -> description = strdup(description);
  ware -> price = price;
  node* n = create_new_node(name);

  n -> n_content = ware;

  shelf * shelf = create_new_shelf(shelf_name, amount);
  linked_list_node * ll_node = create_new_ll(shelf);
  list* list = create_new_list(amount, ll_node); 

  ware -> list = list;
  return n;
}

node* create_new_cart_item(node* item, int amount)
{
  cart_item* ci = calloc(1, sizeof(struct cart_item_s));
  assert(ci != NULL);

  char* name = strdup(get_key(item));
  ci -> name = name;
  ci -> price = get_price(item);
  ci -> amount = amount;
  ci -> total_price = (ci -> price)*(ci -> amount);

  node * n = create_new_node(name);
  n -> n_content = ci;
  return n;  
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
  char* old_key = get_key(n);
  char* old_name = get_ware_name(n);
  n = separate_node(root, Warehouse, n);

  n -> key = strdup(new_name);
  ((ware*) n -> n_content) -> name = strdup(new_name);
  insert_node(Warehouse, n);

  if (node_exists(Cart, old_name))
    {
      node* tmp_node_cart = find_node(Top(Cart), old_name);
      tmp_node_cart = separate_node(root, Cart, tmp_node_cart);
      char* old_cart_key = get_key(tmp_node_cart);
      char* old_cart_name = get_cart_name(tmp_node_cart);

      tmp_node_cart -> key = strdup(new_name);
      ((cart_item*) tmp_node_cart -> n_content) -> name = strdup(new_name);
      insert_node(Cart, tmp_node_cart);

      free(old_cart_key);
      free(old_cart_name);
    }
  free(old_key);
  free(old_name);
  print_tree_aux(Top(Warehouse), 0,0,0, true);
  return;
}

void change_description(node* n, char* new_description)
{
  char* old_description = get_description(n);
  ((ware*)n -> n_content) -> description = strdup(new_description);

 
  free(old_description);
}

void change_price(root* root, node* n, int new_price)
{
  ((ware*)n -> n_content) -> price = new_price;
  if (node_exists(Cart, get_key(n)))
    {
      cart_item* ci = n -> n_content;
      ci -> price = new_price;
      ci  -> total_price = new_price * (ci -> amount);
    }
}

void change_cart_amount(node* cart_node, int add_amount)
{
  cart_item* ci = cart_node -> n_content;
  int new_amount =  ci -> amount + add_amount;
  ci -> amount = new_amount;
  ci -> total_price = ci -> price * new_amount;
}
//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

bool tree_is_empty(tree_root *tree)
{
  if (tree == NULL) return true;
  else if (tree -> top_node == NULL) return true;
  else return false;
}

node* find_node(node* node, char* name)
{
  if (node == NULL) return NULL;
  
  char* crnt_node_name = get_key(node);

  if (strcmp(name, crnt_node_name) == 0)
    {
      return node;
    }
  else if (strcmp(name, crnt_node_name) > 0)
    {
      return find_node(node -> right_node, name);
    }
  else
    {
      return find_node(node -> left_node, name);
    }
}

node* find_prev_node(tree_root* tree, node* n, char* name) 
{
  node* tmp_node = find_node(Top(tree), name);
  if (n == NULL) return NULL;
  char* crnt_node_name = get_key(n);
  
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
      return NULL;
    }
}

bool node_exists(tree_root* tree, char* name)
{
  if (find_node(Top(tree), name) != NULL) return true;
  return false;
}

void insert_new_ware(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount)
{
   node* node = create_new_ware(name, description, price, shelf_name, amount);
   insert_node(tree, node);
   return;
  
}

void insert_node(tree_root* tree, node* new_node)
{  
  if (tree_is_empty(tree))
    {
      tree -> top_node = new_node;
      return;
    }
  node* crnt_node = tree -> top_node;
  char* name = get_key(new_node);

  while (true)
    {
      char* crnt_node_name = get_key(crnt_node);  
      
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



void update_cart_amount(root* root, char* name, int limit)
{
  if (node_exists(Cart, name))
    {
      node* ware_node = find_node(Top(Warehouse), name);
      node* cart_node = find_node(Top(Cart), name);
      cart_item* ci = cart_node -> n_content;
      int cart_amount = ci -> amount;
      if (cart_amount > get_amount(ware_node))
	{
	  ci -> amount = get_amount(ware_node);
	  ci -> total_price = (ci -> total_price) * (ci -> amount);
	}
    }
}

void remove_node(root* root, node* n)
{
  n = separate_node(root, Warehouse, n);
  if (node_exists(Cart, get_key(n)))
    {
      node* tmp_node_cart = separate_node(root, Cart, n);
      destroy_nodes_aux(root, Cart, tmp_node_cart);
    }
  destroy_nodes_aux(root, Warehouse, n);
}

void check_out_cart(root* root)
{
  check_out_cart_aux(root, Top(Cart));
  destroy_nodes(root, Cart, Top(Cart));
  root -> cart -> top_node = NULL;
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

int total_price(node* n, int total)
{
  if(n)
    {
      total = total_price(n->left_node, total);
      total = total_price(n->right_node, total);
      int price = get_cart_price(n);
      return (total + price);
    }
  return(total);
}

int total_items(node* n, int total)
{
  if(n)
    {
      total = total_items (n->left_node, total);
      total = total_items (n->right_node, total);
      return (total +1);
    }
  return(total);
}

void print_tree(root* root, tree_root *tree, int low, int high)
{
  bool warehouse = true;
  if (root -> warehouse == tree) warehouse = true;
  else warehouse = false;
  printf("\n");
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

  print_tree_aux(Top(tree), 0, low, high, warehouse);
  if(!warehouse) printf("\nTotal price: %d kr\n", total_price(Top(tree), 0));  
  print_line();
}

/*
-----------------------------------------------------------------------
-----------------------------------------------------------------------
-------------- D E S T R O Y ------------------------------------------
-----------------------------------------------------------------------
----------------------------------------------------------------------- */

void destroy_cart_item(cart_item * ci)
{
  free(ci -> name); 
  free(ci);
}
void destroy_ware(ware* w)
{
  free(w -> name);
  free(w -> description);
  destroy_list((list*) w -> list);
  free(w);
}
void destroy_nodes_aux(root* root, tree_root* tree, node* n)
{
  if (tree == Cart)
    {
      cart_item* ci = n -> n_content;
      destroy_cart_item(ci);
    }
  else // tree == Warehouse
    {
      ware* w = n -> n_content;
      destroy_ware(w);
    }
  free(n -> key);
  free(n);
}

void destroy_nodes(root* root, tree_root* tree, node* n)
{
  if (n)
    {
      destroy_nodes(root, tree, getLeft(n));
      destroy_nodes(root, tree, getRight(n));
      destroy_nodes_aux(root, tree, n);
    }
}

void destroy_tree(root* root, tree_root* tree)
{
  destroy_nodes(root, tree, Top(tree));
  free(tree);
} 

void destroy_all(root* root)
{
  destroy_tree(root, Cart);
  destroy_tree(root, Warehouse);
  free(root);
}

//---------------------------------------------------
//---------------------------------------------------
//----- HIDDEN FUNCTIONS ----------------------------
//---------------------------------------------------
//---------------------------------------------------

bool node_is_leaf(node* n)
{
  if (n->right_node == NULL && n->left_node == NULL) return true;
  else return false;
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

node* separate_node(root* root, tree_root* tree, node* rn)
{
  bool leaf = node_is_leaf(rn);
  node* prev_node = find_prev_node(tree, Top(tree), get_key(rn));

  if (leaf)
    {
      if (tree -> top_node == rn) tree -> top_node = NULL;
      if (prev_node == NULL) puts("prev_node är null");
      if (prev_node != NULL)
	{
	  if (prev_node -> right_node == rn) prev_node -> right_node = NULL; 
	  else if (prev_node -> left_node == rn) prev_node -> left_node = NULL;
	  else puts("something is wrong");
	}
    }
  else if (child(rn)) //node has one child
    {
      if (Top(tree) == rn) tree -> top_node  = child(rn);
      else connect_child(prev_node, rn, child(rn));
    }
  
  else //node has two children
    {
      struct root_s * tmp_root = create_new_root();
      tree_root* tmp_tree;
      if (tree == Warehouse) 
	{
	  tmp_tree = tmp_root -> warehouse;
	}
      else
	{
	  tmp_tree = tmp_root -> cart;
	}
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
      destroy_all(tmp_root);
    }
  print_line();
  return rn;
}

int print_tree_aux(node* n, int i, int low, int high, bool warehouse) 
 {
   if(n)
     {
       i = print_tree_aux(n->left_node, i, low, high, warehouse);
       if ((low < i && i <= high) || (low == high))
	 {
	   if (warehouse) printf("%d. %s\n", i, get_key(n));
	   else printf("* %s (%d)\n", get_key(n), get_cart_amount(n));
	 }
       i = print_tree_aux(n->right_node, i, low, high, warehouse);
       return (i);
     }
   return(i+1);
 }


void check_out_cart_aux(root* root, node* n)
{
  if (n)
    {
      check_out_cart_aux(root, getLeft(n));

      int cart_amount = get_cart_amount(n);
      node* w_node = find_node(Top(Warehouse), get_key(n));
      remove_amount(w_node, cart_amount);
      int ware_amount = get_amount(w_node);

      if(list_is_empty(w_node) || ware_amount == 0)
	{
	  w_node = separate_node(root, Warehouse, w_node);
	  destroy_nodes_aux(root, Warehouse, w_node);
	}

      check_out_cart_aux(root, getRight(n));
    }
}
