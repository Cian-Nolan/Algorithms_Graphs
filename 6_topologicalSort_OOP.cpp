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
private:
    map<char,vector<char>> graph;
    map<char,bool> vis;
    list<char> topOrder;

public:
    topologicalSortAdjacencyList(map<char,vector<char>>); // takes the graph as arguement
    void dfs(char node, map<char,vector<char>>&, map<char,bool>&, list<char>&); // depth first search
    list<char> solve(); // solve top list
};

topologicalSortAdjacencyList::topologicalSortAdjacencyList(map<char,vector<char>> graphIn)
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

void topologicalSortAdjacencyList::dfs(char node, map<char,vector<char>>& graph, map<char,bool>& visited, list<char>& topOrder)
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
        dfs(child, graph, visited, topOrder); 
        
    }

    // on the way back up the stack
    cout << node << endl;
    topOrder.push_front(node);
}

/* *************** top Sort Class End *************** */

main() 
{
    // adjacency list graph
    map<char,vector<char>> graph; 
    graph['a'] = {'d'};
    graph['b'] = {'d'};
    graph['c'] = {'a','b'};
    graph['d'] = {'g','h'};
    graph['e'] = {'a','d','f'};
    graph['f'] = {'j','k'};
    graph['g'] = {'i'};
    graph['h'] = {'i','j'};
    graph['i'] = {'l'};
    graph['j'] = {'l','m'};
    graph['k'] = {'j'};
    graph['l'] = {};
    graph['m'] = {};

    // construct a top sort object
    topologicalSortAdjacencyList ts(graph);

    // solve topological order
    list<char> topOrder = ts.solve();

    // print out top Order vector
    cout << "topological order: " << endl;
    for(auto i : topOrder)
    {
        cout << i << " "; 
    }

}