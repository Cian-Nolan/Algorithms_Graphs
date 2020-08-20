#include <bits/stdc++.h>

using namespace std;



// produces an order on a directed graph such that all nodes face left->right (used to represent dependencies/ prerequisites)
// i.e. each directed edge from A to B appers in the order A,B
// topological orders ARE NOT UNIQUE
// any graph with a directed cycle has no topological order
// the only type of graph which has a vilid topological ordering is a DIRECTED ACYCLIC GRAPH (DAG)
// N.B. to find if graph is DAG, use Tarjan's connected component algorithm
// N.B. All trees are DAGs 

// method: do DFS on an unvisited node until you reach the end
// on the recursive call (on the way back up the stack),  add the nodes in reverse order
void dfs(char node, map<char,vector<char>>& graph, map<char,bool>& visited, list<char>& topOrder)
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

main() 
{
    map<char,vector<char>> graph; // represented as an adjacency list
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

    // initialise 'visited' map
    map<char,bool> visited;
    for(auto i = graph.begin(); i != graph.end(); i++)
    {
        visited[(*i).first] = false;
    }


    // topological order vector
    list<char> topOrder;

    // start node, graph, visited array
    for(auto node : graph)
    {
        if (visited[node.first] == false)
        {
            dfs(node.first, graph, visited, topOrder);
        }
    }


    // print out top Order vector
    cout << "topological order: " << endl;
    for(auto i : topOrder)
    {
        cout << i << " "; 
    }

}