#include "IO.h"
//#include "tree.h" //behövs detta??

void print_name(node *node, bool number);
void print_description(node *node, bool number);	    
void print_price(node *node, bool number);	  
void print_shelf_name(node *node, bool number);	   
void print_amount(node *node, bool number);
void print_box(node* n, bool numbers);

void edit_item_IO_aux(root* root, node* n);

void add_item_to_cart_IO(root* root)
{
  printCart();
  printWarehouse();
bool add_more;
  char answer = ask_alt("What would you like to do?\n [c]hoose an item to put in cart\n [e]xit", "ce");
  if (answer == 'e') add_more = false;
  else add_more = true;

  while (add_more)
    {
      node* n = ask_item(Warehouse);
      print_name(n, WithoutNumbers);
      print_amount(n, WithoutNumbers);
      int to_cart = ask_int_q("How many would you like add to cart?", 1, get_amount(n));

    }
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
  shelf_name = ask_shelf_name(Warehouse, NULL);
  amount = ask_amount();
  
  print_line();
  insert_new_node(Warehouse, name, description, price, shelf_name, amount);

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
      print_tree(root, Warehouse, low, high);
      if (total <= high)
	{
	  ans = ask_alt("\nWhat would you like to do?\n [r]emove an item\n [e]xit", "re");
	}
      else
	{
	  ans = ask_alt("\nWhat would you like to do?\n [r]emove an item\n [n]ext page\n [e]xit", "rne");
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

node* edit_description_IO(root* root, node* item)
{
  char* new_description = ask_description(item);
  change_description(item, new_description);
  puts("Description updated");
  return item;
}

node* edit_price_IO(root* root, node* item)
{
  int new_price = ask_price();
  change_price(root, item, new_price);
  return item;
}
node* edit_shelfname_IO(root* root, node* item)
{
  print_shelf_names(item, WithoutNumbers);
  char* new_shelf_name = NULL;
  char ans = ask_alt("[e]dit a shelfname // [a]dd an new shelf // [r]emove a shelf", "ear");
  if (ans == 'e')
    {
      shelf* shelf = ask_shelf(Warehouse, item);
      new_shelf_name = ask_shelf_name(Warehouse, item);
      change_shelf_name(item, shelf, new_shelf_name);	
    }
  else if (ans == 'a')
    {
      new_shelf_name = ask_shelf_name(Warehouse, item);
      int amount = ask_amount();
      add_shelf(item, new_shelf_name, amount);
    }

  else // ans == 'r'
    {
      puts("Remove shelf (not avalible yet)");
      //remove shelf
    }
  puts("Item with updated shelf names");
  print_shelf_names(item, WithoutNumbers);
  return item;
}

void edit_item_IO_aux(root* root, node* item) 
{
   puts("\n----- EDIT ITEM -------------");
  

  bool cont_edit = true;

  while (cont_edit)
    {
      print_box(item, WithNumbers);
      int edit = ask_int_q("What would you like to edit?", 1, 5);
  
      switch (edit)
	{
	case 1: item = edit_name_IO(root, item);
	  break;
	case 2: item = edit_description_IO(root, item); break;
	case 3: item = edit_price_IO(root, item); break;
	case 4: item = edit_shelfname_IO(root, item);
	  break;
	case 5: {
	  print_amount(item, WithoutNumbers);
	  /*num_items = ask_int_q("\nNew num_items: ", 1, 99999999); */} break;
	default: puts("defaaaauultttt");
	}
      cont_edit = ask_yn("Continue edit this item? y/n ");
        
      }
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
      print_tree(root, Warehouse, low, high);
      print_line();

      if (total <= high)
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


void show_warehouse_IO(root* root, tree_root* tree)
{
  int low = 0;
  int high = ItemsPerPage;
 
  char answer;
  int total = total_items(Top(tree), 0);
  printf("total: %d", total);
  while(true)
    {
      print_tree(root, tree, low, high);
      printf("total: %d\thigh: %d\n", total, high);
      if (total <= high)
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
  printf("\n=====\t\t=====\n");
  print_name(node, numbers);
  print_description(node, numbers);
  print_price(node, numbers);
  print_shelf_names(node, numbers);
  print_amount(node, numbers);
  printf("=====\t\t=====\n\n");
}

void print_name(node *node, bool number)
{
  if (number) printf("1. Name\t\t%s\n", get_name(node));
  else printf(" Name:\t\t%s\n", get_name(node));
}
void print_description(node *node, bool number)
{
  if (number) printf("2. Description\t%s\n", get_description(node));
  else printf(" Description:\t%s\n", get_description(node));
}	    
void print_price(node *node, bool number)
{
  if (number) printf("3. Price\t%d kr\n", get_price(node));
  else printf(" Price:\t\t%d kr\n", get_price(node));
}	  
void print_shelf_names(node *node, bool number)
{
  if (number) printf("4. Shelf\t");
  else printf(" Shelf:\t\t");
  shelf_names(get_first(get_list(node)));
}	   
void print_amount(node *node, bool number)
{
  if (number) printf("5. Amount\t%d\n", get_amount(node));
  else printf(" Amount:\t%d\n", get_amount(node));
}
