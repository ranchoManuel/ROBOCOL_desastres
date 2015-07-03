typedef struct node {
    int data;
    struct node* next;
} node;

typedef node* listPointer;

node* init_robocol_list();
int append(listPointer*, int);
int delete(listPointer*, int);
bool empty_list(listPointer);
void display_list(listPointer);