#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "database.h"
#include "smallfunc.h"

#ifndef IO_H 
#define IO_H


//funktioner som menu kallar på

void add_shelf_IO(warehouse *warehouse_list);

void remove_shelf_IO(warehouse *warehouse_list);

void edit_shelf_IO(warehouse *warehouse_list);

void undo_action_IO(warehouse * warehouse_list);

int exit_warehouse();

int ask_int_q(char* question, int low, int high);

void print_warehouse(warehouse *warehouse_list);


#endif /* IO_H */

