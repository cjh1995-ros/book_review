#include "project_priority_queue.hpp"
#include <vector>

void heap_sort(std::vector<int>& v)
{
    MaxHeap h;

    for (int i = 0; i < v.size(); i++)
        h.insert(v[i]);

    for (int i = 0; i < v.size(); i++)
        v[i] = h.remove().get_key();
}


void MakeHuffTree(std::vector<int> codes)
{
    MinHeap h;

    for (int i = 0; i < codes.size(); i++)
        h.insert(codes[i]);

    for (int i = 0; i < codes.size() - 1; i++)
    {
        HeapNode e1 = h.remove();
        HeapNode e2 = h.remove();
        int sum = e1.get_key() + e2.get_key();
        h.insert(sum);
        printf("(%d + %d) = %d\n", 
                e1.get_key(), e2.get_key(), sum);
    }

    h.display();
}

int main()
{
    MaxHeap h;

    h.insert(10);   h.insert(9);
    h.insert(8);   h.insert(7);
    h.insert(6);   h.insert(5);
    h.insert(4);   h.insert(3);
    h.insert(2);   h.insert(1);

    std::cout << "############## Heap Test ##############" << std::endl;
    h.display();

    

    std::cout << "############## Sorting! Test ##############" << std::endl;
    std::vector<int> vec;
    for (int i = 0; i < 10; i++) vec.push_back( rand() % 100 );

    std::cout << "Before: ";
    for (int i = 0; i < 10; i++) std::cout << vec[i] << " ";
    printf("\n");


    heap_sort(vec);

    std::cout << "After: ";
    for (int i = 0; i < 10; i++) std::cout << vec[i] << " ";
    printf("\n");


    // MakeHuffTree(vec);

    MinPriorityQueueLList mpql;

    for (int i = 0; i < 10; i++)
        mpql.insert(vec[i]);

    std::cout << "By Linked List: " << std::endl;
    mpql.display();

    mpql.remove(); mpql.remove();

    mpql.display();
}