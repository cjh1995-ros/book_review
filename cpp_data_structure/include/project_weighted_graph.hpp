#pragma once

#include "project_graph.hpp"
#include <memory>
#include <vector>


#define INF 9999



class WMatGraph : public MatGraph
{
public:
    void insert_edge(int i, int j, int w)
    {
        if (w >= INF) w = INF;
        set_edge(i, j, w);
        set_edge(j, i, w);
    }
    bool has_edge(int i, int j) { return get_edge(i, j) < INF && get_edge(i, j) > 0; }
};



class VertexSets
{
private:
    int parent_[MAX_VERTICES]; // 부모 정점의 id
    int n_set_;
public:
    VertexSets(int n): n_set_(n)
    {
        for (int i = 0; i < n_set_; i++)
            parent_[i] = -1; // 초기에는 모든 정점이 고유 집합에 속함. 
    }

    bool is_root(int v) { return parent_[v] < 0; }
    int find_set(int v) 
    {
        while (!is_root(v)) v = parent_[v];
        return v;
    }
    void union_set(int s1, int s2) // 집합 s1을 s2와 합침
    {
        parent_[s1] = s2;
        n_set_--;
    }
};



/// @brief 간선 정보를 저장한 노드. key는 간선 크기. v1 정점 1, v2 정점 2.
struct HeapNode
{
    int key;
    int v1;
    int v2;
    HeapNode() = default;
    HeapNode(int k, int u, int v): key(k), v1(u), v2(v) {}
    void set_key(int k) { key = k; }
    int get_key() { return key; }
    int get_v1() { return v1; }
    int get_v2() { return v2; }
};

typedef std::shared_ptr<HeapNode> ptr;


class MinHeap
{
protected:
    ptr heap_nodes_[MAX_VERTICES]; // 힙 삽입은 맞는데, 정렬 기준은 간선의 가중치로 결정됨.
    int size_;


public:
    MinHeap()
    {
        size_ = 0;
        for (int i = 0; i < MAX_VERTICES; i++)
            heap_nodes_[i] = nullptr; // 초기화 되지 않은 경우.
    }

    bool is_full() { return size_ == MAX_VERTICES; }
    bool is_empty() { return size_ == 0; }

    ptr get_parent(int i) { return heap_nodes_[i / 2]; }
    ptr get_left(int i)   { return heap_nodes_[i * 2]; }
    ptr get_right(int i)  { return heap_nodes_[i * 2 + 1]; }

    /// @brief node를 heap tree에 삽입하려고 함.
    /// @param key: 간선의 가중치
    /// @param u: 정점 1
    /// @param v: 정점 2
    void insert(int key, int u, int v)
    {
        if (is_full()) return; // 꽉 차면 그냥 넘김. 

        // 새로운 노드가 들어왔으니, 해당 노드는 트리의 맨 마지막에 삽입됨.
        int i = ++size_;

        while (i != 1 && key < get_parent(i)->get_key())
        {
            heap_nodes_[i] = get_parent(i);
            i /= 2; // i <= parent;
        }

        heap_nodes_[i] = std::make_shared<HeapNode>(key, u, v);
    }

    ptr remove()
    {
        if (is_empty()) return nullptr;

        ptr item = heap_nodes_[1];
        ptr node = heap_nodes_[size_--]; // 가장 큰 값 지님. 이 값을 계속해서 내릴 것임.

        int parent  = 1;
        int child   = 2;

        while (child <= size_)
        {
            if (node->get_key() < heap_nodes_[parent]->get_key()) break;

            if (get_left(parent)->get_key() > get_right(parent)->get_key()) // 더 작은 값과 교환
                child += 1;

            heap_nodes_[parent] = heap_nodes_[child]; // 교환 
            parent = child;
            child *= 2;
        }

        heap_nodes_[parent] = node;

        return item;
    }
};


class WGraphMst : public WMatGraph
{
public:
    void Kruskal()
    {
        MinHeap heap;

        for (int i = 0; i < size_; i++)
        {
            for (int j = i + 1; j < size_; j++)
            {
                if (has_edge(i, j))
                    heap.insert(get_edge(i, j), i, j);
            }
        }

        VertexSets set(size_);

        int accepted_edge = 0;

        while ( accepted_edge < size_ - 1)
        {
            ptr n = heap.remove();

            int uset = set.find_set(n->get_v1());
            int vset = set.find_set(n->get_v2());

            if (uset != vset)
            {
                printf("간선추가..%c - %c (가중치: %d)\n", 
                    get_vertex(n->get_v1()), 
                    get_vertex(n->get_v2()),
                    n->get_key());
                set.union_set(uset, vset);
                accepted_edge++;
            }
        }
    }


    int get_min_vertex(bool* selected, int* dist)
    {
        int min_v;
        int min_dist = INF;

        for (int i = 0; i < size_; i++)
        {
            if (!selected[i] && dist[i] < min_dist)
            {
                min_v = i;
                min_dist = dist[i];
            }
        }

        return min_v;
    }

    void Prim(int s)
    {
        bool selected[size_];
        int dist[size_];

        // dist 초기화 
        for (int i = 0; i < size_; i++)
        {
            selected[i] = false;
            dist[i] = INF;
        }
            
        dist[s] = 0;

        for (int i = 0; i < size_; i++) // 누군지 몰라서? ㄴㄴ 시작점이 상관 없어서.
        {
            int u = get_min_vertex(selected, dist); // 맨 처음엔 0 이 선택될 것.

            selected[u] = true;

            if (dist[u] == INF) return;
            printf("%c ", get_vertex(u));

            for (int v = 0; v < size_; v++)
            {
                if (get_edge(u, v) != INF)
                {
                    if (!selected[v] && get_edge(u, v) < dist[v])
                        dist[v] = get_edge(u, v);
                }
            }
        }        
    }
};


class WGraphDijkstra : public WMatGraph
{
private:
    int     dist[MAX_VERTICES];
    bool    found[MAX_VERTICES];
public:
    int choose_vertex()
    {
        int min = INF;
        int min_pos = -1;

        for (int i = 0; i < size_; i++)
        {
            if (dist[i] < min && !found[i])
            {
                min = dist[i];
                min_pos = i;
            }
        }

        return min_pos;
    }


    void ShortestPath(int start)
    {
        for (int i = 0; i < size_; i++)
        {
            dist[i] = get_edge(start, i);
            found[i] = false;
        }

        found[start] = true;
        dist[start] = 0;

        for (int i = 0; i < size_; i++)
        {
            printf("Step %2d", i+1);
            print_distance();

            int u = choose_vertex();
            found[u] = true;

            for (int w = 0; w < size_; w++)
            {
                if (found[w] == false)
                if (dist[u] + get_edge(u, w) < dist[w])
                    dist[w] = dist[u] + get_edge(u, w);
            }
        }
    }


    void print_distance()
    {
        for (int i = 0; i < size_; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }

};