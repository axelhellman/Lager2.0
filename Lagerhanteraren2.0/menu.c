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

  insert_new_ware(Warehouse, "Gurka", "grön", 11, "A11", 11);
  insert_new_ware(Warehouse, "Lampa", "skäggig", 1, "K8", 1);
  insert_new_ware(Warehouse, "Häst", "fulsfdkj", 34, "K5", 1);
  insert_new_ware(Warehouse, "Lars", "grön", 2, "F2", 1);
  insert_new_ware(Warehouse, "Berg", "högt", 10000, "G34", 3);
  insert_new_ware(Warehouse, "Igelkott", "högt", 10000, "G33", 3);
  insert_new_ware(Warehouse, "Danne", "skäggig", 1, "E2", 1);
  insert_new_ware(Warehouse, "Gös", "skäggig", 1, "E3", 1);
  insert_new_ware(Warehouse, "Apa", "skäggig", 1, "E4", 1);
  insert_new_ware(Warehouse, "Iller", "skäggig", 1, "K7", 1);
  insert_new_ware(Warehouse, "Hej hej", "skäggig", 1, "K9", 1);

  node* gurka = find_node(Top(Warehouse), "Gurka");
  add_shelf(gurka, "A5", 5);
  add_shelf(gurka, "A3", 3);
  add_shelf(gurka, "A6", 6);
  add_shelf(gurka, "A4", 4);
  add_shelf(gurka, "A5", 5);
  add_shelf(gurka, "A2", 2);
  add_shelf(gurka, "A5", 5);
   

  puts("shelves");
  print_shelf_names(gurka, WithoutNumbers);
  print_line();
  gurka = remove_amount(gurka, 11);
  print_shelf_names(gurka, WithoutNumbers);
  print_line(); 
  
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
  printWarehouse();

  puts("removes");
  remove_node(root, find_node(Top(Warehouse), "Häst"));
  puts("removed");
  puts("New Warehouse");
  printWarehouse();
  print_line();
  

 
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
	  show_warehouse_IO(root, Warehouse);
	  break;

	case 6:
	  add_item_to_cart_IO(root);
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
