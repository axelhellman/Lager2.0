#include "database.h"

// ==================
// ----- STRUCT -----
// ==================



// shelf, items are stored here
struct shelf
{
  struct item
  {
    char *name;
    char *description;
    int price;
  } item;

  char *shelf_num;
  int num_items;
  
  shelf *next_shelf;
};

enum prev_action_e
  {
    NONE,
    ADD,
    REMOVE,
    EDIT
  };

// warehouse
struct warehouse
{
  shelf *first_shelf;

  // used to save the previous state. Used by undo_action
  struct _prev_state
  {
    enum prev_action_e prev_action;
    shelf *old_shelf;
    int old_index;
  } prev_state;
};



// ===============
// ----- AUX -----
// ===============



bool is_shelf_taken(warehouse *warehouse_list, const char *shelf_num)
{
  for(shelf *shelf = warehouse_list->first_shelf; shelf != NULL; shelf = shelf->next_shelf)
    {
      if(strcmp(shelf_num, shelf->shelf_num) == 0)
	{
	  return true;
	}
    }

  return false;
}

int warehouse_empty(warehouse *warehouse_list)
{
  if(warehouse_list->first_shelf == NULL)
    {
      return 1;
    }

  return 0;
}

shelf * create_new_shelf(char *name, char *description, int price,
			 char *shelf_num, int num_items);

int get_shelf_index(warehouse *warehouse_list, shelf *shelf)
{
  struct shelf *crnt_shelf = warehouse_list->first_shelf;
  int index = 0;
  
  for(index = 0; crnt_shelf != shelf; ++index)
    {
      crnt_shelf = crnt_shelf->next_shelf;
      if(crnt_shelf == NULL)
	{
	  return -1;
	}
    }

  return index;
}

shelf * copy_shelf(shelf *shelf)
{
  struct shelf * copy =
    create_new_shelf(strdup(shelf->item.name),
		     strdup(shelf->item.description),
		     shelf->item.price,
		     strdup(shelf->shelf_num),
		     shelf->num_items);

  copy->next_shelf = shelf->next_shelf;

  return copy;
}

// Get the last element of warehouse_list
shelf * get_last_shelf(warehouse *warehouse_list)
{
  shelf *shelf = warehouse_list -> first_shelf;
  if(shelf == NULL)
    {
      return NULL;
    }
  
  while(1)
    {
      if(shelf -> next_shelf == NULL)
	{
	  return shelf;
	}
      else
	{
	  shelf = shelf -> next_shelf;
	}
    }

  return NULL;
}

// Get shelf at index in warehouse_list
shelf * get_shelf(warehouse *warehouse_list, int index)
{
  shelf *shelf = warehouse_list -> first_shelf;
  
  for(int i = 0; i != index; ++i)
    {
      shelf = shelf -> next_shelf;
      if(shelf == NULL)
	{
	  return NULL;
	}
    }

  return shelf;
}

char * get_name(shelf *shelf)
{
  return (shelf -> item.name);
}

char * get_description(shelf *shelf)
{
  return shelf -> item.description;
}

int get_price(shelf *shelf)
{
  return shelf -> item.price;
}

char * get_shelf_num(shelf *shelf)
{
  return shelf -> shelf_num;
}

int get_num_items(shelf *shelf)
{
  return shelf -> num_items;
}

shelf * get_next_shelf(shelf *shelf)
{
  return shelf -> next_shelf;
}

shelf * get_first(warehouse * warehouse_list)
{
  return warehouse_list -> first_shelf;
}



// ======================
// ----- SAVE STATE -----
// ======================



void save_state(warehouse *warehouse_list, shelf *shelf,
		int index, enum prev_action_e action)
{
  warehouse_list->prev_state.prev_action = action;
  warehouse_list->prev_state.old_index = index;
  
  switch(action)
    {
    case NONE:
      
      break;

    case ADD:
      warehouse_list->prev_state.old_shelf = NULL;
      break;

    case REMOVE:
      warehouse_list->prev_state.old_shelf = copy_shelf(shelf);
      break;

    case EDIT:
      warehouse_list->prev_state.old_shelf = copy_shelf(shelf);
      break;
    }
}



// =========================
// ----- NEW WAREHOUSE -----
// =========================



void init_warehouse(warehouse *warehouse_list)
{
  warehouse_list -> first_shelf = NULL;
  warehouse_list -> prev_state.prev_action = NONE;
  warehouse_list -> prev_state.old_shelf = NULL;
  warehouse_list -> prev_state.old_index = 0;
}

warehouse * new_warehouse()
{
  warehouse *warehouse_list =
    (warehouse*) malloc(sizeof(warehouse));

  init_warehouse(warehouse_list);

  return warehouse_list;
}



// ===============
// ----- ADD -----
// ===============



// Declares the variables of shelf
void create_new_shelf_aux(shelf *shelf, char *name, char *description, int price,
		  char *shelf_num, int num_items)
{
  shelf -> item.name = calloc(strlen(name)+1, sizeof(char));
  strcpy(shelf->item.name, name);
  //shelf -> item.name = name;
  shelf -> item.description = description;
  shelf -> item.price = price;
  
  shelf -> shelf_num = shelf_num;
  shelf -> num_items = num_items;

  shelf -> next_shelf = NULL;
}

