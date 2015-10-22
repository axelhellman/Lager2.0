#include "IO.h"
#include "tree.h"

void print_name(node *node, bool number);
void print_description(node *node, bool number);	    
void print_price(node *node, bool number);	  
void print_shelf_name(node *node, bool number);	   
void print_amount(node *node, bool number);
void print_box(node* n, bool numbers);

void edit_item_IO_aux(root* root, node* n);

void add_item_to_cart_IO()
{
  // print_cart(); //not_implemented
  char answer = ask_alt("What would you like to do?\n [c]hoose an item to put in cart\n [n]ext page\n [e]xit", "cne");
  printf("Your choice: %c", answer);
}

void add_ware_IO(root *root)
{
  puts("\n----- ADD AN ITEM --------------------");
  char* name;
  char* description;
  int price;
  char* shelf_name; 
  int amount;
  node *node;
  char ans;

  while(true)
    {
      name = AskName;
      if (node_exists(Warehouse, name))
	{
	  printf("\nThat item already exists. What would you like to do?\n");
	  ans = ask_alt(" [e]dit existing item\n [c]hoose another name", "ec");
	}
      else break;
      
      if (ans == 'e')
	{
	  edit_item_IO_aux(root, find_node(Top(Warehouse), name));
	  return;
	}
      //else  (ans == 'c') continue; 
    }
  
  description = ask_description();
  price = ask_price();
  shelf_name = ask_shelf_name(Warehouse);
  amount = ask_amount();
  
  print_line();
  insert_or_update(Warehouse, name, description, price, shelf_name, amount);

  node = find_node(Top(Warehouse), name);
  printf("\n\tYour new item:");
  print_box(node, WithoutNumbers);

  ans = ask_alt("[s]ave this item / [d]on't save / [e]dit", "sde");
  if  (ans == 's')
    {
      printf("\n%s added to the warehouse!\n", name);
    }
  else if (ans == 'd')
    {
      remove_node(root, node);
      puts("Item NOT added");
    }
  else
    {
      puts("edit edit edit edit");
      edit_item_IO_aux(root, find_node(Top(Warehouse), name));
    }
}


void remove_item_IO(root *root)
{
  int low = 0;
  int high = ItemsPerPage;
  int total = total_items(Top(Warehouse), 0);
  char ans;
  node* item;

  while (true)
    {
      print_warehouse(Warehouse, low, high);
      if (total > high)
	{
	  ans = ask_alt("\nWhat would you like to do?\n [r]emove an item\n [n]ext page\n [e]xit", "rne");
	}
      else
	{
	  ans = ask_alt("\nWhat would you like to do?\n [r]emove an item\n [e]xit", "re");
	}
      if (ans == 'n')
	{
	  low = low + ItemsPerPage;
	  high = high + ItemsPerPage;
	}
      else if (ans == 'r')
	{
	  item = ask_item(Warehouse);
	    
	  if (ask_yn("Are you sure you would like to remove this item? y/n"))
	    {
	      remove_node(root, item);
	      total = total - 1;
	    }
	  low = 0;
	  high = ItemsPerPage;
	}
      else break;
    }
  print_line();
  return;
}

node* edit_name_IO(root* root, node* item)
{
 print_name(item, WithoutNumbers);
 // char* old_name = get_name(item);
 char *new_name = AskName;
 while (node_exists(Warehouse, new_name))
   {
     printf("\nThat item already exists, choose another name.");
     new_name = AskName;
   }
 change_name(root, item, new_name);
 puts("Name updated!");
 return item;
}

void edit_item_IO_aux(root* root, node* item) 
{
   puts("\n----- EDIT ITEM -------------");
   print_box(item, WithNumbers);
   puts("Waht would you like to edit???????");
   puts("hmmm okay lets change the name");
   edit_name_IO(root, item);
   /* 
  bool cont_edit = true;

  while (cont_edit)
    {
      //edit_shelf(warehouse_list, choosed_shelf, name, description, price, shelf_name, num_items);
      int edit = ask_int_q("What would you like to edit?", 1, 5);
  
      switch (edit)
	{
	case 1: edit_name_IO(tree, item);
	  break;
	case 2: {
	  print_description(item, WithoutNumbers);
	  description = ask_str_q("\nNew description: ");} break;
	case 3: {
	  print_price(item, WithoutNumbers);
	  price = ask_int_q("\nNew price", 1, 99999999);} break;
	case 4: {
	  print_shelf_name(item, WithoutNumbers);
	  shelf_name = ask_str_q("\nNew shelf number: ");
	  shelf_name = fix_shelf_name(warehouse_list, shelf_name);} break;
	case 5: {
	  print_num_items(item, WithoutNumbers);
	  num_items = ask_int_q("\nNew num_items: ", 1, 99999999);} break;
	default: puts("defaaaauultttt");
	}
      cont_edit = ask_yn("Continue edit this item? y/n ");
        
      } */
}


