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
void test(char** name)
{
  *name = "<3Tobbe";
  return;
}
void main_menu()
{
  bool cont = false;
  root* root = create_new_root();
  //Warehouse_root * warehouse = create_new_Warehouse();
  insert_or_update(Warehouse, "Gurka", "grön", 11, "A1", 1);
  insert_or_update(Warehouse, "Lampa", "skäggig", 1, "K8", 1);
  insert_or_update(Warehouse, "Häst", "fulsfdkj", 34, "K5", 1);
  insert_or_update(Warehouse, "Lars", "grön", 2, "F2", 1);
  insert_or_update(Warehouse, "Berg", "högt", 10000, "G34", 3);
  insert_or_update(Warehouse, "Igelkott", "högt", 10000, "G33", 3);
  insert_or_update(Warehouse, "Danne", "skäggig", 1, "E2", 1);
  insert_or_update(Warehouse, "Gös", "skäggig", 1, "E3", 1);
  insert_or_update(Warehouse, "Apa", "skäggig", 1, "E4", 1);
  insert_or_update(Warehouse, "Iller", "skäggig", 1, "K7", 1);
  insert_or_update(Warehouse, "Hej hej", "skäggig", 1, "K9", 1);

  insert_or_update(Warehouse, "Gurka", "grön", 33, "A3", 3);
  insert_or_update(Warehouse, "Gurka", "grön", 66, "A6", 6);
  insert_or_update(Warehouse, "Gurka", "grön", 44, "A4", 4);
  insert_or_update(Warehouse, "Gurka", "grön", 55, "A5", 5);
  insert_or_update(Warehouse, "Gurka", "grön", 22, "A2", 2);
  
  /*
  char** name = calloc(10, sizeof(char));
  *name = "Karro";
  printf("%s", *name);
  test(name);
  printf("%s\n\n", *name);

  //  free(*name);
  free(name);
  */
  puts("Warehouse now");
  printAll(Warehouse);

  puts("removes");
  remove_node(root, find_node(Top(Warehouse), "Häst"));
  puts("removed");
  puts("New Warehouse");
  printAll(Warehouse);
  print_line();
  
  puts("shelves");
  print_shelf_names(find_node(Top(Warehouse), "Gurka"), WithoutNumbers);
  puts("end of shelves");
 
  while (!cont)
    {
      print_main_menu();

      int answer;
      answer = ask_int_q("\nWhat would you like to do?", 0, 6);

      switch (answer)
	{
	case 1:
	  add_ware_IO(root);
	  break;

	case 2:
	  remove_item_IO(root);
	  break;

	case 3:
	  edit_item_IO(root);
	  break;

	case 4:
	  puts("Undo is not available");
	  break;

	case 5:
	  show_warehouse_IO(Warehouse);
	  break;

	case 6:
	  add_item_to_cart_IO();
	  break;

	case 0:
	  {
	    cont = exit_warehouse();
	  }
	  break;
	default: puts ("defaaaaauuuuuult");	    
	}
    }
  printf("destroys Warehouse");
  //destroy_Warehouse(Warehouse); 
}
