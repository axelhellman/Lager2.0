#include "list.h"
#ifdef TREE_H
#include "tree.h"
#endif /* TREE_H */

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

/*
char * get_shelf_name(node *node)
{
  N_Content_eq_Ware;
  shelf * tmp_shelf = ware -> list -> ll_first -> ll_content;
  return (tmp_shelf -> shelf_name);
  } 
*/

int get_amount(node* node)
{
  list* list = get_list(node);
  return (list -> total);
}

char* get_shelf_name2(linked_list_node *crnt_ll_node)
{
  shelf* s = crnt_ll_node -> ll_content;
  return (s -> shelf_name);
}

int get_shelf_amount(linked_list_node *crnt_ll_node)
{
  shelf* s = crnt_ll_node -> ll_content;
  int a = s -> amount;
  return a;
}

linked_list_node* get_ll_node(list* l)
{
  return (l -> ll_first);
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

list* create_new_list(int total, linked_list_node* ll_node) //lägg till destructor dest //lägg till ll_node
{
  list *list = calloc(1, sizeof(struct list_s));
  assert(list != NULL);
  list -> total = total;
  list -> ll_first = ll_node;
  list -> ll_last = ll_node;
  //list -> free_content = dest;
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
  shelf -> shelf_name = shelf_name;
  shelf -> amount = amount;
  return shelf;
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------


void insert_shelf(list *list, shelf *new_shelf)
{
  linked_list_node *new_node = create_new_ll(new_shelf);
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
//denna ska absolut göras om. Den är bra att ha när vi testar men behövs inte egentligen tror jag
{
  shelf *new_shelf = create_new_shelf(shelf_name, amount);
  list* l = get_list(node);
  insert_shelf(l, new_shelf);  
}




bool shelf_is_taken_list(list* list, char* shelf_name)
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
  list* l = get_list(node);
  //ware* w = node -> n_content;
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