// Creates a new shelf
shelf * create_new_shelf(char *name, char *description, int price,
		  char *shelf_num, int num_items)
{
  shelf *shelf = (struct shelf *) malloc(sizeof(struct shelf));
  assert(shelf != NULL);

  create_new_shelf_aux(shelf, name, description, price,
		        shelf_num, num_items);

  return shelf;
}


// -----


// adds a new item to warehouse_list
void add_shelf(warehouse *warehouse_list, char *name, char *description, int price,
	      char *shelf_num, int num_items)
{
  // create new shelf
  shelf *shelf = create_new_shelf(name, description, price, shelf_num, num_items);
  
  // check: is warehouse empty?
  if(warehouse_list -> first_shelf == NULL)
    {
      // yes: put first in list
      warehouse_list -> first_shelf = shelf;
    }
  else
    {
      // no: append to last element
      struct shelf *end_shelf = get_last_shelf(warehouse_list);
      end_shelf -> next_shelf = shelf;
    }

  // Save this action
  save_state(warehouse_list, shelf, get_shelf_index(warehouse_list, shelf), ADD);
}



//==================
//----- REMOVE -----
//==================



// Remove shelf at index in warehouse_list
void remove_shelf(warehouse *warehouse_list, int index)
{
  shelf *prev_shelf = get_shelf(warehouse_list, index-1);
  shelf *shelf = prev_shelf -> next_shelf;

  assert(shelf != NULL);

  save_state(warehouse_list, shelf, index, REMOVE);
  
  prev_shelf -> next_shelf = shelf -> next_shelf;
  free(shelf);
}



//================
//----- EDIT -----
//================



void edit_shelf(warehouse* warehouse_list, shelf *shelf, char *name, char *description, int price, char *shelf_num, int num_items)
{
  save_state(warehouse_list, shelf, get_shelf_index(warehouse_list, shelf), EDIT);
  
  shelf -> item.name = name;
  shelf -> item.description = description;
  shelf -> item.price = price;
  shelf -> shelf_num = shelf_num;
  shelf -> num_items = num_items;
}



//===================
//----- DESTROY -----
//===================


// Jag har ingen aning om vad jag gör haha! Men försöker göra något som friar allt minne.
// destroys the entire warehouse
/*
void destroy_tree(tree* tree, node *node_to_destroy)
{
  node *tmp_node = NULL;
  node *left_node = node_to_destroy -> left_node;
  node *right_node = node_to_destroy  -> right_node;


  while(node_to_destroy != NULL)
    {
      tmp_node = node_to_destroy;
      free(tmp_node);
      destroy_tree(left_node);
      destroy_tree(right_ndoe);


    }

  free(tree);
}
*/


// =======================
// ----- UNDO ACTION -----
// =======================



void undo_action(warehouse *warehouse_list)
{

  // the shelf that was added, removed or edited
  shelf *undo_shelf = get_shelf(warehouse_list, warehouse_list->prev_state.old_index);
  // the previous state of undo_shelf
  shelf *old_shelf  = warehouse_list->prev_state.old_shelf;
  // the shelf before the shelf that needs "undo-ing"
  shelf *prev_shelf = NULL;


  
  // if undo_shelf is the first shelf in the warehouse
  if(warehouse_list->prev_state.old_index != 0)
    {
      prev_shelf = get_shelf(warehouse_list, warehouse_list->prev_state.old_index - 1);
    }

  switch(warehouse_list -> prev_state.prev_action)
    {
    case ADD:
      // remove that which was added

      // set prev_shelf's next_shelf to the shelf after undo_shelf
      if(prev_shelf == NULL)
	{
	  warehouse_list->first_shelf = undo_shelf->next_shelf;
	}
      else
	{
	  prev_shelf->next_shelf = undo_shelf->next_shelf;
	}
      
      // free up the memory
      free(undo_shelf);

      warehouse_list -> prev_state.prev_action = NONE;
      break;

    case REMOVE:
      // add that which was removed

      // if we removed the first shelf of the warehouse
      if(prev_shelf == NULL)
	{
	  old_shelf->next_shelf = warehouse_list->first_shelf;
	  warehouse_list->first_shelf = old_shelf;
	}
      else
	{
	  old_shelf->next_shelf = prev_shelf->next_shelf;
	  prev_shelf->next_shelf = old_shelf;
	}
      
      warehouse_list -> prev_state.prev_action = NONE;
      break;

    case EDIT:
      // return an item to it's former glory

      if(prev_shelf == NULL)
	{
	  warehouse_list->first_shelf = old_shelf;
	}
      else
	{
	  prev_shelf->next_shelf = old_shelf;
	}
      
      old_shelf->next_shelf = undo_shelf->next_shelf;

      free(undo_shelf);
	
      warehouse_list -> prev_state.prev_action = NONE;
      break;

    case NONE:
      // tell user there's nothing to undo
      printf("There's nothing to undo!\n");
      break;
      
    default:
      // something went wrong
      break;
    }
}
