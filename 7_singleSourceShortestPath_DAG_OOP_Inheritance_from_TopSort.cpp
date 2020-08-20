#include <bits/stdc++.h>

using namespace std;

// produces an order on a directed graph such that all nodes face left->right
// i.e. each directed edge from A to B appers in the order A,B
// topological orders ARE NOT UNIQUE
// any graph with a directed cycle has no topological order
// the only type of graph which has a vilid topological ordering is a DIRECTED ACYCLIC GRAPH (DAG)
// N.B. to find if graph is DAG, use Tarjan's connected component algorithm
// N.B. All trees are DAGs 
// method: do DFS on an unvisited node until you reach the end
// on the recursive call (on the way back up the stack),  add the nodes in reverse order

class topologicalSortAdjacencyList
{
protected:
    map<char,vector<pair<char,int>>> graph;
    map<char,bool> vis;
    list<char> topOrder;

public:
    topologicalSortAdjacencyList(map<char,vector<pair<char,int>>>); // takes the graph as arguement
    void dfs(char node, map<char,vector<pair<char,int>>>&, map<char,bool>&, list<char>&); // depth first search
    list<char> solve(); // solve top list
};

topologicalSortAdjacencyList::topologicalSortAdjacencyList(map<char,vector<pair<char,int>>> graphIn)
{
    this->graph = graphIn;
    for(auto i : graphIn)
    {
        this->vis[i.first] = false;
    }
    cout << "initialisation done " << endl;
}

list<char> topologicalSortAdjacencyList::solve()
{
    // start node, graph, visited array
    for(auto node : this->graph)
    {
        if (this->vis[node.first] == false)
        {
            dfs(node.first, graph, vis, topOrder);
        }
    }
    return topOrder;
}

void topologicalSortAdjacencyList::dfs(char node, map<char,vector<pair<char,int>>>& graph, map<char,bool>& visited, list<char>& topOrder)
{
    //base case
    auto itFound = graph.find(node);
    if(itFound == graph.end()) return;

    // mark current as visited & print if not already visited
    if(visited[node] == true) return;
    visited[node] = true;
    
    // do dfs on all children
    for(auto child : (*itFound).second)
    {
        dfs(child.second, graph, visited, topOrder); 
        
    }

    // on the way back up the stack
    cout << node << endl;
    topOrder.push_front(node);
}


// single source shortest path depends on getting a top sort firstly, then finding shortest distance to each node
class singleSourceShortestPathAdjacentcyList : public  topologicalSortAdjacencyList
{
public:
    singleSourceShortestPathAdjacentcyList(map<char,vector<pair<char,int>>>);
    int solveShortestDistance(int,int);

};

singleSourceShortestPathAdjacentcyList::singleSourceShortestPathAdjacentcyList(map<char,vector<pair<char,int>>> graphIn) : topologicalSortAdjacencyList(graphIn)
{
    cout << "initialisation done (sssp) " << endl;
    topologicalSortAdjacencyList::solve();
}

int singleSourceShortestPathAdjacentcyList::solveShortestDistance(int start, int finish)
{
    // get the minimum distance between start and each remaining node in the graph
    // on each step, 'relax' the vertex i.e. replace the vertex value with the shortest distance to that point 
    map<char, int> distances;
    for(auto i : this->graph)
    {
        distances[i.first] = INT_MAX;
    }

    // reverse order, also allows '<' operator for comparing interators which is not available for a list
    vector<char> topOrderReversed;
    for(int i = topOrder.size() - 1; i >= 0; i--)
    {
        topOrderReversed.push_back(topOrder.back());
        topOrder.pop_back();
        cout << topOrderReversed.back();
    }
    cout << endl;

    auto it1 = find(topOrderReversed.begin(), topOrderReversed.end(), start);
    auto it2 = find(topOrderReversed.begin(), topOrderReversed.end(), finish);

    auto startIt = min(it1, it2);
    auto finishIt = max(it1, it2);

    map<char,int> minimumIncomingPaths;

    if(startIt != topOrderReversed.end() && finishIt != topOrderReversed.end() )
    { 
        // initialise map
        for(auto i = startIt; i <= finishIt; i++)
        {
            minimumIncomingPaths[*i] = INT_MAX;
        }

        minimumIncomingPaths[*startIt] = 0;

        //cout << "... testing ...." << endl;
            for(auto i : minimumIncomingPaths)
    {
        cout << i.first << " " << i.second << endl;
    }
            //cout << "... testing ...." << endl;


        for(auto node = startIt; node <= finishIt; node++)
        {
            //explore adjacent 
            for(auto adjNode : graph[*node])
            {
                //update the minimum
                int currShortest = minimumIncomingPaths[adjNode.first];
                int shortestUpToHere = minimumIncomingPaths[*(node)];
                //cout << "total shortest for " << adjNode.first << ": " << adjNode.second << " + " << shortestUpToHere << " ... vs:" << currShortest << endl;
                int totalShortest = adjNode.second + shortestUpToHere;
                minimumIncomingPaths[adjNode.first] = min(currShortest, totalShortest);
                //cout << "   total shortest result " << adjNode.first << ": " << minimumIncomingPaths[adjNode.first] << endl;
            }
        }
    }

    for(auto i : minimumIncomingPaths)
    {
        cout << i.first << " " << i.second << endl;
    }

    cout << "min path for " << *startIt << " to " << *finishIt << endl;
    return minimumIncomingPaths[*finishIt];
}


main() 
{

    // adjacency list graph
    // this map indicates adjacentcy and distance
    map<char,vector<pair<char,int>>> graph; 
    graph['a'] = { {'b',3}, {'c',6} };
    graph['b'] = { {'c',4}, {'d',4}, {'e',11}  };
    graph['c'] = { {'d',8}, {'g',11} };
    graph['d'] = { {'e',-4}, {'f',5}, {'g',2} };
    graph['e'] = { {'h',9} };
    graph['f'] = { {'h',1} };
    graph['g'] = { {'h',2} };
    graph['h'] = { };

    // construct a top sort object
    singleSourceShortestPathAdjacentcyList sssp(graph);

    cout << "shortest distance " <<  sssp.solveShortestDistance('a', 'h');

    // solve topological order
    //list<char> topOrder = ts.solve();

    /*// print out top Order vector
    cout << "topological order: " << endl;
    for(auto i : topOrder)
    {
        cout << i << " "; 
    }*/
}