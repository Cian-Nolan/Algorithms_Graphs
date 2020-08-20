#include <bits/stdc++.h>

using namespace std;

bool isValid(pair<int,int>& p, vector<vector<char>>& grid){

    int row = p.first;
    int col = p.second;

    return (row >= 0 && row < grid.size() && col >= 0 && col < grid.at(0).size() );

}

int shortestPath(pair<int,int> start, vector<vector<char>>& grid, vector<vector<bool>>& vis)
{
    //check if start point is valid
    if(grid.size() == 0 || !isValid(start, grid)) return -1;

    //explore neighbours
    queue<pair<int,int>> q;
    vector<pair<int,int>> directions = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    q.push(start);
    int moveCount = 0;
    int thisLayerCount = 1; // include start node (+1)
    int nextLayerCount = 0;
    bool flagFound = false;

    while(!q.empty())
    {
        pair<int,int> curr = q.front();
        q.pop();

        //print current node
        cout << "curr: " << curr.first << ", " << curr.second << endl;
        if(grid.at(curr.first).at(curr.second) == 'E')
        {
            cout << "found end at " << curr.first << ", " << curr.second << endl;
            flagFound = true;
            break;
        }

        // run through all possible neighbour nodes
        for(auto d: directions)
        {
            pair<int,int> adjacent = {curr.first+d.first, curr.second+d.second};
            if(isValid(adjacent, grid))
            {
                if(vis.at(adjacent.first).at(adjacent.second) == false && grid.at(adjacent.first).at(adjacent.second) != '#')
                {
                    // if neighbour is valid and is not visited, add to q and mark as visited
                    q.push(adjacent);
                    vis.at(adjacent.first).at(adjacent.second) = true;

                    nextLayerCount++; // the next layer to be serviced
                }
            }
        }

        thisLayerCount--; // have just serviced the queue

        if(thisLayerCount == 0)
        {
            moveCount++;
            thisLayerCount = nextLayerCount;
            nextLayerCount = 0;
        }

    }

    if(flagFound)
    {
        return moveCount+1; // +1 to include last move to E
    }
    else
    {
        return -1;
    }

}

main() 
{
    vector<vector<char>> grid(5, vector<char>(7));
    vector<vector<bool>> vis(5, vector<bool>(7));

    grid[0][0] = 'S';
    grid[0][1] = '.';
    grid[0][2] = '.';
    grid[0][3] = '#';
    grid[0][4] = '.';
    grid[0][5] = '.';
    grid[0][6] = '.';

    grid[1][0] = '.';
    grid[1][1] = '#';
    grid[1][2] = '.';
    grid[1][3] = '.';
    grid[1][4] = '.';
    grid[1][5] = '#';
    grid[1][6] = '.';

    grid[2][0] = '.';
    grid[2][1] = '#';
    grid[2][2] = '.';
    grid[2][3] = '.';
    grid[2][4] = '.';
    grid[2][5] = '.';
    grid[2][6] = '.';

    grid[3][0] = '.';
    grid[3][1] = '.';
    grid[3][2] = '#';
    grid[3][3] = '#';
    grid[3][4] = '#';
    grid[3][5] = '.';
    grid[3][6] = '.';

    grid[4][0] = '#';
    grid[4][1] = '.';
    grid[4][2] = '#';
    grid[4][3] = '.';
    grid[4][4] = 'E';
    grid[4][5] = '.';
    grid[4][6] = '.';

    /*
    Grid: S = start, E = end, # = out of bounds
    find shortest path length

    (S . . # . . .)
    (. # . . . # .)
    (. # . . . . .)
    (. . # # . . .)
    (# . # . E # .) */

    for(auto r : grid)
    {
        for(char elem : r)
        {
            cout << elem << " ";
        }
        cout << endl;
    }

    // start node, graph, visited array
    pair<int,int> start = {0,0};
    cout << "move count: " << shortestPath(start, grid, vis) << endl;

}