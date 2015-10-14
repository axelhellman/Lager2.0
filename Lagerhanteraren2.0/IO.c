#include "IO.h"
#include "tree.h"

typedef struct tree_root_s tree_root;

void print_add_shelf(char *name, char *description, int price, char *shelf_name, int num_items);

void print_name(node *node);
void print_description(node *node);	    
void print_price(node *node);	  
void print_shelf_name(node *node);	   
void print_num_items(node *node);

void print_box_shelf(char *name, char *description, int price, char *shelf_name, int num_items);
//void print_box_shelf2(shelf* shelf);
void print_box_shelf_name(char *name, char *description, int price, char *shelf_name, int num_items);
/*
shelf * print_20(warehouse *warehouse_list, shelf *shelf_start);

void edit_shelf_IO_aux(warehouse* warehouse_list, shelf* choosed_shelf);
//char ask_alt(char* question, char* alternatives); */




void add_item_to_cart_IO()
{
  // print_cart(); //not_implemented
  char answer = ask_alt("What would you like to do?\n [c]hoose an item to put in cart\n [n]ext 20 items\n [e]xit", "cne");
  printf("Your choice: %c", answer);
}

void add_ware_IO(tree_root *tree)
{
  puts("\n----- ADD AN ITEM --------------------");
  char* name;
  char* description;
  int price;
  char* shelf_name; 
  int num_items;
  node* node;
  
  name = ask_name();

  if (! node_exists(tree, name))
    {
      description = ask_description();
      price = ask_price();
    }
  else //(node_exists(tree, name))
    {
      node = find_node(TreeRoot, name);
      printf("%s is already in the warehouse.\n", name);
      description = get_description(node);
      price = get_price(node);
      print_description(node);
      print_price(node);
    }
  shelf_name = ask_shelf_name(tree);
  num_items = ask_num_items();
   
  print_line();

  print_add_shelf(name, description, price, shelf_name, num_items);

  char ans = ask_alt("[s]ave this item / [d]on't save / [e]dit", "sde");
  if  (ans == 's')
    {
      insert_or_update(tree, name, description, price, shelf_name, num_items);
      printf("\n%s added to the warehouse!\n", name);
    }
  else if (ans == 'd')
    {
      puts("Item NOT added");
    }
  else
    {
      insert_or_update(tree, name, description, price, shelf_name, num_items);
      puts("edit edit edit edit");
      //edit_shelf_IO_aux(tree, name);
    }
}


void remove_shelf_IO(tree_root *tree)
{
  int low = 0;
  int high = 20;
  int total = total_items(TreeRoot, 0);
  print_warehouse(tree, 0, 0, 20);
  char ans;
  node* item;

  
  while (true)
    {
      if (total > 20)
	{
	  ans = ask_alt("\nWhat would you like to do? [r]emove an item\n [n]ext 20 items\n [e]xit", "rne");
	}
      else
	{
	  ans = ask_alt("\nWhat would you like to do?\n [r]emove an item\n [e]xit", "re");
	}
      if (ans == 'n')
	{
	  low = low + 20;
	  high = high + 20;
	  int total = print_tree(TreeRoot, 0, low, high); 
	}
      else if (ans == 'r')
	{
	  item = ask_item(tree);
	    
	  if (ask_yn("Are you sure you would like to remove this item? y/n"))
	    {
	      remove_node(tree, item);
	      total = total - 1;
	    }
	}
      else break;
    }
  print_line();
  return;
}


/*
void edit_shelf_IO_aux(warehouse* warehouse_list, shelf* choosed_shelf) 
{
  bool cont = true;
  
  char* name = get_name(choosed_shelf);
  char* description = get_description(choosed_shelf);
  int price = get_price(choosed_shelf);
  char* shelf_name = get_shelf_name(choosed_shelf);
  int num_items = get_num_items(choosed_shelf);
  
  while (cont_edit)
    {
      edit_shelf(warehouse_list, choosed_shelf, name, description, price, shelf_name, num_items);
      puts("\n-----EDIT ITEM-------------");
      print_box_shelf_name(name, description, price, shelf_name, num_items);
      int edit = ask_int_q("What would you like to edit?", 1, 5);
  
      switch (edit)
	{
	case 1: {
	  print_name(choosed_shelf);
	  name = ask_str_q("\nNew name: ");} break;
	case 2: {
	  print_description(choosed_shelf);
	  description = ask_str_q("\nNew description: ");} break;
	case 3: {
	  print_price(choosed_shelf);
	  price = ask_int_q("\nNew price", 1, 99999999);} break;
	case 4: {
	  print_shelf_name(choosed_shelf);
	  shelf_name = ask_str_q("\nNew shelf number: ");
	  shelf_name = fix_shelf_name(warehouse_list, shelf_name);} break;
	case 5: {
	  print_num_items(choosed_shelf);
	  num_items = ask_int_q("\nNew num_items: ", 1, 99999999);} break;
	default: puts("defaaaauultttt");
	}
      cont_edit = ask_yn("Continue edit this item? y/n ");
        
    }
  bool save_ware = ask_yn("Save this ware? y/n");
  if (save_ware)
    {
      edit_shelf(warehouse_list, choosed_shelf, name, description, price, shelf_name, num_items);
      puts("Item successfully updated");
    }
    else
      {
	puts ("Last edit NOT saved");
      }
}

*/

