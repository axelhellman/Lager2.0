#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef SMALLFUNC_H 
#define SMALLFUNC_H

#include "database.h"

int ask_index(warehouse* warehouse_list, int page);

char* ask_str_q (char *question);

int ask_int_q (char *question, int low, int high);

int ask_yn(char* question);

char ask_alt(char* question, char* alternatives);

char* fix_shelf_num(warehouse* warehouse_list, char* shelf_num);

void print_line(void);

#endif /* SMALLFUNC_H */
