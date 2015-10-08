#include "smallfunc.h"

void strip(char* str);
void clear(void);
bool check_shelf_ans(char* answer);
void print_alt_chars(char* alternatives);
bool out_of_range(int ok_ans, int low, int high);
bool only_digits(char* answer);
// void lower_letter(char* answer, int i);


char* ask_name()
{
  return (ask_str_q("Name:"));
}

char* ask_description()
{
  return (ask_str_q("Description:"));
}

int ask_price()
{
  return (ask_int_q("Price (kr):", 1, 99999999));
}

char* ask_shelf_name()
{
  char* shelf_name = ask_str_q("Shelf number:");
  //shelf_num = fix_shelf_num(warehouse_list, shelf_num);
  return shelf_name;
}

int ask_num_items()
{
  return (ask_int_q("Number of items:", 1, 99999999));

}
/*
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
	  answer = ask_int_q("Item doesn't exist, please choose another item. Press 0 to exit.", 0, 20);
	  index = page * 20 + answer - 1;
	  shelf = get_shelf (warehouse_list, index);
	}
      break;
    }
  return index;
}
*/

char* ask_str_q (char *question)
{
  char input[256] = "\n";
  while (input[0] == '\n')
    {
      printf("%s\n> ", question);
      fgets(input, sizeof(input), stdin);
    }
  strip(input);
  
  input[0] = toupper(input[0]);

  for (int i = 1; i<strlen(input); ++i)
    {
      input[i]=tolower(input[i]);
    }
  char* answer = strdup(input);
  return answer;
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
      strip (input);
   
      if (strcmp(input, "0")==0) 
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

      if (only_digits(input) == false)
	{
	  question = "Please answer with digits and nothing else.";
	  continue;
	}

      ok_ans = atoi(input);

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

bool ask_yn(char* question)
{
  char ans = ask_alt(question, "yn");

  if (ans == 'y')
    {
      return true;}
  else
    {
      return false;}
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

/*
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



*/


// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------

void strip (char* str)
{
  int len = strlen (str);
  for (int i = 0; i<len; ++i)
    {
      if (str[i] == '\n')
	{
	  str[i] = '\0';
	  break;
	}
    } 
  return; //free??
}

void clear (void)
{
  bool newline_found; 
  do {
    newline_found = getchar() != '\n';
  } while (newline_found);
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

void print_line(void)
{
  puts("--------------------------------------");
}
/* void lower_letter(char* answer, int i)
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
    }*/
