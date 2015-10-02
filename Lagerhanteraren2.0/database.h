#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef DATABASE_H 
#define DATABASE_H

typedef struct warehouse warehouse;
typedef struct shelf shelf;

// Creates a new warehouse
warehouse * new_warehouse();

bool is_shelf_taken(warehouse *warehouse_list, const char *shelf_num);

// adds a new item to the shelf
void add_shelf(warehouse *warehouse_list, char *name, char *description, int price, char *shelf_num, int num_items);

// removes an item, based on index in list.
void remove_shelf(warehouse *warehouse_list, int index);

// Edits a shelf. Updates the exsisting shelf (at address shelf) with the arguments passed to this function.
void edit_shelf(warehouse *warehouse_list, shelf *shelf, char *name, char *description, int price, char *shelf_num, int num_items);

// gets address to shelf at index in warehouse_list
shelf * get_shelf(warehouse *warehouse_list, int index);

// undos the latest action
void undo_action(warehouse *warehouse_list);

// free up memory used by program
void destroy_warehouse(warehouse *warehouse_list);

shelf * get_last_shelf(warehouse *warehouse_list); //Karro testar

char * get_name(shelf *shelf);
char * get_description(shelf *shelf);
int get_price(shelf *shelf);
char * get_shelf_num(shelf *shelf);
int get_num_items(shelf *shelf);
shelf * get_next_shelf(shelf *shelf);

shelf * get_first(warehouse * warehouse_list);

int warehouse_empty(warehouse *warehouse_list);

#endif /* DATABASE_H */
