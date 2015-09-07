typedef struct queue
{
    int space;
    int size;
    int front;
    int rear;
    int *data;
} queue;

queue* init_robocol_queue(int);
int dequeue(queue*);
bool enqueue(queue*, int);
int front(queue*);
int rear(queue*);
bool empty_queue(queue*);
bool overflow(queue*);
void display_queue(queue*);