#include <vector>
#include <random>
#include <iostream>

#define DEFAULT_GRAPH -1
using namespace std;

class Node
{
public:
    int id;
    vector<Node *> adj;
    Node(int v)
    {
        id = v;
    }
    bool visited = false;
};

class Graph
{

private:
    bool isTheNodesConnected(Node *u, Node *v)
    {
        bool a = false;
        bool b = false;
        for (int i = 0; i < u->adj.size(); i++)
        {
            if (u->adj[i]->id == v->id)
            {
                a = true;
            }
        }
        for (int i = 0; i < v->adj.size(); i++)
        {
            if (v->adj[i]->id == u->id)
            {
                b = true;
            }
        }

        return a || b;
    }

    void createEdge(Node *u, Node *v)
    {
        if (!isTheNodesConnected(u, v))
        {
            u->adj.push_back(v);
            v->adj.push_back(u);
        }
    }

    void createRandomGraph(int n = 10, float p = 0.3)
    {
        // This function create a graph with n nodes, for every couple of nodes u and v, exists an edge (u,v) with probability p
        for (int i = 0; i < n; i++)
        {
            Node *a = new Node(i);
            nodes.push_back(a);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (((float)rand() / RAND_MAX < p) && i != j) // Probabilità che ci sia un arco è 1-p
                {
                    createEdge(nodes[i], nodes[j]);
                }
            }
        }
    }

    void createDefaultGraph()
    {
        Node *a = new Node(1);
        Node *b = new Node(2);
        Node *c = new Node(3);
        Node *d = new Node(4);

        a->adj.push_back(b);
        b->adj.push_back(a);
        a->adj.push_back(c);
        c->adj.push_back(a);
        b->adj.push_back(c);
        c->adj.push_back(b);
        d->adj.push_back(c);
        c->adj.push_back(d);

        nodes.push_back(a);
        nodes.push_back(b);
        nodes.push_back(c);
        nodes.push_back(d);
    }

    void DFSrec(Node *x, vector<bool> vis, bool verbose, int ident = 0)
    {
        if (verbose)
        {
            for (int i = 0; i < ident; i++)
            {
                cout << " | ";
            }
            cout << "currently on node : " << x->id << "\n";
        }
        x->visited = true;
        vis[x->id] = true;
        for (int i = 0; i < x->adj.size(); i++)
        {
            if ((x->adj[i])->visited == false)
            {
                DFSrec(x->adj[i], vis, verbose, ++ident);
            }
        }
    }

public:
    vector<Node *> nodes;

    Graph()
    {
        createDefaultGraph();
    }

    Graph(int n = DEFAULT_GRAPH)
    {
        if (n == DEFAULT_GRAPH)
        {
            createDefaultGraph();
            return;
        }
    }

    Graph(int n = 10, float p = 0.3)
    {
        createRandomGraph(n, p);
    }

    void showGraphInformation()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << "\nvert id : " << nodes[i]->id;
            if (nodes[i]->adj.size() != 0)
            {
                cout << ", adjiacents : {";
            }
            for (int j = 0; j < nodes[i]->adj.size(); j++)
            {

                cout << nodes[i]->adj[j]->id;

                if (j != nodes[i]->adj.size() - 1)
                {
                    cout << ", ";
                }
                else
                {
                    cout << "}";
                }
            }
        }
        cout << "\n";
    }

    void DFS(Node *x, bool verbose = false)
    {
        if (verbose)
            cout << "\n-----START OF THE DFS------\n";
        vector<bool> vis;
        for (int i = 0; i < nodes.size(); i++)
        {
            vis.push_back(false);
        }
        DFSrec(x, vis, verbose);
        if (verbose)
            cout << "\n-----END OF THE DFS------\n";
    }
};