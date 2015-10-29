#include "tree.h"
#include "list.h"

// ----- HIDDEN FUNCTIONS --------------------------- 
void destroy_shelf(void* s);
void destroy_llnode(linked_list_node* ll_node);
void print_check_out_aux(node* n, int amount);
linked_list_node* get_prev_node(list* l, shelf* s);
void insert_shelf(list *list, shelf *new_shelf);

//---------------------------------------------------
//---------------------------------------------------


struct list_s
{
  int total;
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

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

int get_amount(node* node)
{
  list* list = get_list(node);
  return (list -> total);
}
char* get_shelf_name1(shelf* s)
{
  return (s -> shelf_name);
}
char* get_shelf_name2(linked_list_node *crnt_ll_node) //endast i list.c
{
  shelf* s = crnt_ll_node -> ll_content;
  return (s -> shelf_name);
}

int get_shelf_amount1(shelf* s)
{
  return (s -> amount);
}
int get_shelf_amount2(linked_list_node *crnt_ll_node) //endast i list.c
{
  shelf* s = crnt_ll_node -> ll_content;
  int a = s -> amount;
  return a;
}

linked_list_node* get_first(list* l)
{
  return (l -> ll_first);
}

shelf* get_shelf(node* n, char* shelf_name)
{
  list* l = get_list(n);
  linked_list_node* crnt_llnode;
  
  for (crnt_llnode = get_first(l); crnt_llnode != NULL; crnt_llnode = crnt_llnode -> next_node)
    {
      shelf* crnt_shelf = crnt_llnode -> ll_content;
      char* crnt_name = get_shelf_name2(crnt_llnode);

      if (strcmp(crnt_name, shelf_name) == 0) return crnt_shelf;
    }
  return NULL;
}


//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

list* create_new_list(int total, linked_list_node* ll_node)
{
  list *list = calloc(1, sizeof(struct list_s));
  assert(list != NULL);
  list -> total = total;
  list -> ll_first = ll_node;
  list -> ll_last = ll_node;
  return list;
}
linked_list_node* create_new_ll(shelf* shelf)
{
  linked_list_node *ll_node = calloc(1, sizeof(struct linked_list_node_s));
  assert(ll_node != NULL);
  ll_node -> ll_content = shelf;
  return ll_node;
}
shelf* create_new_shelf(char* shelf_name, int amount)
{
  shelf *shelf = calloc(1, sizeof(struct shelf_s));
  assert(shelf != NULL);
  shelf -> shelf_name = strdup(shelf_name);
  shelf -> amount = amount;
  return shelf;
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

bool list_is_empty(node* n)
{
  list* l = get_list(n);
  if (l == NULL) return true;
  else if (l -> ll_first == NULL) //&& l -> ll_last == NULL)
    return true;
  else return false;
}

void add_shelf(node* node, char* shelf_name, int new_amount)
{
  shelf* s = get_shelf(node, shelf_name);
  if (s)
    {
      new_amount = new_amount + s -> amount;
      remove_shelf(node, get_shelf(node, shelf_name));
    }
  
  shelf* new_shelf = create_new_shelf(shelf_name, new_amount);
  list* l = get_list(node);
  insert_shelf(l, new_shelf);
  return;
}

void remove_shelf(node* n, shelf* shelf)
{
  list* l = get_list(n);
  linked_list_node* prev = get_prev_node(l, shelf);
  linked_list_node* remove;
  if (prev == NULL)
    {
      remove = l -> ll_first;
      l -> ll_first = remove -> next_node;
    }
  else
    {    
      remove = prev -> next_node;
      linked_list_node* next = remove -> next_node;
      prev -> next_node = next;
    }
  int r_amount = get_shelf_amount2(remove);
  l -> total = l -> total - r_amount;
  destroy_llnode(remove);
}

node* add_amount(node* n, int add_amount)
{
  list* l = get_list(n);
  l -> total = l -> total + add_amount;
  shelf* first_shelf = l -> ll_first -> ll_content;
  first_shelf -> amount = first_shelf -> amount + add_amount;
  return n;
}

node* remove_amount(node* n, int r_amount)
{
  list* l = get_list(n);
  linked_list_node* crnt_node = l -> ll_first;
  while(r_amount != 0)
    {
      int crnt_amount = get_shelf_amount2(crnt_node);
      shelf* crnt_shelf = crnt_node -> ll_content;
      if (r_amount == crnt_amount)
	{
	  remove_shelf(n, crnt_shelf);
	  r_amount = r_amount - crnt_amount;
	}
      else if (r_amount < crnt_amount)
	{
	  crnt_shelf -> amount = crnt_amount - r_amount;
	  l -> total = l -> total - r_amount;

	  char* shelf_name = strdup(get_shelf_name1(crnt_shelf));
	  int new_amount = crnt_shelf -> amount;
	  remove_shelf(n, crnt_shelf);
	  add_shelf(n, shelf_name, new_amount);
	  free(shelf_name);
	  r_amount = 0;
	}
      else // (amount > crnt_amount)
	{
	  crnt_node = crnt_node -> next_node;
	  remove_shelf(n, crnt_shelf);
	  r_amount = r_amount - crnt_amount;
	}
     
    }
  return n;
}

bool shelf_is_taken_list(list* list, char* shelf_name)
{
  if (shelf_name == NULL) return false;

  for (linked_list_node *current_node = list -> ll_first; current_node != NULL; current_node = current_node->next_node)
    {
      shelf* crnt_shelf = current_node -> ll_content;
    
      char* crnt_name = calloc(128, sizeof(char));
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
  list* l = get_list(node);
  if(node != NULL)
    {
      if (getLeft(node))
	{
	  bool taken_left = shelf_is_taken(getLeft(node), shelf_name);
	  if (taken_left) return true;
	}

      taken = shelf_is_taken_list(l, shelf_name);
      if (taken) return true;

      if (getRight(node))
	{
	  bool taken_right = shelf_is_taken(getRight(node), shelf_name);
	  if (taken_right) return true;
	}
    }
  return taken;
}
//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------


void print_check_out(root* root, node* n)
{
  if(n)
    {
      print_check_out(root, getLeft(n));
      node* w_node = find_node(Top(Warehouse), get_key(n));
      print_check_out_aux(w_node, get_cart_amount(n));
      print_check_out(root, getRight(n));
    }
}

void shelf_names(linked_list_node *crnt_ll_node)
{
  if (crnt_ll_node == NULL) return;
 
  char *name = get_shelf_name2(crnt_ll_node);
  if (crnt_ll_node -> next_node) printf("%s, ", name);
  else printf("%s\n", name);
  
  shelf_names(crnt_ll_node -> next_node);
}

//---------------------------------------------------
//------ DESTROY ------------------------------------
//---------------------------------------------------
//---------------------------------------------------

void destroy_shelf(void* s)
{
  shelf* shelf = s;
  free(shelf -> shelf_name);
  free(shelf);
}
void destroy_llnode(linked_list_node* ll_node)
{
  destroy_shelf(ll_node -> ll_content);
  ll_node -> ll_content = NULL; //är detta onödigt?
  ll_node -> next_node = NULL;
  free(ll_node);
}
void destroy_list(list* l)
{
  if (l == NULL)
    {
      puts("l är null");
      return;
    }
  linked_list_node* ll_node = l -> ll_first;
  linked_list_node* tmp_ll_node = NULL;
  while (ll_node != NULL)
    {
      tmp_ll_node = ll_node;
      ll_node = ll_node -> next_node;
      destroy_llnode(tmp_ll_node);
    } 
  if (l != NULL)
    free(l);
}

//---------------------------------------------------
//---------------------------------------------------
//--- HIDDEN FUNCTIONS ------------------------------
//---------------------------------------------------
//---------------------------------------------------

void print_check_out_aux(node* n, int amount)
{
  char* name = get_key(n);
  list* l = get_list(n);
  linked_list_node* crnt_node = l -> ll_first;
  while(amount != 0)
    {
      int crnt_amount = get_shelf_amount2(crnt_node);
      shelf* crnt_shelf = crnt_node -> ll_content;
      char* shelf_name = crnt_shelf -> shelf_name;
      
      if (amount == crnt_amount)
	{
	  printf("* %s (%d %s)\n", shelf_name, crnt_amount, name);
	  amount = amount - crnt_amount;
	}
      else if (amount < crnt_amount)
	{
	  printf("* %s (%d %s)\n", shelf_name, amount, name);
	  amount = 0;
	}
      else // (amount > crnt_amount)
	{
	  printf("* %s (%d %s)\n", shelf_name, crnt_amount, name);
	  crnt_node = crnt_node -> next_node;
 	  amount = amount - crnt_amount;
	}
    }
  return;
}
  
linked_list_node* get_prev_node(list* l, shelf* s)
{
  //if (list_is_empty(l)) return NULL; //ny

  linked_list_node* crnt_node = l -> ll_first;
  if (crnt_node -> next_node == NULL) return NULL;
  if (((shelf*) crnt_node -> ll_content) == s) return NULL;
 
  shelf* next_shelf = crnt_node -> next_node -> ll_content;
  while (crnt_node != NULL) {
   
    if (next_shelf == s)
      return crnt_node;
    else
      {
	crnt_node = crnt_node -> next_node;
	next_shelf = crnt_node -> next_node -> ll_content;
      }
  }
  return NULL;
}

void insert_shelf(list *list, shelf *new_shelf)
{
  linked_list_node *new_node = create_new_ll(new_shelf);
  int amount = new_shelf -> amount;
  list -> total = list -> total + amount;

  linked_list_node *prev_node = NULL;
  linked_list_node *crnt_node = list -> ll_first;
   if (crnt_node == NULL)
    {
      list -> ll_first = new_node;
      list -> ll_last = new_node;
      return;
      }  
  
  while (true)
    {
      if (crnt_node == NULL)
	{
	  prev_node -> next_node = new_node;
	  list -> ll_last = new_node;
	  break;
	}
            
      int crnt_amount = get_shelf_amount2(crnt_node);
 
      if (crnt_amount <  amount && prev_node == NULL)
	{
	  list -> ll_first = new_node;
	  new_node -> next_node = crnt_node;
	  break;
	}
      else if (crnt_amount <  amount || crnt_amount == amount)
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
	}
      //break;
    }
  return;
}
