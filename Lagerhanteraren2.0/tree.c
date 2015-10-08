#include "tree.h"

struct tree_root_s
{
  node *top_node; //tree är top-node
  //  cart *cart;
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

struct list_s
{
  int total_amount;
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
  // här tror jag att jag gör så att pekaren tmp_shelf pekar på samma sak som pekaren ll_content. Det här känns lite fuskigt?!
  return (tmp_shelf -> shelf_name);
}
int get_amount(node *node)
{
  N_Content_eq_Ware;
  return (ware -> list -> total_amount);
}
node* get_root(tree_root *tree)
{
  return (tree -> top_node);
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

list* create_new_list(amount)
{
 list *list = calloc(1, sizeof(struct list_s));
  assert(list != NULL);
  list -> total_amount = amount;
  return list;
}

linked_list_node* create_new_ll(list * list)
{
  linked_list_node *ll_node = calloc(1, sizeof(struct linked_list_node_s));
  assert(ll_node != NULL);

  list -> ll_first = ll_node;
  list -> ll_last = ll_node;
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

  ware* ware = node -> n_content;
  ware = create_new_ware(name, description, price);

  list* list = create_new_list(amount);
  ware -> list = list;
  
  linked_list_node * ll_node = create_new_ll(list);
  
  shelf * shelf = create_new_shelf(shelf_name, price);
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

void balance_tree(node* node)
{ 
  puts("lala");
}


void remove_node(node* node, char* name, list * list, shelf_node * shelf_node)
 )
{
  node *temp = find_node(node, name);

  if (temp == NULL) return temp;

  
  else if (temp == node)
    {
      
      free(shelf_node);
      free(list);
      free(temp);
	//Fall då det enbart finns en vara på en hyllplats
    }

  else
    {
      //Fall då det finns fler än en vara på olika hyllor
    }
  
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


node* remove_node(node *node, char* name) // TODO: Behövs antagligen fler argument
{
  node *node = find_node(TreeRoot, name);
  
  // base case
  if (temporary == NULL) printf("non existing\n");
  

     // En node med ett barn till höger/vänster
    else
      {
if (temporary->left_node == NULL)
 {
   temporary = node->right_node;
   free(temporary); //TODO: free(listan m.m)
   return node;
 }
else if (temporary->right_node == NULL)
 {
   temporary = node->left_node;
   free(temporary); // TODO: lika som ovna
   return node;
 }
/*
// En node med två löv till v & h
// temp = minValueNode(->right_node);
node->name = temporary->name;
node->right_node = remove_node(node->right_node, temporary->name);
*/
      }
  return node;
}

void update_node(node* node, char* shelf_name, int amount)
{
  puts("hej");
}


void balance_tree(node* node)
{ 
  puts("lala");
}

/*node * minValueNode(node* node)
{
  node*  = node;
  
  // loop down to find the leftmost leaf 
  while (current->left_node != NULL)
        current = current->left_node;
  
  return current;
}
*/




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
