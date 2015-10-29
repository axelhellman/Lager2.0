#include "smallfunc.h"
#include "tree.h"
#include "list.h"

// ----- HIDDEN FUNCTIONS ---------------------------
void strip(char* str);
void clear(void);
bool check_shelf_ans(char* answer);
void print_alt_chars(char* alternatives);
bool out_of_range(int ok_ans, int low, int high);
bool only_digits(char* answer);
char* fix_shelf_name(tree_root * tree, node* n, char* shelf_name);
// -------------------------------------------------
// -------------------------------------------------


node* ask_item(tree_root *tree)
{
  char* question = "Name:";
  char* name = ask_str_q(question);
  while (! find_node(Top(tree), name))
    {
      free(name);
      question = "That item doesn't exists in the warehouse, please choose another one.";
      name = ask_str_q(question);
    }
  node* n = find_node(Top(tree), name);
  free(name);
  return n;
}
char* ask_description(node* n)
{
  if (n == NULL) return (ask_str_q("Description:"));
  else return(ask_str_q("New description:"));
}

int ask_price(node* n)
{
  if (n == NULL) return (ask_int_q("Price (kr):", 1, 99999999));
  else return (ask_int_q("New price (kr):", 1, 99999999));
}
void* ask_shelf(tree_root* tree, node* n)
{
  char* shelf_name = ask_str_q("Which shelf?");
  shelf_name = fix_shelf_name(tree, n, shelf_name);
     while (get_shelf(n, shelf_name) == NULL)
	{
	  free(shelf_name);
	  printf("\nThat's not a shelf...\n");
	  shelf_name = ask_shelf_name(tree, n);
	}
     shelf* s = get_shelf(n, shelf_name);
     free(shelf_name);
     return s;
}

char* ask_shelf_name(tree_root* tree, node* n)
{
  char* shelf_name = ask_str_q("Shelf name:");
  shelf_name = fix_shelf_name(tree, n, shelf_name);
  return shelf_name;
}

int ask_amount()
{
  return (ask_int_q("Amount:", 1, 9999));
}

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
      while (input[0] == '\n' || input[0] == ' ' || input[0] == '\0')
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

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------

char* fix_shelf_name(tree_root *tree, node* n, char* shelf_name)
{
  while (true)
    {
      while (!(check_shelf_ans(shelf_name)))
	{
	  free(shelf_name);
	  shelf_name = ask_str_q("Please answer on the format [A23], [A2], [B34]");
	}
      shelf_name[0] = toupper(shelf_name[0]);
      
      if (n != NULL && shelf_is_taken_list(get_list(n), shelf_name))
	{
	  return shelf_name;
	}
      else if (shelf_is_taken(Top(tree), shelf_name))
	{
	  free(shelf_name);
	  shelf_name = ask_str_q("That shelf is already taken. Please choose another shelf.");
	}
      else break;    
    }
  return shelf_name;
}


bool check_shelf_ans(char* answer)
{
  if (isalpha(answer[0]))
    {
      if (answer[1]== '\0') return false;
  
      for (int i=1; i<strlen(answer); ++i)
	{
	  if (!(isdigit(answer[i]))) return false;
	}
      return true;
    }
  return false;
}


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
  return;
}

void clear (void)
{
  bool newline_found; 
  do {
    newline_found = getchar() != '\n';
  } while (newline_found);
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
      return true;
  else
      return false;
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

// --------------------------------------------------------------
// --------------------------------------------------------------
// -----------PRINT FUNCTIONS -----------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------


void print_line(void)
{
  puts("--------------------------------------");
}

void print_box(node* node, bool numbers)
{
  printf("\n=====\t\t=====\n");
  if (node == NULL) //|| list_is_empty(node))
    {
      puts("Item doesn't exists");
    }
  else
    {
      print_name(node, numbers);
      print_description(node, numbers);
      print_price(node, numbers);
      print_shelf_names(node, numbers);
      print_amount(node, numbers);
    }
  printf("=====\t\t=====\n\n");
}

void print_name(node *node, bool number)
{
  if (number) printf("1. Name\t\t%s\n", get_key(node));
  else printf(" Name:\t\t%s\n", get_key(node));
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
