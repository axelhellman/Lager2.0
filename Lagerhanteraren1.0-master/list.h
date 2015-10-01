typedef struct goods goods_t;


//Functions
goods_t * create_shelf(); 
void add_to_shelf(goods_t newItem, goods_t * oldList); 
int get_element(int page, int loc);
void show_page_IO(goods_t *list, char action);
goods_t generate_goods();
void display_goods(goods_t g);
void edit_name(goods_t *l, int element);
void edit_description(goods_t *l, int element);
void edit_price(goods_t *l, int element);
void edit_shelf(goods_t *l, int element);
void edit_quantity(goods_t *l, int element);
int choose_ware(goods_t *l);
void edit_propertie(goods_t *l, int ware);
void edit_goods_IO(goods_t *l, int page);
void remove_ware(goods_t *element);
void remove_goods_IO(goods_t *l, int page);
char * readstring(); 
void add_to_shelf_IO(goods_t *l);
void menu();
void undo_action(void *previousShelf, void *currentShelf);
void get_old_shelf(void *previousShelf, void *currentShelf);
void exit_program();
int read_int();
char read_char();
char * readstring();
char * readstring_with_buffer(char *buffer, size_t bufsize);





