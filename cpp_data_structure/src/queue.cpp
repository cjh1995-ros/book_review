#include "queue.hpp"

int main()
{
    CircularQueue cq;

    int max_enqueue_itr = 30;

    for (int i = 0; i < max_enqueue_itr; i++)
        cq.enqueue(i);

    cq.print();

    int max_dequeue_itr = 10;

    for (int i = 0; i < max_dequeue_itr; i++ )
        cq.dequeue();
    
    cq.print();

    return 0;
}