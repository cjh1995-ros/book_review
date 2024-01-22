#include "project_graph.hpp"






int main()
{
    // MatGraph g;
    // ListGraph g;
    // SrchMatGraph g;
    // SrchListGraph g;
    // ConnectedComponentGraph g;
    // ConnectedComponentListGraph g;
    TopoGraph g;

    for (int i = 0; i < 6; i++)
        g.insert_vertex('A'+i);

    g.insert_dir_edge(0, 2);
    g.insert_dir_edge(0, 3);
    g.insert_dir_edge(1, 3);
    g.insert_dir_edge(1, 4);
    g.insert_dir_edge(2, 3);
    g.insert_dir_edge(2, 5);
    g.insert_dir_edge(3, 5);
    g.insert_dir_edge(4, 5);

    g.display();
    g.topo_sort();

    // for (int i = 0; i < 5; i++)
    //     g.insert_vertex('A'+i);

    // g.insert_edge(1, 0);
    // g.insert_edge(2, 0);
    // g.insert_edge(3, 4);

    // printf("연결성분 테스트 그래프\n");
    // g.display();
    // g.reset_visited();
    // g.find_connected_components();

    // for (int i = 0; i < 8; i++)
    //     g.insert_vertex('A'+i);

    // g.insert_edge(0, 1);
    // g.insert_edge(0, 1);
    // g.insert_edge(1, 3);
    // g.insert_edge(2, 3);
    // g.insert_edge(2, 4);
    // g.insert_edge(3, 5);
    // g.insert_edge(4, 6);
    // g.insert_edge(4, 7);
    // g.insert_edge(6, 7);

    // g.display();

    // g.reset_visited();
    // std::cout << std::endl;
    // g.DFS(0);

    // g.reset_visited();
    // std::cout << std::endl;
    // g.BFS(0);



    // char linked = g.is_linked(0, 2) ? 'y' : 'n';

    // std::cout << "Do A and C linked?: " << linked << std::endl;

    std::cout << std::endl;

    std::string file = "graph_test.txt";

    random_graph_generator(10, 20, file);

    read_graph_from_file(file);

    return 0;
}