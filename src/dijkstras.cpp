#include "dijkstras.h"
#include <limits.h>
#include <algorithm>
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    size_t n = G.numVertices;
    vector<int> distance(n, INT_MAX);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});
    distance[source] = 0;
    while(!minHeap.empty())
    {
        int u = minHeap.top().second;
        minHeap.pop();
       
        if(visited[u])
            continue;
        visited[u] = true;
        for(Edge e: G[u])
        {
            int v = e.dst;
            int weight = e.weight;
            if(!visited[v] && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                minHeap.push({distance[v], v});
            }
        }

    }
    return distance;
}
vector<int> extract_shortest_path(const vector<int>&  distances, const vector<int>& previous, int destination)
{
    if(destination < 0 || destination >=distances.size()||distances[destination] == INF)
        return {};
    vector<int> path;
    int curr = destination;
    while(curr > -1)
    {
        path.push_back(curr);
        curr = previous[curr];
    }
    if(path.back() == -1||path.empty())
        return {};
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total)
{
    for(int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " " ;
    }
    cout <<endl;
    cout << "Total cost is " << total << endl;
}
