#include "student_stack.hpp"

int main()
{
    StudentStack stack;

    stack.push(Student(20240114, "Choi Jun Hyeok1", "Computer Science"));
    stack.push(Student(20240115, "Choi Jun Hyeok2", "Computer Science"));
    stack.push(Student(20240116, "Choi Jun Hyeok3", "Computer Science"));
    stack.push(Student(20240117, "Choi Jun Hyeok4", "Computer Science"));
    stack.push(Student(20240118, "Choi Jun Hyeok5", "Computer Science"));

    stack.print();
}