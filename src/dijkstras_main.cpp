#include "dijkstras.h"
#include <iostream>
using namespace std;

int main()
{
    Graph G;
    file_to_graph("src/small.txt",  G);
    vector<int> distance(G.numVertices, -1);
    vector<int> prev(G.numVertices, -1);
    dijkstra_shortest_path(G, 0, prev);
    extract_shortest_path(distance, prev,2 );
    print_path(prev, 2);
    return 0;
}

