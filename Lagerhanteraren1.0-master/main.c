#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

#define NAME_LENGTH 20
#define DESC_LENGTH 100
#define SHELF_LENGTH 4

struct goods
{
  char name[NAME_LENGTH];
  char description[DESC_LENGTH];
  int price;
  char shelf[SHELF_LENGTH];
  int quantity;
};


goods_t * create_shelf(int n)
{
  goods_t *s = (goods_t *) calloc(n, sizeof(goods_t));
  return s;
}



void add_to_shelf(goods_t newItem, goods_t *oldList)
{

  void *ptr2 = (void *) calloc(1, sizeof(goods_t));
  for (int i = 0; i < 100; i++)
    {
      void *ptr = (oldList + i);
      int n = memcmp(ptr, ptr2, sizeof(goods_t));
      if (!n)
	{
	  oldList[i] = newItem;
	  return;
	}
    }
  free(ptr2);
}



int get_element(int page, int loc)
{
  int n = ((page-1)*20) + (loc-1);
  return n;
}



void show_page_IO(goods_t *list, char action)
{
 
  for (int page = 1; page <= 5; page++)
    {
      
      printf("\n\n\n\tpage: %d / 5\n", page);
      for(int i_loc = 1; i_loc <= 20; ++i_loc)
	{
	  int n = get_element(page, i_loc);
	  printf("\n\t %d %s", i_loc, list[n].name);
	}
      printf("\n\n\tDid you find your item? [Y]es/[G]o to next page/[M]enu: _");
      int loop = 1;
      while (loop)
	{
	  char c = read_char();
	  switch(c)
	    {
	    case 'G':
	      {
		loop = 0;
		break;
	      }
	    case 'Y':
	      if (action == 'e')
		{
		  edit_goods_IO(list, page);
		}
	      else if (action == 'r')
		{
		  remove_goods_IO(list, page);
		}
	      else if (action == 'l')
		{
		  printf("\n\tChoose item to show its information: [1-20]  _");
		  int index = read_int();
		  int ware = get_element(page, index);
		  display_goods(list[ware]);
		}
	      return;
	    case 'M':
	      return;
	    default:
	      printf("\n\tInvalid input _");
	      break;
	    }
	}
	
    }
}



goods_t generate_goods()
{
  goods_t a;

  
  printf("\n\n\n\tWhat is the name of the item? _");
  char *name = readstring();
  strcpy(a.name, name);
  free(name);

  printf("\tGive the description of the item. _");
  char *desc = readstring();
  strcpy(a.description, desc);
  free(desc);
  
  printf("\tWhat does the item cost? _");
  a.price = read_int();
  
  printf("\tChoose shelf for the item _");
  char *shelf = readstring();
  strcpy(a.shelf, shelf);
  free(shelf); 

  printf("\tHow many are there of the item? _");
  a.quantity = read_int();

  return a;      
}



void display_goods(goods_t dis)
{

  printf("\n\tName: %s", dis.name );

  printf("\n\tDescription: %s", dis.description);

  printf("\n\tPrice: %d", dis.price);

  printf("\n\tShelf: %s", dis.shelf);

  printf("\n\tAmount: %d", dis.quantity);
}



void edit_name(goods_t *list, int i)
{
  printf("\n\n\tThe items current name is: %s \n\t ------------- \n\t New name: _", list[i].name);
  readstring_with_buffer(list[i].name, NAME_LENGTH);  
  printf("\tWares new name is now: %s", list[i].name);
}



void edit_description(goods_t *list, int i)
{
  printf("\n\n\tThe items current description: %s \n\t ------------- \n\tNew description: _", list[i].description);
  readstring_with_buffer(list[i].description, DESC_LENGTH);  
  printf("\tWares new name is now: %s", list[i].description);
}




void edit_price(goods_t *list, int i)
{
  printf("\n\n\tThe items current price is: %d \n\t ------------- \n\tNew price: _", list[i].price);
  list[i].price = read_int();
  printf("\tWares new price is now: %d", list[i].price);
}




void edit_shelf(goods_t *list, int i)
{

  printf("\n\n\tThe items current shelf: %s \n\t ------------- \n\tNew shelf: _", list[i].shelf);
  readstring_with_buffer(list[i].shelf, SHELF_LENGTH);  
  printf("\tWares new name is now: %s", list[i].shelf);
  
}



void edit_quantity(goods_t *list, int i)
{
  printf("\n\n\tCurrent amount of item: %d \n\t ------------- \n\tNew amount: _", list[i].quantity);
  list[i].quantity = read_int();
  printf("\tWares new amount is now: %d", list[i].quantity);
}



int choose_ware(goods_t *l)
{
  printf("\n\tChoose ware to edit: [1-20]  _");
  int i = read_int();
  display_goods(l[i-1]);
  return (i-1);
}



