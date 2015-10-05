typedef struct tree_s tree;
typedef struct node_s node;
typedef struct list_s list;
typedef struct shelf_node_s shelf_node;

node * create_new_node(char* name, char* description, int price, char*shelf_name, int amount);

void destroy_tree(node* node); //argument?

// skickar in ett namn på en vara och trädet. Returnerar true om varan redan finns. Annars returernar den false
bool existing_node(node* node, char* name);


  
