#include "database.h"
#include "IO.h"

void print_add_shelf(char *name, char *description, int price, char *shelf_num, int num_items);

void print_name(shelf *shelf);
void print_description(shelf *shelf);	    
void print_price(shelf *shelf);	  
void print_shelf_num(shelf *shelf);	   
void print_num_items (shelf *shelf);

void print_box_shelf(char *name, char *description, int price, char *shelf_num, int num_items);
void print_box_shelf2(shelf* shelf);
void print_box_shelf_num(char *name, char *description, int price, char *shelf_num, int num_items);
shelf * print_20(warehouse *warehouse_list, shelf *shelf_start);

void edit_shelf_IO_aux(warehouse* warehouse_list, shelf* choosed_shelf);
char ask_alt(char* question, char* alternatives);

char* strip (char* str)
{
  char* copy = strdup(str);
  int len = strlen (copy);
  for (int i = 0; i<len; ++i)
    {
      if (copy[i] == '\n')
	{
	  copy[i] = '\0';
	  break;
	}
    } 
  return copy; //free??
}

void clear (void)
{
  bool newline_found; 
  do {
    newline_found = getchar() != '\n';
  } while (newline_found);
}

int ask_index(warehouse* warehouse_list, int page)
{
  int answer;
  int index;
  shelf* shelf;
  answer = ask_int_q ("Choose an item. Answer with a number between 1-20. Press 0 to exit.", 0, 20);

  while (true)
    {
      index = page * 20 + answer - 1;
      shelf = get_shelf(warehouse_list, index);
      while (shelf == NULL)
	{
	  answer = ask_int_q("Item doesn't exist, please choose another item", 1, 20);
	  index = page * 20 + answer - 1;
	  shelf = get_shelf (warehouse_list, index);
	}
      break;
    }
  return index;
}

void lower_letter(char* answer, int i)
{
  if (answer[i] == '\0')
    {
      return; 
    }
  else
    {
      answer[i] = tolower(answer[i]);
      lower_letter(answer, i+1);
    }
}
char* ask_str_q (char *question)
{
  char input[256] = "\n";
  while (input[0] == '\n')
    {
      printf("%s\n> ", question);
      fgets(input, sizeof(input), stdin);
    }
  char* answer = strip(input);

  answer[0] = toupper(answer[0]);
  lower_letter(answer, 1);
  
  /* for (int i = 1; i<strlen(answer); ++i)
    {
      answer[i]=tolower(answer[i]);
    } */

  return answer;
}

bool out_of_range(int ok_ans, int low, int high)
{
  if ((ok_ans < low) || (high < ok_ans))
    {
      return true;
    }
  else
    {
      return false;
    }
}

bool only_digits(char* answer)
{
  int ok_ans;
  for (int i=0; i<strlen(answer); i++)
	{
	  ok_ans = isdigit(answer[i]);
	  if (ok_ans == 0 && answer[i]!= '0')
	    {
	      return false;
	    }
	}
  return true;
}

int ask_int_q (char *question, int low, int high)
{
  int ok_ans;
  while (true)
    {
      char input[128] = "\n";
      while (input[0] == '\n')
	{
	  printf("%s\n> ", question);
	  fgets(input, sizeof(input), stdin);
	}
      char* answer = strip (input);
   
      if (strcmp(answer, "0")==0)
	{
	  if (out_of_range(0, low, high))
	    {
	      printf("That's not an option, answer with a number between %d-%d", low, high);
	      question = ".";
	      continue;
	    }
	  else
	    {
	      return 0;
	    }
	}

      if (only_digits(answer) == false)
	{
	  question = "Please answer with digits and nothing else.";
	  continue;
	}

      ok_ans = atoi(answer);

      if (out_of_range(ok_ans, low, high))
	{
	  printf("That's not an option, answer with a number between %d-%d", low, high);
	  question = ".";
	  continue;
	}
      break;
    }
  return ok_ans;
}

int ask_yn(char* question)
{
  char ans = ask_alt(question, "yn");

  if (ans == 'y')
    {
      return 1;}
  else
    {
      return 0;}
}


void print_alt_chars(char* alternatives)
{
  int i;
  printf("That's not an option, please answer ");
  for (i = 0; (i+1) < strlen(alternatives); i++)
    {
      printf("'%c' or ", alternatives[i]);
    }
  printf("'%c'\n> ", alternatives[i]);
}

char ask_alt(char* question, char* alternatives)
{
  char ans;
  printf("%s\n> ", question);
  while(true)
    { 
      ans = getchar();
      clear();
      if (ans == '\n')
       	{
	  print_alt_chars(alternatives);
	  continue;
	}

      for (int i=0; i < strlen(alternatives); i++)
	{
	  if (ans == alternatives[i])
	    {
	      return ans ;
	    }
	}
      print_alt_chars(alternatives);
    }

}

