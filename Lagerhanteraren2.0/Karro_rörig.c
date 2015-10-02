
//IO.c
int same_shelf_num_index(warehouse *warehouse_list, char* shelf_num)
{
  shelf *crnt_shelf = warehouse_list->first_shelf;
  char* crnt_shelf_num = crnt_shelf->shelf_num;
  int index = 0;
  for (index = 0; strcmp(crnt_shelf_num, shelf_num) != 0; ++index)
    {
      crnt_shelf = crnt_shelf->next_shelf;
      crnt_shelf_num = crnt_shelf->shelf_num;
      if(crnt_shelf == NULL)
	{
	  return -1;
	}
    }
  return index;
}


//database.h
int same_shelf_num_index(warehouse *warehouse_list, char* shelf_num);
