#include "linked_list.hpp"



int main()
{
    LinkedStack l_stack;

    l_stack.push({1, "Choi", "Computer Science"});
    l_stack.push({2, "Jun", "Science"});
    l_stack.push({3, "Hyeok", "Computer"});
    l_stack.push({4, "Cool", "Mechanical"});
    l_stack.push({5, "Morai", "Electronic"});
    l_stack.push({6, "Bench", "Mechatronic"});
    l_stack.push({7, "Tree", "Art"});
    l_stack.push({8, "ETC", "Law"});

    l_stack.print();

}