bool check_shelf_ans(char* answer)
{
  if (isalpha(answer[0]))
    {
      if (answer[1]== '\0')
	{
	  return false;
	}
  
      for (int i=1; i<strlen(answer); ++i)
	{
	  if (!(isdigit(answer[i])))
	    {
	      return false;
	    }
	}
      return true;
    }
  return false;
}

char* fix_shelf_num(warehouse* warehouse_list, char* shelf_num)
{
  while (true)
    {
      while (!(check_shelf_ans(shelf_num)))
	{
	  free(shelf_num);
	  shelf_num = ask_str_q("Please answer on the format [A23], [A2], [B34]");
	}

      shelf_num[0] = toupper(shelf_num[0]);
  
      if (is_shelf_taken(warehouse_list, shelf_num))
	{  
	  shelf_num = ask_str_q("That shelf is already taken. Please choose another shelf.");
	}
      else
	{
	  break;
	}
    }
  return shelf_num;
}

void add_item_to_chart_IO()
{
  // print_chart(); //not_implemented
  char answer = ask_alt("What would you like to do?\n [c]hoose an item to put in cart\n [n]ext 20 items\n [e]xit", "cne");
  printf("Your choice: %c", answer);
}

void add_shelf_IO(warehouse *warehouse_list)
{
  puts("\n----- ADD AN ITEM --------------------");
  char* name;
  char* description;
  int price;
  char* shelf_num; 
  int num_items;
  
  name = ask_str_q("Name:");
  description = ask_str_q("Description:");
  price = ask_int_q("Price (kr):", 1, 99999999);
  shelf_num = ask_str_q("Shelf number:");
  shelf_num = fix_shelf_num(warehouse_list, shelf_num);
  num_items = ask_int_q("Number of items:", 1, 99999999);

  puts("---------------------------------");

  print_add_shelf(name, description, price, shelf_num, num_items);

  char ans = ask_alt("[s]ave this item / [d]on't save / [e]dit", "sde");
  if  (ans == 's')
    {
      add_shelf(warehouse_list, name, description, price, shelf_num, num_items);
      printf("\n%s added to the warehouse!\n", name);
    }
  else if (ans == 'd')
    {
      puts("Item NOT added");
    }
  else
    {
      add_shelf(warehouse_list, name, description, price, shelf_num, num_items);
      edit_shelf_IO_aux(warehouse_list, get_last_shelf(warehouse_list));
    }
}


void remove_shelf_IO(warehouse *warehouse_list)
{
  if(warehouse_empty(warehouse_list))
    {
      printf("The warehouse is empty!\n");
      return ;
    }
  
  shelf* shelf = print_20(warehouse_list, NULL);
  char ans = 0;
  int index;
  int page = 0;
  
  while (true)
    {
      if (shelf == NULL)
	{
	  ans = ask_alt("\nWhat would you like to do? [r]emove an item\n [n]ext 20 items\n [e]xit", "rne");
	}
      else
	{
	  ans = ask_alt("\nWhat would you like to do?\n [r]emove an item\n [e]xit", "re");
	}
      if (ans == 'n')
	{
	  page = page +1;
	  shelf = print_20(warehouse_list, shelf);
	}
      else if (ans == 'r')
	{
	  index = ask_index(warehouse_list, page);
	  remove_shelf(warehouse_list, index);
	  break;
	}
      else
	{
	  break;
	}
    }
  return;
}



void edit_shelf_IO_aux(warehouse* warehouse_list, shelf* choosed_shelf) 
{
  int cont = 1;
  
  char* name = get_name(choosed_shelf);
  char* description = get_description(choosed_shelf);
  int price = get_price(choosed_shelf);
  char* shelf_num = get_shelf_num(choosed_shelf);
  int num_items = get_num_items(choosed_shelf);
 
  
  while (cont)
    {
      edit_shelf(warehouse_list, choosed_shelf, name, description, price, shelf_num, num_items); //flyttade hit
      puts("\n-----EDIT ITEM-------------");
      print_box_shelf_num(name, description, price, shelf_num, num_items);
      int edit;
      edit =  ask_int_q("What would you like to edit?", 1, 5);
  
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
	  print_shelf_num(choosed_shelf);
	  shelf_num = ask_str_q("\nNew shelf number: ");
	  shelf_num = fix_shelf_num(warehouse_list, shelf_num);} break;
	case 5: {
	  print_num_items(choosed_shelf);
	  num_items = ask_int_q("\nNew num_items: ", 1, 99999999);} break;
	default: puts("defaaaauultttt");
	}
      cont = ask_yn("Continue edit this item? y/n ");
        
    }
  int ans = ask_yn("Save this ware? y/n");
  if (ans == 1)
    {
      edit_shelf(warehouse_list, choosed_shelf, name, description, price, shelf_num, num_items);
      puts("Item successfully updated");
    }
    else
      {
	puts ("Last edit NOT saved");
      }
}



