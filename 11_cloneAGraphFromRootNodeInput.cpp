#include <bits/stdc++.h>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};



//bfs for display of the returned 
void bfs(Node* root)
{
    set<Node*> vis;
    queue<Node*> q;
    q.push(root);
    int thisLayer = 1, nextLayer = 0;

    while(!q.empty())
    {
        Node* currNode = q.front();
        q.pop();
        vis.insert(currNode);

        cout << currNode->val << " ";

        for(auto adj : currNode->neighbors)
        {
            if(vis.find(adj) == vis.end())
            {
                q.push(adj);
                vis.insert(adj); 
            }
            nextLayer++;
        }
        thisLayer--;

        if(thisLayer == 0)
        {
            cout << endl;
            thisLayer = nextLayer;
            nextLayer = 0;
        }
    }
}


Node* cloneGraph(Node* root)
{
    unordered_map<Node*, Node*> org_copy; // original to copy map

    //start
    org_copy[root] = new Node(root->val);

    // root VAL added, now expolore for neighbours

    queue<Node*> q;
    q.push(root);

    while(!q.empty())
    {
        Node* currNode = q.front();
        q.pop();

        for(auto adj : currNode->neighbors)
        {
            if(org_copy.find(adj) == org_copy.end())
            {
                //if neighbour is not in the map already, create obj and add to map
                org_copy[adj] = new Node(adj->val);

                // now add to queue so that its neighbours will be processed later
                q.push(adj);  

            }
              
            // if the neighbour is already in the map, then just update the currNode
            //neighbor table WITH A REFERENCE TO THE ADJ NODE
            org_copy[currNode]->neighbors.push_back(org_copy[adj]);

        }

    }

    return org_copy[root];
}







main() 
{
    /*
    *  (0) - (1)
    *   |     |
    *  (2) - (3)
    *   
    */
    Node* n0 = new Node(0);
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    n0->neighbors = {n1,n2};
    n1->neighbors = {n0,n3};
    n2->neighbors = {n0,n3};
    n3->neighbors = {n1,n2};

    Node* ret = cloneGraph(n0);

    cout << "returned node: " << endl;
    cout << ret->val << endl;

    // just for display
    cout << "bfs result " << endl;
    bfs(ret);

}