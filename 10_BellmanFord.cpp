#include <bits/stdc++.h>

using namespace std;

class bellman_Ford
{
private:
    map<int,vector<pair<int,int>>> graph;
    vector<int> dist;

public:
    bellman_Ford(map<int,vector<pair<int,int>>> graphIn){
        this->graph = graphIn;
    }
    // pair< node, shortestDistanceFromStartToThatNode >
    vector<int> solve(int);
};

vector<int> bellman_Ford::solve(int start)
{
    // initialise the distance array
    for(int i = 0; i < graph.size(); i++)
    {
        dist.push_back(INT_MAX);
    }
    dist.at(start) = 0;

    // need to relax every edge because in the worst case, a vertex's
    // path length might need V adjustments
    for(int i = 0; i < graph.size(); i++)
    {
        // visit every vertex
        for(auto vertex : graph)
        {
            // visit every edge
            for(auto edge : vertex.second)  
            {
                int currNode = vertex.first;
                int nextNode = edge.first;
                int distanceToCurrNode = dist.at(currNode);
                int tempDistance = distanceToCurrNode + edge.second;
                dist.at(nextNode) = min(dist.at(nextNode), tempDistance);
            }
        }
    }

    cout << "step 1 result: " << endl;
    for(auto i : dist)
    {
        cout << i << endl;
    }


    // now we need to detect negative cycles
    // so repeat the relaxation process
    for(int i = 0; i < graph.size(); i++)
    {
        // visit every vertex
        for(auto vertex : graph)
        {
            // visit every edge
            for(auto edge : vertex.second)  
            {
                int currNode = vertex.first;
                int currDistance = dist.at(currNode);
                int nextNode = edge.first;
                int nextDistance = edge.second;

                int totalDistanceToNext = currDistance + nextDistance;

                if(totalDistanceToNext < currDistance)
                {
                    dist.at(nextNode) = INT_MIN;
                }
            }
        }
    }

    return dist;
}



main() 
{
    // adjacency list graph
    map<int,vector<pair<int,int>>> graph; 

    graph[0] = { {1,5} };
    graph[1] = { {2,20}, {5,30}, {6,60}  };
    graph[2] = { {3,10}, {4,75} };
    graph[3] = { {2,-15} };
    graph[4] = { {9,100} };
    graph[5] = { {4,25}, {6,5}, {8,50} };
    graph[6] = { {7,-50} };
    graph[7] = { {8,-10} };
    graph[8] = { };
    graph[9] = { };

    bellman_Ford b(graph);
    vector<int> result = b.solve(0);

    cout << "shortest distance vector: " << endl;
    for(auto i : result)
    {
        cout << i << " " << endl;
    }
}