void edit_shelf_IO(warehouse* warehouse_list)
{
  int continue_edit = 1;

  if(warehouse_empty(warehouse_list))
    {
      printf("The warehouse is empty!\n");
      return;
    }
  
  while (continue_edit)
    {
      shelf *shelf = NULL;
      char answer;
      int index;
      int page = 0;
      printf("\n----- EDIT AN ITEM -----------" );
      printf("\nItems in warehouse:\n");
      shelf = print_20(warehouse_list, shelf);
      puts("------------------------------");

      while(true)
	{

	  if (shelf == NULL)
	    {
	      answer = ask_alt("\nWhat would you like to do? \n [c]hoose an item to edit\n [s]ee next 20 items (not available)\n [e]xit and go back to main menu", "ce");
	    }
	  else
	    {
	      answer = ask_alt("\nWhat would you like to do? \n [c]hoose an item to edit\n [s]ee next 20 items\n [e]xit and go back to main menu", "cse");
	    }
 
	
	  if (answer == 'c')
	    {
	      index = ask_index(warehouse_list, page);
	      shelf = get_shelf(warehouse_list, index);
	      edit_shelf_IO_aux(warehouse_list, shelf);
	      continue_edit = ask_yn("Edit another item? y/n");
	    }

	  else if (answer == 's')
	    {
	      page = page +1;
	      shelf = print_20(warehouse_list, shelf);
	      continue;
	    }

	  else
	    {
	      puts("EXIIIIT");
	      return;
	    }
	}
    }  
}


  
void undo_action_IO(warehouse* warehouse_list)
{
  int answer = ask_yn("Are you sure you would like to undo your last action? y/n");
  if (answer)
    {
      undo_action(warehouse_list);
    }
}


int exit_warehouse()
{
  char ans;
  ans = ask_yn("Are you sure you would like to exit the warehouse? y/n");

  if (ans == 1) 
    {
      return 0; //exit
    }
  else
    {
      return 1; //stay in program
    }
}


// PRINT FUNCTIONS -----------------------------------

void print_warehouse(warehouse *warehouse_list)
{
  shelf *tmp_shelf = NULL;
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
}
void print_add_shelf(char *name, char *description, int price, char *shelf_num, int num_items)
{
  printf("\n\n");
  printf("\tYour new item\n");
  print_box_shelf(name, description, price, shelf_num, num_items);
}

void print_box_shelf(char *name, char *description, int price, char *shelf_num, int num_items)
{
  printf("=====\t\t\t=====\n");
  printf(" Name\t\t\t%s\n", name);
  printf(" Description\t\t%s\n", description);
  printf(" Price\t\t\t%d\n", price);
  printf(" Shelf number\t\t%s\n", shelf_num);
  printf(" Number of items\t%d\n", num_items);
  printf("=====\t\t\t=====\n\n");
}

void print_box_shelf2(shelf* shelf)
{
  char *name = get_name(shelf);
  char *description = get_description(shelf);
  int price = get_price(shelf);
  char *shelf_num = get_shelf_num(shelf);
  int num_items = get_num_items(shelf);
  print_box_shelf(name, description, price, shelf_num, num_items);
}

void print_box_shelf_num(char *name, char *description, int price, char *shelf_num, int num_items)
{
  printf("=====\t\t\t=====\n");
  printf("1. Name\t\t\t%s\n", name);
  printf("2. Description\t\t%s\n", description);
  printf("3. Price\t\t\t%d\n", price);
  printf("4. Shelf number\t\t%s\n", shelf_num);
  printf("5. Number of items\t%d\n", num_items);
  printf("=====\t\t\t=====\n\n");
}

void print_name(shelf *shelf)
{
  printf("Name:\t\t%s", get_name(shelf));
}

void print_description(shelf *shelf)
{
  printf("Description:\t%s", get_description(shelf));
}
	    
void print_price(shelf *shelf)
{
  printf("Price:\t\t%d kr", get_price(shelf));
}
	  
void print_shelf_num(shelf *shelf)
{
  printf("Shelf number:\t%s", get_shelf_num(shelf));
}
	   
void print_num_items(shelf *shelf)
{
  printf("Number of items:\t%d", get_num_items(shelf));
}