void edit_propertie(goods_t *l, int ware)
{
  int loop = 1;
  while(loop)
    {
      char c = read_char();
      switch (c){

      case 'N':
	edit_name(l, ware);
	return;

      case 'D': 
	edit_description(l, ware);
	return;

      case 'P':
	edit_price(l, ware);
	return;

      case 'S':
	edit_shelf(l, ware);
	return;

      case 'Q':
	edit_quantity(l, ware);
	return;
      case 'c':
	return;
      default:
	printf("\n\n\t Invalid input: _");
	break;
      }
    }
}



void edit_goods_IO(goods_t *l, int page)
{
  printf("\n\tChoose ware to edit: [1-20]  _");
  int index = read_int();  
  int ware = get_element(page, index);
  display_goods(l[ware]);
  printf("\n\n\t[N]ame\n\t[D]escription\n\t[P]rice\n\t[S]helf\n\t[Q]uantity\n\t[c]ancel \n\n\tchoose row or [c]ancel: _");
  edit_propertie(l, ware);
  
}



void remove_ware(goods_t *element)
{
  goods_t *emptylocation =(goods_t *) calloc(1, sizeof(goods_t));
  element = memcpy(element, emptylocation, sizeof(goods_t));
}



void remove_goods_IO(goods_t * l, int page)
{
  printf("\n\tWhat ware would you like to remove? [1-20]  _");
  int index = read_int();
  int ware = get_element(page, index);
  goods_t *ptr = &l[ware];
  display_goods(l[ware]);
  printf("\n\tAre you sure you want to delete your ware? [Y]es/[N]o _");
  
  int loop = 1;
  while(loop)
    {
      char c = read_char();
      switch(c)
	{
	case 'Y':
	  {
	    remove_ware(ptr);
	    return;
	  }

	case 'N':
	  return;

	default:
	  printf("Invalid input _");
	  break;
	}
    }
    
}



int read_int()
{
  char *input = readstring();
  int result = atoi(input);
  free(input);
  return result; 
}



char read_char()
{
  char *input = readstring();
  char result = *input;
  free(input);
  return result; 
}



char * readstring()
{
  return readstring_with_buffer(NULL, 0);
}



char * readstring_with_buffer(char *buffer, size_t bufsize)
{
  ssize_t word;
  
  word = getline(&buffer,&bufsize,stdin);

  if (word >= 0)
    {
      buffer[word-1] = '\0';
    }
  
  return buffer;
  
}



void add_to_shelf_IO(goods_t *l)
{

  goods_t item = generate_goods();
  printf("\n\n");
  display_goods(item);
  printf("\n\tAre you sure you want to add %s to your shelf? [Y]es/[N]o/[E]dit  _  ", item.name);

  while (1)
    {
      char input = read_char();
      
      switch(input)
	{
	case 'Y':
	  add_to_shelf(item, l);
	  return;
	case 'N':
	  return;
	case 'E':
	  {
	    goods_t edItem = generate_goods();
	    add_to_shelf(edItem, l);
	    return;
	  }
	default:
	  printf("\n\tInvalid input _");
	  break;
	}
    }
 
}



void menu()
{
  printf("\n\n\n\n\n\n\n\tWelcome to Foodguard 1.0\n\t========================\n\n\n\t [A]dd a ware\n\t [R]emove a ware\n\t [E]dit properties for a ware\n\t [U]ndo most recent action\n\t[L]ist all goods\n\t E[x]it program\n\n\t Choose action: _");
  
}



void undo_action(void *previousShelf, void *currentShelf)
{
  memcpy(currentShelf, previousShelf, 100*(sizeof(goods_t)));  
}



void get_old_shelf(void *previousShelf, void *currentShelf)
{
  memcpy(previousShelf, currentShelf, 100*(sizeof(goods_t)));
  
}



void exit_program()
{
  printf("Are you sure you want to quit Foodguard? [Y]es/[N]o _");
  int loop = 1;
  while(loop)
    {
      char c = read_char();
      switch(c)
	{
	case 'Y':
	  exit(0);
	case 'N':
	  return;
	default:
	  printf("\n\tInvalid input _");
	  break;
	}
    }
    
}



int main()
{
  goods_t *myShelf = create_shelf(100);
  goods_t *previousshelf = create_shelf(100);
  int loop = 1; 
 
 
  while (loop)
    {
      menu();
      char option = read_char();
      switch(option)
	{

	case 'A':
	  {
	    get_old_shelf(previousshelf, myShelf);
	    add_to_shelf_IO(myShelf);
	    break;
	  }

	case 'R':
	  {
	    get_old_shelf(previousshelf, myShelf);
	    char remove = 'r';
	    show_page_IO(myShelf, remove);
	    break;
	  }

	case 'E':
	  {
	    char edit = 'e';
	    show_page_IO(myShelf, edit);
	    break;
	  }
	case 'U':
	  undo_action(previousshelf, myShelf);
	  printf("\n\tYou have undone your latest action");
	  break;
	  
	case 'L':
	  {
	    char list = 'l';
	    show_page_IO(myShelf, list);  
	    break;
	  }  
	case 'x':
	  exit_program();
	  break;
	default:
	  printf("\n\nInvalid input _");
	  break;
	}
    }
  return 0;
}


