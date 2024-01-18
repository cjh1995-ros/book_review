#include <memory>
#include <iostream>
#include <vector>
#include <cstdlib>



constexpr int MAX_ELEMENT = 200;

template<typename T>
struct HeapNode : public std::enable_shared_from_this<HeapNode<T>>
{
    T key;
    HeapNode() = default;
    HeapNode(T k): key(k)   {}
    void set_key(T k)       { key = k; }
    int get_key()           { return key; }
    void display()           { std::cout << key << " ";}
};



template<typename T>
class MaxHeap
{
using Heap = HeapNode<T>;
using pHeap = Heap*;
private:
    Heap heap_nodes_[MAX_ELEMENT];
    int size_;
public:
    MaxHeap(): size_(0) {}
    bool is_empty()             { return size_ == 0; }
    bool is_full()              { return size_ == MAX_ELEMENT; }
    Heap& get_parent(int i)     { return heap_nodes_[i/2]; }
    Heap& get_left(int i)       { return heap_nodes_[i*2]; }
    Heap& get_right(int i)      { return heap_nodes_[i*2+1]; }


    void insert(T k)
    {
        if (is_full()) return;
        int i = ++size_;

        // 트리를 거슬러 올라가며 부모 노드와 비교하는 과정.
        while (i != 1 && k > get_parent(i).get_key())  // 루트가 아니고 + 부모 노드보다 키값이 크면
        {
            heap_nodes_[i] = get_parent(i);             // 부모를 자신으로 끌어내림.
            i /= 2;                                     // 한 레벨 상승
        }

        heap_nodes_[i].set_key(k);
    }

    Heap remove()
    {
        if (is_empty()) return NULL;

        Heap item = heap_nodes_[1];
        Heap last = heap_nodes_[size_--];
        int parent = 1;
        int child = 2;

        while (child <= size_)
        {
            if (child < size_ &&
                get_left(parent).get_key() < get_right(parent).get_key())
                child++;
            if (last.get_key() >= heap_nodes_[child].get_key()) break;

            heap_nodes_[parent] = heap_nodes_[child];
            parent = child;
            child *= 2;
        }

        heap_nodes_[parent] = last;
        
        return item;
    }

    void display()
    {
        for (int i = 1, level = 1; i <= size_; i++)
        {
            if (i == level) {
                std::cout << std::endl;
                level *=2;
            }
            heap_nodes_[i].display();
        }
    }
};




template<typename T>
class MinHeap
{
using Heap = HeapNode<T>;
using pHeap = Heap*;
private:
    Heap heap_nodes_[MAX_ELEMENT];
    int size_;
public:
    MinHeap(): size_(0) {}
    bool is_empty()             { return size_ == 0; }
    bool is_full()              { return size_ == MAX_ELEMENT; }
    Heap& get_parent(int i)     { return heap_nodes_[i/2]; }
    Heap& get_left(int i)       { return heap_nodes_[i*2]; }
    Heap& get_right(int i)      { return heap_nodes_[i*2+1]; }


    void insert(T k)
    {
        if (is_full()) return;
        int i = ++size_;

        // 트리를 거슬러 올라가며 부모 노드와 비교하는 과정.
        while (i != 1 && k < get_parent(i).get_key())  // 루트가 아니고 + 부모 노드보다 키값이 크면
        {
            heap_nodes_[i] = get_parent(i);             // 부모를 자신으로 끌어내림.
            i /= 2;                                     // 한 레벨 상승
        }

        heap_nodes_[i].set_key(k);
    }

    Heap remove()
    {
        if (is_empty()) return NULL;

        Heap item = heap_nodes_[1];
        Heap last = heap_nodes_[size_--];
        int parent = 1;
        int child = 2;

        while (child <= size_)
        {
            if (child < size_ &&
                get_left(parent).get_key() > get_right(parent).get_key())
                child++;
            if (last.get_key() <= heap_nodes_[child].get_key()) break;

            heap_nodes_[parent] = heap_nodes_[child];
            parent = child;
            child *= 2;
        }

        heap_nodes_[parent] = last;
        
        return item;
    }

    void display()
    {
        for (int i = 1, level = 1; i <= size_; i++)
        {
            if (i == level) {
                std::cout << std::endl;
                level *=2;
            }
            heap_nodes_[i].display();
        }
    }
};



template<typename T>
void heap_sort(std::vector<T>& a, int n)
{
    MaxHeap<T> h;

    // init heap
    for (int i = 0; i < n; i++)
        h.insert(a[i]);
    
    for (int i = n - 1; i > 0; i--)
        a[i] = h.remove().get_key();
}


template<typename T>
void huffman_code(std::vector<T>& a, int n)
{
    MinHeap<T> heap;

    // init heap
    for (int i = 0; i < n; i++)
        heap.insert(a[i]);
    

    for (int i = n - 1; i > 0; i--)
    {
        HeapNode<T> e1 = heap.remove();
        HeapNode<T> e2 = heap.remove();

        heap.insert(e1.get_key() + e2.get_key());
        std::cout << e1.get_key() << " + " << e2.get_key() <<std::endl;
    }
}


int main()
{
    // MaxHeap<int> heap;

    // heap.insert(10);    heap.insert(5);
    // heap.insert(30);    heap.insert(8);
    // heap.insert(9);     heap.insert(3);
    // heap.insert(7);

    // heap.display();

    // heap.remove();
    // heap.remove();

    // heap.display();

    std::vector<int> a;

    for (int i = 0; i < 10; i++) a.push_back(rand() % 100);

    std::cout << "Before sorting!" << std::endl;

    for (int i = 0; i < 10; i++) std::cout << a[i] << " ";
    
    std::cout << std::endl;

    heap_sort<int>(a, 10);

    std::cout << "After sorting!" << std::endl;

    for (int i = 0; i < 10; i++) std::cout << a[i] << " ";


    huffman_code(a, 10);
    
    for (int i = 0; i < 10; i++) std::cout << a[i] << " ";
    
    return 0;
}