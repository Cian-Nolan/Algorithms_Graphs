#include <bits/stdc++.h>

using namespace std;


void dfs(int node, map<int,vector<int>>& graph, vector<bool>& visited)
{
    // check if it exists
    auto it = graph.find(node);
    if(it == graph.end() ) return;

    // check if it was already visited
    if(visited.at(node) == true) return;

    // mark as visited & print
    visited.at(node) = true;
    cout << node << endl;

    //dfs on children
    for(int child : graph.at(node))
    {
        dfs(child, graph, visited);
    }
}

main() 
{

    vector<bool> visited(13, false);
    map<int,vector<int>> graph; // represented as an adjacency list
    graph[0] = {1,9};
    graph[1] = {0,8};
    graph[2] = {3};
    graph[3] = {2,4,5,7};
    graph[4] = {3};
    graph[5] = {3,6};
    graph[6] = {5,7};
    graph[7] = {3,6,8,10,11};
    graph[8] = {1,7,9};
    graph[9] = {0,8};
    graph[10] = {7,11};
    graph[11] = {7,10};
    graph[12] = {};

    // start node, graph, visited array
    dfs(12, graph, visited);

}