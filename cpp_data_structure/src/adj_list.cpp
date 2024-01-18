#include "adj_list.hpp"


int main()
{
    AdjListGraph g;

    g.insert_vertex('A');
    g.insert_vertex('B');
    g.insert_vertex('C');
    g.insert_vertex('D');
    
    g.insert_edge(0, 1);
    g.insert_edge(0, 3);
    g.insert_edge(1, 0);
    g.insert_edge(1, 2);
    g.insert_edge(1, 3);
    g.insert_edge(2, 3);

    g.display();





    return 0;
}