#include "dijkstras.h"
#include <iostream>
using namespace std;

int main()
{
    Graph G;
    file_to_graph("src/small.txt",  G);
    vector<int> distance(G.numVertices, -1);
    vector<int> prev(G.numVertices, -1);
    distance = dijkstra_shortest_path(G, 0, prev);
    vector<int> path = extract_shortest_path(distance, prev,2);
    print_path(path, distance[2]);
    return 0;
}

