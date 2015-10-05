#include "menu.h"
#include "tree.h"


void print_main_menu()
{
  puts("\n----- MAIN MENU ----------------------");
  puts("--------------------------------------\n");
  puts("1. Add an item");
  puts("2. Remove an item");
  puts("3. Edit an item");
  puts("4. Undo the last action");
  puts("5. List all items in the database");
  puts("6. Add items to cart");
  puts("0. Exit program");
  //create_new_node("Katt", "svart", 900, "A23", 2);


}

void main_menu()
{

  warehouse *warehouse_list = new_warehouse();
  
  int cont = 1;
  
  while (cont)
    {
      print_main_menu();

      int answer;
      answer = ask_int_q("\nWhat would you like to do?", 0, 6);

      switch (answer)
	{
	case 1:
	  add_shelf_IO(warehouse_list);
	  break;

	case 2:
	  remove_shelf_IO(warehouse_list);
	  break;

	case 3:
	  edit_shelf_IO(warehouse_list);
	  break;

	case 4:
	  undo_action_IO(warehouse_list);
	  break;

	case 5:
	  print_warehouse(warehouse_list);
	  break;

	case 6:
	  puts("Fix menu for ADD A ITEM TO CART");
	  //add_item_to_chart_IO();
	  break;

	case 0:
	  {
	    cont = exit_warehouse();
	  }
	  break;
	default: puts ("defaaaaauuuuuult");	    
	}
    }

  //destroy_tree(tree);
}
