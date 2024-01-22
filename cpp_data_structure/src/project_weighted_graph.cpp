#include "project_weighted_graph.hpp"




int main()
{
    // WGraphMst g;
    WGraphDijkstra g;

    for (int i = 0; i < 7; i++)
        g.insert_vertex('A' + i);
    
    g.insert_edge(0, 1, 29);    g.insert_edge(0, 2, 9999); 
    g.insert_edge(0, 3, 9999);  g.insert_edge(0, 4, 9999);
    g.insert_edge(0, 5, 10);    g.insert_edge(0, 6, 9999);

    g.insert_edge(1, 2, 16);    g.insert_edge(1, 3, 9999);
    g.insert_edge(1, 4, 9999);  g.insert_edge(1, 5, 9999);
    g.insert_edge(1, 6, 9999);

    g.insert_edge(2, 3, 12);    g.insert_edge(2, 4, 9999);
    g.insert_edge(2, 5, 9999);  g.insert_edge(2, 6, 9999);

    g.insert_edge(3, 4, 22);    g.insert_edge(3, 5, 9999);
    g.insert_edge(3, 6, 18);

    g.insert_edge(4, 5, 27);    g.insert_edge(4, 6, 25);

    g.insert_edge(5, 6, 9999);

    g.display();


    // g.Kruskal();

    std::cout << std::endl;

    // g.Prim(2); // 간선 기중 최소 신장 트리 만드는 기법.

    std::cout << std::endl;

    g.ShortestPath(0);
    
}