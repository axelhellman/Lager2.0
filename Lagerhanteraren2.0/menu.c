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
  bool cont = false;
  tree_root * tree = create_new_tree();
  insert_or_update(tree, "Gurka", "grön", 11, "A1", 1);
  insert_or_update(tree, "Häst", "fulsfdkj", 34, "K5", 1);
  insert_or_update(tree, "Lars", "grön", 2, "F2", 1);
 
  insert_or_update(tree, "Berg", "högt", 10000, "G34", 3);
 
  insert_or_update(tree, "Danne", "skäggig", 1, "E2", 1);
  insert_or_update(tree, "Gös", "skäggig", 1, "E3", 1);
  insert_or_update(tree, "Apa", "skäggig", 1, "E4", 1);
 
   
  printtest(find_node(TreeRoot, "Gurka"));
  puts("Tree now");
  print_tree(TreeRoot);

  puts("removes");
  remove_node(tree, "Häst");
  puts("removed");
  puts("New tree");
  print_tree(TreeRoot);

  

  /*
  insert_or_update(tree, "Gurka", "grön", 33, "A3", 3);
  insert_or_update(tree, "Gurka", "grön", 66, "A6", 6);
  insert_or_update(tree, "Gurka", "grön", 44, "A4", 4);
  insert_or_update(tree, "Gurka", "grön", 55, "A5", 5);
  insert_or_update(tree, "Gurka", "grön", 22, "A2", 2); */
    
  /*
  puts("shelfs");
  
  node* gurknode = find_node(TreeRoot, "Gurka");
  puts("1");
  if(gurknode == NULL) puts("gurknode null");

  list* gurklist = get_list(gurknode);
  puts("2");
  if(gurklist == NULL) puts("gurklistnull");

  
  linked_list_node *gurkllnode = get_ll_node(gurklist);
  puts("3");
  if(gurkllnode == NULL) puts("gurkllnode null");


  print_shelfs(gurkllnode); 
  puts("end of shelfs"); */
  while (!cont)
    {
      print_main_menu();

      int answer;
      answer = ask_int_q("\nWhat would you like to do?", 0, 6);

      switch (answer)
	{
	case 1:
	  add_ware_IO(tree);
	  break;

	case 2:
	  remove_shelf_IO(tree);
	  break;

	case 3:
	  edit_shelf_IO(tree);
	  break;

	case 4:
	  puts("Undo");//undo_action_IO(warehouse_list);
	  break;

	case 5:
	  print_tree(TreeRoot);
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
  printf("destroys tree");
  //destroy_tree(tree);
}
