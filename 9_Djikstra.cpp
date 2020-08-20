#include <bits/stdc++.h>

using namespace std;

// operator overload - sorts the priority queue by shortest distance (NESTED CLASS)
class pq_Order
{
public:
    bool operator() (pair<int,int> p1, pair<int,int> p2)
    {
        return p1.second > p2.second;
    }
};

class dijkstra_Lazy
{
private:
    map<int,vector<pair<int,int>>> graph;

public:
    dijkstra_Lazy(map<int,vector<pair<int,int>>> graphIn){
        this->graph = graphIn;
    }
    // pair< node, shortestDistanceFromStartToThatNode >
    vector<int> solve(int);
};

vector<int> dijkstra_Lazy::solve(int start)
{
    // initialise the distance array
    vector<int> dist;
    for(int i = 0; i < graph.size(); i++)
    {
        dist.push_back(INT_MAX);
    }
    dist.at(start) = 0;

    //visisted array
    vector<bool> visited(dist.size()); 

    // initilise prority queue
    priority_queue<pair<int,int>, vector<pair<int,int>>, pq_Order> pq;
    pq.push({start,0});
    visited.at(start) = true;

    //service the queue
    while(!pq.empty())
    {
        // consider the current node to be a 'base' which you start from to check
        // all adjacent nodes. when we're done with the base, we move on to the
        // next most-promising neighbour and start a new base  
        // since we don't want to go backwards, we need to mark each base as 
        // visited (but not each neighbour until that neighbour becomes a base)
        // ** You cannot get a shorter path by revisiting
        // a node you have already visited before.

        // extract the minimum element from the queue, mark as visited
        int currNode = pq.top().first;
        int currDistance = pq.top().second;
        pq.pop();
        visited.at(currNode) = true; 

        // go through the adjacency list, check for shorter distance to nodes
        for(pair<int,int> adj : graph.at(currNode))
        {
            int nextNode = adj.first;
            int nextDistance =  adj.second;

            int shortestDistancetoCurrent = dist.at(currNode);
            int tempDistance = shortestDistancetoCurrent +  nextDistance;

            // if the next node provides a shorter path, then add it to the queue
            // Relax edge by updating minimum cost if applicable.
            if(visited.at(nextNode) == false)
            {
                if(tempDistance < dist.at(nextNode))
                {
                    dist.at(nextNode) = min(dist.at(nextNode), tempDistance);
                    pq.push(adj);
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

    graph[0] = { {1,4}, {2,1} };
    graph[1] = { {3,1} };
    graph[2] = { {1,2}, {3,5} };
    graph[3] = { {4,3} };
    graph[4] = {};

    dijkstra_Lazy d(graph);
    vector<int> result = d.solve(0);

    cout << "shortest distance vector: " << endl;
    for(auto i : result)
    {
        cout << i << " " << endl;
    }
}