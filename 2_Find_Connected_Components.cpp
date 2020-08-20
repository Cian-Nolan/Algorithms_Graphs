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

void findConnected(int node, map<int,vector<int>>& graph, vector<bool>& visited, vector<int>& group)
{
    if(group.empty())
    {
        group.push_back(1);
    }
    else
    {
        group.push_back(group.back()+1);
    }

    dfs(node, graph, visited);

    cout << "----- group " << group.back() << " end" << endl;
}

main() 
{
    // find connected components, return number of groups
    vector<int> groups;
    vector<bool> visited(18, false);
    map<int,vector<int>> graph; // represented as an adjacency list
    graph[0] = {4,8,13,14};
    graph[1] = {5};
    graph[2] = {9,15};
    graph[3] = {9};
    graph[4] = {0,8};
    graph[5] = {1,16,17};
    graph[6] = {7,11};
    graph[7] = {6,11};
    graph[8] = {0,4,14};
    graph[9] = {2,3,15};
    graph[10] = {15};
    graph[11] = {6,7};
    graph[12] = {};
    graph[13] = {0,14};
    graph[14] = {0,8,13};
    graph[15] = {2,9,10};
    graph[16] = {5};
    graph[17] = {5};

    // start node, graph, visited array
    for(int i = 0; i < graph.size(); i++)
    {
        if (visited.at(i) == false)
        {
            findConnected(i, graph, visited, groups);
        }
    }
}