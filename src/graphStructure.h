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
};

class Graph
{

private:
    void createEdge(Node *u, Node *v)
    {
        u->adj.push_back(v);
        v->adj.push_back(u);
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
            for (int j = 0; j < n; j++)
            {
                if ((float)rand() / RAND_MAX < p)
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
        a->adj.push_back(c);
        b->adj.push_back(c);

        nodes.push_back(a);
        nodes.push_back(b);
        nodes.push_back(c);
        nodes.push_back(d);
    }

public:
    vector<Node *> nodes;
    int size;

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
    }
};