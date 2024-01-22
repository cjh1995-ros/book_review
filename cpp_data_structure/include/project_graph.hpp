#pragma once

#include <memory>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <random>
#include <sstream>


constexpr int MAX_VERTICES = 100;

/// @brief 인접행렬 그래프
class MatGraph
{
protected:
    int size_;
    char   vertices_[MAX_VERTICES];
    int adj_mat_[MAX_VERTICES][MAX_VERTICES];
public:
    MatGraph() { reset(); }

    char get_vertex(int i) { return vertices_[i]; }
    int get_edge(int i, int j) { return adj_mat_[i][j]; }
    void set_edge(int i, int j, int val) { adj_mat_[i][j] = val;}
    bool is_empty() { return size_ == 0; }
    bool is_full() { return size_ == MAX_VERTICES; }

    int get_size() { return size_; }

    void reset()
    {
        size_ = 0;

        for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            set_edge(i, j, 0);
    }

    void insert_vertex(char v)
    {
        if (is_full()) printf("최대정점 초과\n");
        else vertices_[size_++] = v;
    }

    void insert_edge(int i, int j) { set_edge(i, j, 1); set_edge(j, i, 1); }

    void display()
    {
        for (int i = 0; i < size_; i++)
        {
            for (int j = 0; j < size_; j++)
                std::cout << adj_mat_[i][j] << " ";
            std::cout << std::endl;
        }
    }
};




class SrchMatGraph : public MatGraph
{
protected:
    bool visited_[MAX_VERTICES];
public:
    void reset_visited() 
    {
        for (int i = 0; i < MAX_VERTICES; i++)
            visited_[i] = false;
    }

    bool is_linked(int i, int j) { return get_edge(i, j) == 1; }

    void DFS(int v)
    {
        visited_[v] = true;

        printf("%c ", vertices_[v]);

        for (int i = 0; i < size_; i++)
        {
            // depth first 이기 때문에 i, v. breath 면 v, i
            if (is_linked(i, v) && visited_[i] == false)
                DFS(i);
        }
    }

    void BFS(int v) // queue 안쓰고 가능?
    {
        visited_[v] = true;

        printf("%c ", vertices_[v]);

        std::queue<int> q;

        q.push(v);

        while (!q.empty())
        {
            int new_v = q.front();
            q.pop();

            for (int i = 0; i < size_; i++)
            {
                // depth first 이기 때문에 i, v. breath 면 v, i
                if (is_linked(new_v, i) && visited_[i] == false)
                {
                    visited_[i] = true;
                    printf("%c ", vertices_[i]);
                    q.push(i);
                }
            }
        }

    }
};



class ConnectedComponentGraph : public SrchMatGraph
{
protected:
    int label_[MAX_VERTICES];
public:
    void label_DFS(int v, int color)
    {
        visited_[v] = true;
        label_[v] = color;

        for (int i = 0; i < size_; i++)
            if (!visited_[i] && is_linked(i, v))
                label_DFS(i, color);
    }


    void find_connected_components()
    {
        int count = 0;

        for (int i = 0; i < size_; i++)
            if (!visited_[i])
                label_DFS(i, ++count);
        
        printf("그래프 연결성분 개수: %d\n", count);

    }

};







struct Node : public std::enable_shared_from_this<Node>
{
using ptr = std::shared_ptr<Node>;
    int id;
    ptr next;

    Node(): id(-1), next(nullptr) {};
    Node(int i, ptr n = nullptr): id(i), next(n) {}

    void set_next(ptr n) { next = n; }
    ptr get_next() { return next; }
    void display() { printf("%d ", id); }

    void insert(ptr n)
    {
        // Don't add same id
        if (n->id == id)        return;
        if (next != nullptr)    next->insert(n);
        else                    set_next(n);
    }
};



class ListGraph
{
using ptr = std::shared_ptr<Node>;
protected:
    int     size_;
    char    vertices_[MAX_VERTICES];
    ptr     adj_list_[MAX_VERTICES];
public:
    ListGraph(): size_(0) {}

    void reset()
    {
        for (int i = 0; i < MAX_VERTICES; i++) 
            adj_list_[i].reset();
        size_ = 0;
    }

    int  get_size() { return size_; }
    bool is_empty() { return size_ == 0; }
    bool is_full() { return size_ >= MAX_VERTICES; }
    char get_vertex(int i) { return vertices_[i]; }

    void insert_vertex(char v)
    {
        if (!is_full())
        {
             vertices_[size_] = v;
             adj_list_[size_++] = std::make_shared<Node>();
        }
        else printf("It's full...\n");
    }

    void insert_edge(int i, int j)
    {
        adj_list_[i]->insert(std::make_shared<Node>(j));
        adj_list_[j]->insert(std::make_shared<Node>(i));
    }

    ptr get_adj(int i) { return adj_list_[i]; }

    void display()
    {
        for (int i = 0; i < size_; i++)
        {
            std::cout << get_vertex(i) << " ";
            for (ptr node = adj_list_[i]; node != nullptr; node = node->get_next())
                std::cout << get_vertex(node->id) << " ";
            std::cout << std::endl;
        }
    }
};



class SrchListGraph : public ListGraph
{
using ptr = std::shared_ptr<Node>;    
protected:
    bool visited_[MAX_VERTICES];
public:
    void reset_visited() 
    {
        for (int i = 0; i < MAX_VERTICES; i++)
            visited_[i] = false;
    }

