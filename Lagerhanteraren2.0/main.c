#include "menu.h"

/* void test ()
{
  warehouse *warehouse_list = new_warehouse();

  printf("Add\n");
  add_shelf(warehouse_list, "Karro", "cool tjej", 999, "a2", 1);
  add_shelf(warehouse_list, "Tim", "stark kille", 9999999, "a3", 1);
  add_shelf(warehouse_list, "katt", "svart", 300, "k1", 3);
  
  add_shelf(warehouse_list, "hund", "brun och lurvig", 500, "h1", 2);
  add_shelf(warehouse_list, "gurka", "grön", 15, "g2", 17);
  add_shelf(warehouse_list, "tomat", "röd och möglig", 7, "t2", 13);
  

  print_warehouse(warehouse_list);

  printf("Undo\n");
  undo_action(warehouse_list);

  print_warehouse(warehouse_list);

  printf("Remove\n");
  remove_shelf(warehouse_list, 1);

  print_warehouse(warehouse_list);

  printf("Undo\n");
  undo_action(warehouse_list);

  print_warehouse(warehouse_list);

  printf("Edit\n");
  edit_shelf(warehouse_list,
	     get_shelf(warehouse_list, 1),
	     "Timtim",
	     "Cool kille som inte sar skriver.",
	     1000000,
	     "B27",
	     1337);

  print_shelf(get_shelf(warehouse_list, 1));
  
  print_warehouse(warehouse_list);

  printf("Undo\n");
  undo_action(warehouse_list);

  print_shelf(get_shelf(warehouse_list, 1));
  
  print_warehouse(warehouse_list);

  printf("Destroy\n");
  destroy_warehouse(warehouse_list);
}
*/


int main(void)
{
  //test();
  puts("\nWelcome to our warehouse program!");
  main_menu();
  return 0;
}
