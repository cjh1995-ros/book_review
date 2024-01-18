#include <iostream>
#include <vector>



constexpr int MAX_VTXS = 256;



class AdjMatgraph
{
protected:
    int     size_;
    char    vertices_[MAX_VTXS];
    int     adj_[MAX_VTXS][MAX_VTXS];

public:
    AdjMatgraph(): size_(0) { reset(); }

    char get_vertex(int i) { return vertices_[i]; }
    int get_edge(int i, int j) { return adj_[i][j]; }
    void set_edge(int i, int j, int val) { adj_[i][j] = val; }
    
    bool is_empty() { return size_ == 0; }
    bool is_full() { return size_ >= MAX_VTXS; }

    void reset()
    {
        for (int i = 0; i < MAX_VTXS; i++)
        for (int j = 0; j < MAX_VTXS; j++)
            adj_[i][j] = 0;
    }

    void insert_vertex( char name )
    {
        if (!is_full()) vertices_[size_++] = name;
        else std::cout << "Full!" << std::endl;
    }

    void insert_edge( int u, int v)
    {
        set_edge(u, v, 1);
        set_edge(v, u, 1);
    }

    void display()
    {
        for (int i = 0; i < size_; i++)
        {
            std::cout << get_vertex(i) << " ";
            for (int j = 0; j < size_; j++)
                std::cout << adj_[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

class SrchAMGraph: public AdjMatgraph
{
private:
    bool visited_[MAX_VTXS];
public:
    void reset_visited()
    {
        for (int i = 0; i < MAX_VTXS; i++)
            visited_[i] = false;
    }
    
    bool is_linked(int u, int v) { return this->get_edge(u, v) != 0; }

    void DFS(int v)
    {
        visited_[v] = true; // 현재 정점 방문함.
        std::cout << this->get_vertex(v) << " ";

        for ( int w = 0; w < this->size_; w++)
        {
            if ( is_linked(v, w) && visited_[w] == false)
                DFS(w);
        }
    }
};



int main()
{
    SrchAMGraph g;

    for (int i = 0; i < 8; i++)
        g.insert_vertex('A' + i);

    g.insert_edge(0, 1);
    g.insert_edge(0, 2);
    g.insert_edge(1, 3);
    g.insert_edge(2, 3);
    g.insert_edge(2, 4);
    g.insert_edge(3, 5);
    g.insert_edge(4, 6);
    g.insert_edge(4, 7);
    g.insert_edge(6, 7);

    g.display();

    g.DFS(0);


    return 0;
}