void edit_item_IO(root * root)
{
  bool continue_edit = true;

  int low = 0;
  int high = ItemsPerPage;
  int total = total_items(Top(Warehouse), 0);
  node* item;
  char answer;
  printf("\n-------- EDIT AN ITEM --------------\n" );     

  while (continue_edit)
    {
      print_warehouse(Warehouse, low, high);
      print_line();

      if (total < high)
	{
	  answer = ask_alt("\nWhat would you like to do? \n [c]hoose an item to edit\n [s]ee next page (not available)\n [e]xit and go back to main menu", "ce");
	}
      else
	{
	  answer = ask_alt("\nWhat would you like to do? \n [c]hoose an item to edit\n [s]ee next page\n [e]xit and go back to main menu", "cse");
	}

      
      if (answer == 'c')
	{
	  item = ask_item(Warehouse);
	  puts("Edit edit edit edit");
	  edit_item_IO_aux(root, item);
	  low = 0;
	  high = ItemsPerPage;
	  continue_edit = ask_yn("Edit another item? y/n");
	}
      else if (answer == 's')
	{
	  low = low + ItemsPerPage;
	  high = high + ItemsPerPage;
	}
      else // (answer == 'e')
	{
	  print_line();
	  return;
	}	
    }  
}


void show_warehouse_IO(tree_root* tree)
{
  int low = 0;
  int high = ItemsPerPage;
 
  char answer;
  int total = total_items(Top(tree), 0);
  while(true)
    {
      print_warehouse(tree, low, high);
      if (total < high)
	{
	  answer = ask_alt("\nWhat would you like to do?\n [s]how an item\n [n]ext page (not available)\n [e]xit", "se");
	}
      else
	{
	  answer = ask_alt("\nWhat would you like to do?\n [s]how an item\n [n]ext page\n [e]xit", "sne");
	}
      
      if (answer == 's')
	{
	  node* node = ask_item(tree);
	  print_box(node, WithoutNumbers);
	  low = 0;
	  high = ItemsPerPage;
	}
      else if (answer == 'n')
	{
	  low = low + ItemsPerPage;
	  high = high + ItemsPerPage;
	}
      else break;
    }
}

bool exit_warehouse()
{
  bool ans = ask_yn("Are you sure you would like to exit the warehouse? y/n");
  return ans;
}

// PRINT FUNCTIONS -----------------------------------


/*
void print_cart(tree* tree, cart* cart)
{
  printf("This is your shopping cart");
  print_line();
  printf("shopping cart woho");
  print_line();
  } 

*/
void print_box(node* node, bool numbers)
{
  printf("\n=====\t\t\t=====\n");
  print_name(node, numbers);
  print_description(node, numbers);
  print_price(node, numbers);
  print_shelf_names(node, numbers);
  print_amount(node, numbers);
  printf("=====\t\t\t=====\n\n");
}

void print_name(node *node, bool number)
{
  if (number) printf("1. Name:\t\t%s\n", get_name(node));
  else printf(" Name:\t\t\t%s\n", get_name(node));
}
void print_description(node *node, bool number)
{
  if (number) printf("2. Description:\t\t%s\n", get_description(node));
  else printf(" Description:\t\t%s\n", get_description(node));
}	    
void print_price(node *node, bool number)
{
  if (number) printf("3. Price:\t\t%d kr\n", get_price(node));
  else printf(" Price:\t\t\t%d kr\n", get_price(node));
}	  
void print_shelf_names(node *node, bool number)
{
  if (number) printf("4. Shelf:\t\t");
  else printf(" Shelf:\t\t\t");
  shelf_names(get_ll_node(get_list(node)));
}	   
void print_amount(node *node, bool number)
{
  if (number) printf("5. Amount:\t\t%d\n", get_amount(node));
  else printf(" Amount:\t\t%d\n", get_amount(node));
}
