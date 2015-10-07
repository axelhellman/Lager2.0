#include "menu.h"


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
  
}

void main_menu()
{

 tree_root * tree = create_new_tree();
  
  bool cont = true;
  
  while (cont)
    {
      print_main_menu();

      int answer;
      answer = ask_int_q("\nWhat would you like to do?", 0, 6);

      switch (answer)
	{
	case 1:
	  add_shelf_IO(tree);
	  break;

	case 2:
	  puts("Remove");//remove_shelf_IO(warehouse_list);
	  break;

	case 3:
	  edit_shelf_IO(tree);
	  break;

	case 4:
	  puts("Undo");//undo_action_IO(warehouse_list);
	  break;

	case 5:
	  print_tree(tree -> top_node);
	  break;

	case 6:
	  add_item_to_chart_IO();
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
