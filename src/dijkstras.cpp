#include "dijkstras.h"
#include <limits.h>
#include <algorithm>
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    size_t n = G.numVertices;
    vector<int> distance(n, INT_MAX);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    distance[source] = 0;
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
       
        if(visited[u])
            continue;
        visited[u] = true;
        for(const Edge& e: G[u])
        {
            int v = e.dst;
            int weight = e.weight;
            if(!visited[v] && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }

    }
    return distance;
}
vector<int> extract_shortest_path(const vector<int>&  distances, const vector<int>& previous, int destination)
{
    if(distances[destination] == INF)
        return {};
    vector<int> path;
    int curr = destination;
    while(curr != -1)
    {
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total)
{

    vector<int> path;
    if(total >=0 && total < v.size())
    {
        int curr = total;
        while(curr != -1)
        {
            path.push_back(curr);
            if(curr >= v.size())break;
            int next= v[curr];
            if(next == curr)
                break;
            curr = next;
        }
    }
    
    for(int i = path.size()-1; i >=0; --i)
    {
        cout << path[i] << " " ;
    }
    cout <<endl;
    cout << "Total cost is " << total << endl;
}
