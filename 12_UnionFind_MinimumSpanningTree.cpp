#include <bits/stdc++.h>

using namespace std;


class unionFind
{
private:
    vector<int> sets;
    vector<int> numberOfComponents;
    int numberOfSets;

    int getRoot(int A);

public:
    unionFind(int size);
    bool find(int A, int B);
    void unify(int A, int B);
    void display();
};

unionFind::unionFind(int size)
{
    for(int i = 0; i < size; i++)
    {
        sets.push_back(i);
        numberOfComponents.push_back(1);
    }
    numberOfSets = size;
}

int unionFind::getRoot(int A)
{
    int root = A;
    while(root != sets.at(root))
    {
        root = sets.at(root);
    }

    // path compression
    int path = A;
    while(sets.at(path) != root)
    {
        int next = sets.at(path);
        sets.at(path) = root;
        path = next;
    }
    return root;
}

bool unionFind::find(int A, int B)
{
    // starting point
    int rootA = getRoot(A);
    int rootB = getRoot(B);
    
    return (rootA == rootB);
}

void unionFind::unify(int A, int B)
{
    int rootA = getRoot(A);
    int rootB = getRoot(B);
    int rootAsize = numberOfComponents.at(rootA);
    int rootBsize = numberOfComponents.at(rootB);
 
    if(rootA != rootB)
    {
        if( rootAsize >= rootBsize)
        {
            sets.at(rootB) = rootA;
            numberOfComponents.at(rootA) += numberOfComponents.at(rootB);
        }
        else
        {
            sets.at(rootA) = rootB;
            numberOfComponents.at(rootB) += numberOfComponents.at(rootA);  
        }
        numberOfSets--;
        return;
    }
    cout << "already the same.. " << endl;
}

void unionFind::display()
{
    for(auto i : sets)
    {
        cout << i << " ";
    }
    cout << endl;
    for(auto i : numberOfComponents)
    {
        cout << i << " ";
    }
    cout << endl;
}


class edge
{
public:
    char to, from;
    int weight;
    edge(int _to, int _from, int _weight)
    {
        this->to = _to;
        this->from = _from;
        this->weight = _weight;
    }
};

bool sortByWeight(edge e1, edge e2)
{
    return e1.weight < e2.weight;
}

main() 
{
    vector<edge> edgeList, result;
    map<char,vector<pair<int,int>>> graph; 
    graph['a'] = { {'b',5}, {'d',9}, {'e',1}  };
    graph['b'] = { {'a',5}, {'d',2}, {'c',4}  };
	graph['c'] = { {'b',4}, {'h',4}, {'i',1}, {'j',8}  };
    graph['d'] = { {'a',9}, {'b',2}, {'h',2}, {'g',11},{'f',5}, {'e',2} };
	graph['e'] = { {'a',1}, {'d',2}, {'f',1}  };
    graph['f'] = { {'e',1}, {'d',5}, {'g',7}  };
	graph['g'] = { {'f',7}, {'d',11}, {'h',1}, {'i',4}  };
    graph['h'] = { {'d',2}, {'c',4}, {'i',6}, {'g',1}  };
	graph['i'] = { {'g',4}, {'h',6}, {'c',1}, {'j',6}  };
    graph['j'] = { {'i',6}, {'c',2} };

    // initialise the edge list
    for(auto i : graph)
    {
        for(auto j : i.second)
        {
            edge e(i.first, j.first, j.second);
            edgeList.push_back(e);
        }
    }

    // sort the edge list by weight
    std::sort(edgeList.begin(),edgeList.end(), sortByWeight);

    // map union find integer array to the character node input (BIJECTION)
    /*
        a -> 0, b -> 1, c -> 2, ..
    */
    map<char,int> m;
    int j = 0;
    for(auto i : graph)
    {
        m[i.first] = j;
        j++;
    }
    
    int sum = 0;
    // create a union find 
    unionFind uf(edgeList.size());
    for(auto edge : edgeList)
    {
        if( !(uf.find(m[edge.from], m[edge.to])) )
        {
            uf.unify(m[edge.from], m[edge.to]);
            result.push_back(edge);
            sum += edge.weight;

            cout << "union " << edge.from << " " << edge.to << ", weight: " << edge.weight << ", sum: " << edge.weight  << endl;
        }
    }

    //uf.display();

    cout << "result " << endl;

    for(auto i : result)
    {
        cout << i.from << ", " << i.to << ", " << i.weight << endl;
    }
    cout << "-----" << endl;
    cout << sum << endl;

}