void edit_shelf_IO(tree_root * tree)
{
  bool continue_edit = true;

  int low = 0;
  int high = 20;
  int total = total_items(TreeRoot, 0);
  node* item;
  char answer;
  printf("\n-------- EDIT AN ITEM --------------\n" );     

  while (continue_edit)
    {
      print_warehouse(tree, 0 , low, high);
      print_line();

      if (total < 20)
	{
	  answer = ask_alt("\nWhat would you like to do? \n [c]hoose an item to edit\n [s]ee next 20 items (not available)\n [e]xit and go back to main menu", "ce");
	}
      else
	{
	  answer = ask_alt("\nWhat would you like to do? \n [c]hoose an item to edit\n [s]ee next 20 items\n [e]xit and go back to main menu", "cse");
	}

      
      if (answer == 'c')
	{
	  item = ask_item(tree);
	  puts("Edit edit edit edit");
	  //edit_item_aux
	  continue_edit = ask_yn("Edit another item? y/n");
	}
      else if (answer == 's')
	{
	  low = low + 20;
	  high = high + 20;
	  //continue;
	}
      else // (answer == 'e')
	{
	  print_line();
	  return;
	}	
    }  
}

/*
void undo_action_IO(warehouse* warehouse_list)
{
  bool answer = ask_yn("Are you sure you would like to undo your last action? y/n");
  if (answer)
    {
      undo_action(warehouse_list);
    }
}

*/
bool exit_warehouse()
{
  bool ans = ask_yn("Are you sure you would like to exit the warehouse? y/n");

  return ans;
}


// PRINT FUNCTIONS -----------------------------------

void print_warehouse_IO(tree_root* tree)
{
printAll;
}
/* shelf *tmp_shelf = NULL;
  shelf *shelf = NULL;
  int index;
  int page = 0;
  char answer;
  printf("\n--------------------------------");
  printf("\n\tThe warehouse\n\n");

  while(true)
    {
      if(warehouse_empty(warehouse_list))
	{
	  printf("Warehouse is empty!\n");
	  return;
	}
  
      shelf = print_20(warehouse_list, shelf);
      printf("\n--------------------------------");

      if (shelf == NULL)
	{
	  answer = ask_alt("\nWhat would you like to do?\n [s]how an item\n [n]ext 20 items (not available)\n [e]xit", "se");
	}
      else
	{
	  answer = ask_alt("\nWhat would you like to do?\n [s]how an item\n [n]ext 20 items\n [e]xit", "sne");
	}
      
      if (answer == 's')
	{
	  index = ask_index(warehouse_list, page);
	  if (index == 0) break;
	  tmp_shelf = get_shelf(warehouse_list, index);
	  print_box_shelf2(tmp_shelf);
	}
      else if (answer == 'n')
	{
	  page = page +1;
	  shelf = print_20(warehouse_list, shelf);
	  continue;
	}
      else
	{
	  break;
	}
    }
}

void print_cart(tree* tree, cart* cart)
{
  printf("This is your shopping cart");
  print_line();
  printf("shopping cart woho");
  print_line();
  } 

shelf * print_20(struct warehouse *warehouse_list, struct shelf *shelf_start)
{
  shelf* shelf = NULL;
  
  //If we are to start from the begining of the warehouse
  if(shelf_start == NULL)
    {
      shelf = get_first(warehouse_list);
    }
  else
    {
      shelf = shelf_start;
    }
  
  for(int i = 0; i < 20; ++i)
    {
      printf("%d. ", i+1);
      printf("%s", get_name(shelf));
      printf("\n");
      
      shelf = get_next_shelf(shelf);
      if(shelf == NULL)
	{
	  break;
	}
    }
  return shelf;
} */

void print_add_shelf(char *name, char *description, int price, char *shelf_name, int num_items)
{
  printf("\n\n");
  printf("\tYour new item\n");
  print_box_shelf(name, description, price, shelf_name, num_items);
}

void print_box_shelf(char *name, char *description, int price, char *shelf_name, int num_items)
{
  printf("=====\t\t\t=====\n");
  printf(" Name\t\t\t%s\n", name);
  printf(" Description\t\t%s\n", description);
  printf(" Price\t\t\t%d\n", price);
  printf(" Shelf number\t\t%s\n", shelf_name);
  printf(" Number of items\t%d\n", num_items);
  printf("=====\t\t\t=====\n\n");
}
/*
void print_box_shelf2(shelf* shelf)
{
  char *name = get_name(shelf);
  char *description = get_description(shelf);
  int price = get_price(shelf);
  char *shelf_name = get_shelf_name(shelf);
  int num_items = get_num_items(shelf);
  print_box_shelf(name, description, price, shelf_name, num_items);
}
*/
void print_box_shelf_name(char *name, char *description, int price, char *shelf_name, int num_items)
{
  printf("=====\t\t\t=====\n");
  printf("1. Name\t\t\t%s\n", name);
  printf("2. Description\t\t%s\n", description);
  printf("3. Price\t\t\t%d\n", price);
  printf("4. Shelf number\t\t%s\n", shelf_name);
  printf("5. Number of items\t%d\n", num_items);
  printf("=====\t\t\t=====\n\n");
}

void print_name(node *node)
{
  printf("Name:\t\t%s\n", get_name(node));
}

void print_description(node *node)
{
  printf("Description:\t%s\n", get_description(node));
}
	    
void print_price(node *node)
{
  printf("Price:\t\t%d kr\n", get_price(node));
}
	  
void print_shelf_name(node *node)
{
  printf("Shelf number:\t%s\n", get_shelf_name(node));
}
	   
void print_num_items(node *node)
{
  printf("Number of items:\t%d\n", get_amount(node));
}
