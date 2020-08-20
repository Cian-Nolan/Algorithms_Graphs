#include <bits/stdc++.h>

using namespace std;

void bfs(int node, map<int,vector<int>>& graph, vector<bool>& visited)
{
    // check if it exists
    auto it = graph.find(node);
    if(it == graph.end() ) return;

    // print start node
    cout << node << endl;

    //start a queue
    queue<int> q;
    q.push(node);
    int thisLayerCount = 1;
    int nextLayerCount = 0;

    // service the queue;
    while(!q.empty())
    {
        int currNode = q.front();
        q.pop();

        // mark current node as visited & print
        visited.at(currNode) = true;

        // iterate through adjacent nodes
        for(int adjacent : graph.at(currNode))
        {
            // check if it was already visited
            if(visited.at(adjacent) == false)
            {
                q.push(adjacent);
                visited.at(adjacent) = true;
                cout << adjacent << " ";

                // all nodes in the next layer
                nextLayerCount++;
            }
        }

        thisLayerCount--;
        if(thisLayerCount == 0)
        {
            cout << endl;
            thisLayerCount = nextLayerCount;
            nextLayerCount = 0;
        }


    }
}

main() 
{
    vector<bool> visited(13, false);
    map<int,vector<int>> graph; // represented as an adjacency list
    graph[0] = {7,9,11};
    graph[1] = {8,10};
    graph[2] = {3,12};
    graph[3] = {2,4,7};
    graph[4] = {3};
    graph[5] = {6};
    graph[6] = {5,7};
    graph[7] = {0,3,11};
    graph[8] = {1,9,12};
    graph[9] = {0,8,10};
    graph[10] = {1,9};
    graph[11] = {0,7};
    graph[12] = {2,8};

    // start node, graph, visited array
    bfs(12, graph, visited);


}