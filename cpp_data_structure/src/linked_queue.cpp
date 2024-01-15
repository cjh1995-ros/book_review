#include "linked_list.hpp"



int main()
{
    LinkedQueue l_queue;

    l_queue.enqueue({1, "Choi", "Computer Science"});
    l_queue.enqueue({2, "Jun", "Science"});
    l_queue.enqueue({3, "Hyeok", "Computer"});
    l_queue.enqueue({4, "Cool", "Mechanical"});
    l_queue.enqueue({5, "Morai", "Electronic"});
    l_queue.enqueue({6, "Bench", "Mechatronic"});
    l_queue.enqueue({7, "Tree", "Art"});
    l_queue.enqueue({8, "ETC", "Law"});

    l_queue.print();

    std::shared_ptr<Node> ret1 = l_queue.dequeue();
    ret1->print();

    std::shared_ptr<Node> ret2 = l_queue.dequeue();
    ret2->print();

    std::shared_ptr<Node> ret3 = l_queue.dequeue();
    ret3->print();

    l_queue.print();

    return 0;

}