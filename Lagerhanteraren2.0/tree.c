#include "tree.h"

list * create_new_list (int amount); //lägg till destructor dest
linked_list_node * create_new_ll();
node* separate_node(tree_root *tree, node* rn);

struct tree_root_s
{
  node *top_node; //tree är top-node
  list *data;
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

typedef void(*destructor)(void*);

struct list_s
{
  int total;
  destructor free_content;
  linked_list_node *ll_first;
  linked_list_node *ll_last;
};

struct linked_list_node_s
{
  void* ll_content;
  linked_list_node* next_node;
};

struct shelf_s
{
  char* shelf_name;
  int amount;
};

struct cart_item_s
{
    char* name;
    int price;
    int amount;
    int total_price;
  };

char * get_name(node *node)
{
  return (node -> key);
}
char * get_description(node *node)
{
  N_Content_eq_Ware;
  return (ware -> description);
}
int get_price(node *node)
{
  N_Content_eq_Ware;
  return (ware -> price);
}
char * get_shelf_name(node *node)
{
  N_Content_eq_Ware;
  shelf * tmp_shelf = ware -> list -> ll_first -> ll_content;
  return (tmp_shelf -> shelf_name);
}
int get_amount(node *node)
{
  N_Content_eq_Ware;
  return (ware -> list -> total);
}
node* get_root(tree_root *tree)
{
  return (tree -> top_node);
}
list* get_list(node* n)
{
  ware *w = n -> n_content;
  return (w -> list);
}
int get_shelf_amount(linked_list_node *crnt_ll_node)
{
  shelf* s = crnt_ll_node -> ll_content;
  int a = s -> amount;
  return a;

}
char* get_shelf_name2(linked_list_node *crnt_ll_node)
{
  shelf* s = crnt_ll_node -> ll_content;
  //char* shelf_name = s -> shelf_name;
  return (s -> shelf_name);
}

cart_item* add_item_cart(node* n, int amount) 
{
  cart_item* cart_item = calloc(1, sizeof(struct cart_item_s));
  cart_item -> name = get_name(n);
  cart_item -> price = get_price(n);
  cart_item -> amount = amount;
  return cart_item;
}

list* create_new_cart()
{
  list* cart = create_new_list(0); //lägg till &destroy_cart_item
  linked_list_node * ll_node = create_new_ll(cart);
  cart -> ll_first = ll_node;
  cart -> ll_last = ll_node;
  //connect_cart(cart, ll_node);
  return cart;
}
  
ware* create_new_ware(char* name, char* description, int price)
{
  ware* ware = calloc(1, sizeof(struct ware_s));
  assert (ware != NULL);

  ware -> name = name;
  ware -> description = description;
  ware -> price = price;
  return ware;
}
list* create_new_list(int total) //lägg till destructor dest
{
  list *list = calloc(1, sizeof(struct list_s));
  assert(list != NULL);
  list -> total = total;
  //list -> free_content = dest;
  return list;
}
linked_list_node* create_new_ll()
{
  linked_list_node *ll_node = calloc(1, sizeof(struct linked_list_node_s));
  assert(ll_node != NULL);
  return ll_node;
}
shelf* create_new_shelf(char* shelf_name, int amount)
{
  shelf *shelf = calloc(1, sizeof(struct shelf_s));
  assert(shelf != NULL);
  shelf -> shelf_name = shelf_name;
  shelf -> amount = amount;
  return shelf;
}

node * create_new_node(char* name, char* description, int price, char* shelf_name, int amount)
{
  node *node = calloc(1, sizeof(struct node_s));
  assert(node != NULL);
  node -> key = name;

  ware* ware = create_new_ware(name, description, price);
  node -> n_content = ware;
  list* list = create_new_list(amount); //lägg till &destroy_shelf
  ware -> list = list;
  linked_list_node * ll_node = create_new_ll();
 
  list -> ll_first = ll_node;
  list -> ll_last = ll_node;
  shelf * shelf = create_new_shelf(shelf_name, amount);
  ll_node -> ll_content = shelf;
  
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
    
  //return NULL;
}


bool node_exists(tree_root* tree, char* name)
{
  if (find_node(tree -> top_node, name) != NULL) return true;
  return false;
}


void insert_shelf(list *list, shelf *new_shelf)
{
  linked_list_node *new_node = create_new_ll();
  new_node -> ll_content = new_shelf;
  int amount = new_shelf -> amount;
  list -> total = list -> total + amount;
  printf("New total: %d", list -> total);
  linked_list_node *prev_node = NULL;
 
  linked_list_node *crnt_node = list -> ll_first;

  while (true)
    {
      if (crnt_node == NULL)
	{
	  prev_node -> next_node = new_node;
	  return;
	}
            
      int crnt_amount = get_shelf_amount(crnt_node);
 
      if (crnt_amount <  amount && prev_node == NULL)
	{
	  list -> ll_first = new_node;
	  new_node -> next_node = crnt_node;
	  break;
	}
      else if (crnt_amount <  amount)
	{
	  prev_node -> next_node = new_node;
	  new_node -> next_node = crnt_node;
	  break;
	}
      else if (crnt_amount > amount)
	{
	  prev_node = crnt_node;
	  crnt_node = crnt_node -> next_node;
	}
      
      else
	{
	  puts("something is wrong");
	  break;
	}
    }
}

void update_node(node* node, char* shelf_name, int amount)
{
  shelf *new_shelf = create_new_shelf(shelf_name, amount);
  list* l = get_list(node);
  insert_shelf(l, new_shelf);  
}

void insert_or_update(tree_root* tree, char* name, char* description, int price, char* shelf_name, int amount)
{
  node * node = find_node(tree -> top_node, name);
  if (node == NULL)
    {
      node = create_new_node(name, description, price, shelf_name, amount);
      insert_new_node(tree, node);
      return;
    }
  else // find_node == any node
    {
      update_node(node, shelf_name, amount);
      return;
    }
}


void insert_new_node(tree_root * tree, node* new_node)
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

tree_root* create_new_tree()
{
  tree_root *tree_root = calloc(1, sizeof(struct tree_root_s));
  tree_root -> top_node = NULL;
  list * new_cart = create_new_cart();
  tree_root -> data = new_cart;
  return (tree_root);
}

bool shelf_is_taken_aux(list* list, char* shelf_name)
{
  for (linked_list_node *current_node = list -> ll_first; current_node != NULL; current_node = current_node->next_node)
    {
      shelf* crnt_shelf = current_node -> ll_content;
    
      char* crnt_name = calloc(128, sizeof(char)); //crnt_shelf -> shelf_name;
      strcpy(crnt_name, crnt_shelf -> shelf_name);

      if(strcmp(crnt_name, shelf_name) == 0)
	{
	  free(crnt_name);
	  return true;
	}
      free(crnt_name);
    }
  return false;
}

bool shelf_is_taken(node* node, char* shelf_name)
{
  bool taken = false;
  ware* w = node -> n_content;
  if(node != NULL)
    {
      if (node -> left_node)
	{
	  bool taken_left = shelf_is_taken(node -> left_node, shelf_name);
	  if (taken_left) return true;
	}

      taken = shelf_is_taken_aux(w -> list, shelf_name);
      if (taken) return true;

      if (node -> right_node)
	{
	  bool taken_right = shelf_is_taken(node -> right_node, shelf_name);
	  if (taken_right) return true;
	}
    }
  return taken;
}

node* find_prev_node(tree_root* tree, node* n, char* name)
{
  node* tmp_node = find_node(TreeRoot, name);
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
bool one_child (node *n)
{
  if (n -> left_node == NULL && n -> right_node != NULL) return true;
  else if (n -> right_node == NULL && n -> left_node != NULL) return true;
  else return false;
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

  insert_new_node(tree, tmp_tree -> top_node -> left_node);
  insert_new_node(tree, tmp_tree -> top_node -> right_node);
}
node* child(node* n)
{
  if (n -> left_node == NULL && n -> right_node != NULL) return (n -> right_node);
  else if (n -> right_node == NULL && n -> left_node != NULL) return (n -> left_node);
  else return NULL;
}
void remove_node(tree_root* tree, node* n)
{
  node* tmp_node = separate_node(tree, n);
  printf("destroys node (%s) soon\n", get_name(tmp_node));
  //destroy_node(tmp_node);
}
void change_name(tree_root* tree, node* n, char* new_name)
{
  n = separate_node(tree, n);
  n -> key = new_name;
  ((ware*)n -> n_content) -> name = n -> key;
  insert_new_node(tree, n);
  print_tree(TreeRoot, 0,0,0);
  return;
}
node* separate_node(tree_root *tree, node* rn)
{
  bool leaf = node_is_leaf(rn);
  node* prev_node = find_prev_node(tree, TreeRoot, get_name(rn));
  
  if (leaf)
    {
      if(TreeRoot == rn) tree -> top_node = NULL;
      if (prev_node -> right_node == rn) prev_node -> right_node = NULL; 
      if (prev_node -> left_node == rn) prev_node -> left_node = NULL;
    }
  else if (one_child(rn))
    {
      if (TreeRoot == rn) tree -> top_node = child(rn);
      else connect_child(prev_node, rn, child(rn));
    }
  else //node has two_children
    {
      tree_root *tmp_tree = create_new_tree();
      tmp_tree -> top_node = rn;

      if (TreeRoot == rn) tree -> top_node = NULL;	
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
  
void destroy_shelf(void* s)
{
  shelf* shelf = (shelf*) s;
  free(shelf -> shelf_name);
  free(s);
}

void destroy_list(list* l)
{
  linked_list_node* ll_node = l -> ll_first;
  linked_list_node* tmp_ll_node = NULL;
  while (ll_node != NULL)
    {
      tmp_ll_node = ll_node;
      ll_node = ll_node -> next_node;
      l -> free_content(ll_node -> ll_content);
      
      free(tmp_ll_node);
    }
  free(l)
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
void shelf_names(linked_list_node *crnt_ll_node)
{
  if (crnt_ll_node == NULL) return;
 
  char *name = get_shelf_name2(crnt_ll_node);
  if (crnt_ll_node -> next_node) printf("%s, ", name);
  else printf("%s\n", name);
  
  shelf_names(crnt_ll_node -> next_node);
}
void print_shelfs(linked_list_node *crnt_ll_node)
{
  if (crnt_ll_node == NULL)
    {
      puts("crnt_ll_node är null, finns inga hyllor att printa");
      return;
    }
 
  char *name = get_shelf_name2(crnt_ll_node);
  int amount = get_shelf_amount(crnt_ll_node);

  printf("\nShelf: %s \tAmount: %d", name, amount);
  print_shelfs(crnt_ll_node -> next_node);
}
int total_items(node *n, int total)
{
  if(n)
    {
      total = total_items (n->left_node, total);
      total = total_items (n->right_node, total);
      return (total);
    }
  return(total+1);
}

int print_tree(node *n, int i, int low, int high) 
 {
   if(n)
     {
       i = print_tree (n->left_node, i, low, high);
       if ((low < i && i <= high) || (low == high))
	 printf("%d. %s\n", i, get_name(n));
       i = print_tree (n->right_node, i, low, high);
       return (i);
     }
   return(i+1);
 }

void print_warehouse(tree_root *tree, int low, int high)
{
   print_line();
    if(tree_is_empty(tree))
    {
      printf("The warehouse is empty!\n");
      return;
    }
  if (low == 0) printf("----- Items in warehouse ------\n");
  print_tree(TreeRoot, 0, low, high);
  
}
linked_list_node* get_ll_node(list* l)
{
  return (l -> ll_first);
}
/*
int main (void)
{
  printf("Hej hej");
  tree_root* tree = create_new_tree();
  print_tree(tree -> top_node);
  printf("hej igen");
  insert_or_update(tree, "Gurka", "Grön och skön", 12, "A23", 2);
  insert_or_update(tree, "Häst", "fulsfdkj", 34, "A5", 1);
  insert_or_update(tree, "Berg", "högt", 10000, "G34", 3);
  insert_or_update(tree, "Lars", "grön", 2, "F2", 1);
  insert_or_update(tree, "Danne", "skäggig", 1, "E2", 1);
  insert_or_update(tree, "Gös", "skäggig", 1, "E2", 1);
  insert_or_update(tree, "Apa", "skäggig", 1, "E2", 1);
  puts("print_tree");
  print_tree(TreeRoot);
  puts("print_tree2");
  print_tree2(tree -> top_node, 0);

  node * n = TreeRoot;
  if(!n) puts("n null");
  
  if (shelf_is_taken(n, "A7"))
    {
      printf("shelf is taken/occupied");
    }
  else
    {
      printf("shelf free");
    }
  print_shelfs(get_list(find_node(TreeRoot, "Gurka")) -> ll_first);
  // list* l = create_new_list(0, destroy_shelf);
  
}

*/

