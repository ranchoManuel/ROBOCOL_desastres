#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "robocol_queue.h"

int main(void) {
    queue *q1 = init_robocol_queue(8);
    queue *q2 = init_robocol_queue(8);
    queue *q3 = init_robocol_queue(8);
    enqueue(q1, 5);
    display(q1);
}