    // 사실 그렇게 까지 필욘 없는듯...?
    bool is_linked(int i, int j) 
    {
        if (get_adj(i) != nullptr)
        {
            for (auto n = get_adj(i); n != nullptr; n = n->get_next())
                if (n->id == j) return true;
        }
        return false;
    }

    void DFS(int i)
    {
        visited_[i] = true;
        
        printf("%c ", get_vertex(i));

        for (ptr n = get_adj(i); n != nullptr; n = n->get_next())
            if (n->id != -1 && !visited_[n->id]) // n->id != -1: 기본 노드 건너뜀
                DFS(n->id);
                
    }

    void BFS(int i)
    {
        visited_[i] = true;

        std::queue<ptr> q;
        
        printf("%c ", get_vertex(i));

        q.push(get_adj(i));

        while (!q.empty())
        {
            auto node = q.front();
            q.pop();

            for (auto n = node; n != nullptr; n = n->get_next())
            {
                if (!visited_[n->id] && n->id != -1)
                {
                    visited_[n->id] = true;
                    printf("%c ", get_vertex(n->id));
                    q.push(get_adj(n->id));
                }
            }
        }
    }
};


class ConnectedComponentListGraph : public SrchListGraph
{
protected:
    int label_[MAX_VERTICES];
public:
    void label_DFS(int v, int color)
    {
        visited_[v] = true;
        label_[v] = color;

        for (auto node  = get_adj(v); node != nullptr; node = node->get_next())
            if (!visited_[node->id] && node->id != -1)
                label_DFS(node->id, color);
    }


    void find_connected_components()
    {
        int count = 0;

        for (int i = 0; i < size_; i++)
            if (!visited_[i])
                label_DFS(i, ++count);
        
        printf("그래프 연결성분 개수: %d\n", count);
    }
};



class TopoGraph : public ListGraph
{
protected:
    int ind_deg[MAX_VERTICES];
public:
    void insert_dir_edge(int i, int j)
    { 
        adj_list_[i]->insert(std::make_shared<Node>(j));
    }

    void topo_sort()
    {
        // 인접 degree 초기화
        for (int i = 0; i < size_; i++)
            ind_deg[i] = 0;
        
        // 간선 수 확인
        for (int i = 0; i < size_; i++)
        for (auto node = get_adj(i); node != nullptr; node = node->get_next())
            if (node->id != -1) ind_deg[node->id]++;

        // 진입 차수가 0 인 노드 id 삽입.
        std::stack<int> s;
        for (int i = 0; i < size_; i++)
            if (ind_deg[i] == 0) s.push(i);

        // DFS를 기반한 Sorting 시작
        while (!s.empty())
        {
            int idx = s.top();
            s.pop();

            printf("%c ", get_vertex(idx));

            for (auto n = get_adj(idx); n != nullptr; n = n->get_next())
            {
                if (n->id != -1)
                {
                    ind_deg[n->id]--;
                    if (ind_deg[n->id] == 0) s.push(n->id);
                }
            }
                

        }
    }
};





/// @brief generate non directional matrix
void random_graph_generator(
    int n_vertex, 
    int n_edge, 
    std::string filename = "graph.txt")
{
    if (n_vertex > MAX_VERTICES) n_vertex = MAX_VERTICES;

    MatGraph g;

    for (int i = 0; i < n_vertex; i++)
        g.insert_vertex('A' + i);
    
    // 
    std::random_device rd;  // 시드 생성을 위한 무작위 장치
    std::mt19937 gen(rd()); // 난수 생성기 (Mersenne Twister 알고리즘)

    // 난수 범위 정의
    std::uniform_int_distribution<> dis(0, n_vertex);

    while (n_edge != 0)
    {
        int i = dis(gen);
        int j = dis(gen);

        // 만약 동일하면 다시...
        if (i == j) continue;

        g.insert_edge(i, j);

        // 잘 넣었으면 숫자 감소
        --n_edge;
    }


    // 파일 쓰기
    std::ofstream file(filename);
    if (file.is_open()) {
        // 정점 개수 쓰기
        file << n_vertex << std::endl;

        // 인접 행렬 쓰기
        for (int i = 0; i < n_vertex; i++) {
            file << char('A' + i) << " ";
            for (int j = 0; j < n_vertex; j++) {
                file << g.get_edge(i, j) << " ";
            }
            file << std::endl;
        }
        file.close();
    }
}


void read_graph_from_file(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }

    MatGraph g;
    std::string line;
    int n_vertex;

    // 첫 번째 줄에서 정점의 개수를 읽음
    std::getline(file, line);
    std::istringstream vertex_line(line);
    vertex_line >> n_vertex;

    // 정점 추가
    for (int i = 0; i < n_vertex; ++i) {
        g.insert_vertex('A' + i);
    }

    // 인접 행렬 읽기
    int i = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char vertex_label;
        int adjacency;

        // 정점 레이블 읽기
        iss >> vertex_label;

        // 인접 행렬의 각 요소 읽기
        for (int j = 0; j < n_vertex; ++j) {
            iss >> adjacency;
            if (adjacency != 0) {
                g.set_edge(i, j, adjacency);
            }
        }
        ++i;
    }

    g.display();
}