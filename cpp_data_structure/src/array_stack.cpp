#include "stack.hpp"

int main()
{
    ArrayStack stack;

    for (int i = 0; i < 10; i++)
        stack.push(i);

    stack.print();

    std::cout << "pop: " << stack.pop() << std::endl;
    std::cout << "peek: " << stack.peek() << std::endl;

    stack.print();

    return 0;
}