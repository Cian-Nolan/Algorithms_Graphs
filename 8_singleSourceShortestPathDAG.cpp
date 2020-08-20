#include <bits/stdc++.h>

using namespace std;


class singleSourceShortestPathDAG
{
private:
    map<char,vector<pair<char,int>>> graph;
    map<char,bool> vis;
    list<char> topOrder;
    vector<char> reverseTopOrder;

    // depth first search - used to get topological order
    void dfs(char); 
    // solve top order
    void solveTopologicalSort(); 

public:
    singleSourceShortestPathDAG(map<char,vector<pair<char,int>>>); // takes the graph as arguement
    int solveShortestDistance(char,char);
    
};
//constructer
singleSourceShortestPathDAG::singleSourceShortestPathDAG(map<char,vector<pair<char,int>>> graphIn)
{
    // initialise visited container
    this->graph = graphIn;
    for(auto i : graphIn)
    {
        this->vis[i.first] = false;
    }

    solveTopologicalSort();

    cout << "initialisation done " << endl;
}

void singleSourceShortestPathDAG::solveTopologicalSort()
{
    // iterate through nodes
    for(auto node : this->graph)
    {
        if (this->vis[node.first] == false)
        {
            dfs(node.first);
        }
    }
}

void singleSourceShortestPathDAG::dfs(char node)
{
    //base case
    auto itFound = graph.find(node);
    if(itFound == graph.end()) return;

    // mark current as visited & print if not already visited
    if(vis[node] == true) return;
    vis[node] = true;
    
    // do dfs on all children
    for(auto child : (*itFound).second)
    {
        dfs(child.second);  
    }
    // on the way back up the stack
    //cout << node << endl;
    topOrder.push_front(node);  // !!!!!!!

}

int singleSourceShortestPathDAG::solveShortestDistance(char start, char finish)
{
    // get the minimum distance between start and each remaining node in the graph
    // on each step, 'relax' the vertex i.e. replace the vertex value with the shortest distance to that point 
    // this is done by using the map  minOfIncomingPaths
    map<char,int> minOfIncomingPaths;

    // check if function call is valid
    // assign reverseTopOrder array
    for(int i = topOrder.size()-1; i >= 0; i--)
    {
        reverseTopOrder.push_back(topOrder.back());
        topOrder.pop_back();
    }

    vector<char>::iterator startIt = this->reverseTopOrder.begin(), finishIt = this->reverseTopOrder.end();
    vector<char>::iterator  it1 = find(reverseTopOrder.begin(), reverseTopOrder.end(), start);
    vector<char>::iterator  it2 = find(reverseTopOrder.begin(), reverseTopOrder.end(), finish);

    bool flagNegativeDistance = false; // used to output negative distance at the end;
    if(it1 == it2 || it1 == reverseTopOrder.end() || it2 == reverseTopOrder.end() ){
        return 0;
    }
    else if (it1 < it2){
        startIt = it1;
        finishIt = it2;
    }
    else{
        startIt = it2;
        finishIt = it1;
        flagNegativeDistance = true;       
    }

    // initialise map of incoming paths
    for(auto i = startIt; i <= finishIt; i++)
    {
        minOfIncomingPaths[*i] = INT_MAX;
    }

    minOfIncomingPaths[*startIt] = 0; // <- Zero incoming paths to start node

    // iterate through the whole range of nodes 
    for(auto node = startIt; node <= finishIt; node++)
    {
        //explore adjacency list to find minimum distance to each node 
        for(auto adjNode : graph[*node])
        {
            int shortest_thisNode = minOfIncomingPaths[*(node)];
            int shortest_nextNode = minOfIncomingPaths[adjNode.first];
            int distance_toNext = adjNode.second;
            int shortest_nextNodeIncludingThisNode = shortest_thisNode + distance_toNext;

            minOfIncomingPaths[adjNode.first] = min(shortest_nextNode, shortest_nextNodeIncludingThisNode);
        }
    }   

    for(auto i : minOfIncomingPaths)
    {
        cout << i.first << " " << i.second << endl;

    }

    return minOfIncomingPaths[*finishIt];
}
/// class end

main() 
{
    // adjacency list graph
    map<char,vector<pair<char,int>>> graph; 
    graph['a'] = { {'b',3}, {'c',6} };
    graph['b'] = { {'c',4}, {'d',4}, {'e',11}  };
    graph['c'] = { {'d',8}, {'g',11} };
    graph['d'] = { {'e',-4}, {'f',5}, {'g',2} };
    graph['e'] = { {'h',9} };
    graph['f'] = { {'h',1} };
    graph['g'] = { {'h',2} };
    graph['h'] = { };

    singleSourceShortestPathDAG sssp(graph);
    int result = sssp.solveShortestDistance('a', 'h');
    cout << "shortest distance " <<  result << endl;

}