typedef struct queue {
    int space;
    int size;
    int front;
    int rear;
    int *data;
} queue;

queue* init_robocol_queue(int bound);
int dequeue(queue* q);
bool enqueue(queue *q, int datum);
int front(queue* q);
int rear(queue* q);
bool empty(queue* q);
bool overflow(queue* q);
void display(queue* q);