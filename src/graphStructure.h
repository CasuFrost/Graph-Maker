#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#define DEFAULT_GRAPH -1
using namespace std;
struct point
{
    int x;
    int y;
};
class Node
{
public:
    bool selected = false;
    point pos;
    int id;
    vector<Node *> adj;
    Node(int v)
    {
        id = v;
        pos.x = 0;
        pos.y = 0;
    }
    void setPos(int x, int y)
    {
        pos.x = x;
        pos.y = y;
    }

    bool visited = false;
};

class Graph
{

private:
    vector<Node *> nearest;

    void calcNodesPos()
    {
        int y = 50;
        int breakLine = 10;
        if (nodes.size() <= 10)
        {
            breakLine = nodes.size() / 2;
        }
        for (int i = 0; i < nodes.size(); i++) // calculate positions
        {

            nodes[i]->setPos(50 + (65 * ((i + 1) % breakLine)), y);

            if ((i + 1) % breakLine == 0)
            {
                y += 50;
            }
        }
    }

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

    void DFSrec(Node *x, vector<bool> vis, bool verbose, int ident = 0, SDL_Renderer *renderer = NULL)
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

        if (renderer)
        {
            cout << "draw";
            /*
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            drawStar(renderer, x->pos.x, x->pos.y, 15);
            SDL_RenderPresent(renderer);
            SDL_Delay(200);
            */
        }

        vis[x->id] = true;
        for (int i = 0; i < x->adj.size(); i++)
        {
            if ((x->adj[i])->visited == false)
            {
                DFSrec(x->adj[i], vis, verbose, ++ident, renderer);
            }
        }
    }

public:
    Node *selected;
    vector<Node *> nodes;

    Graph(int n = 0, float p = 0)
    {
        if (n == 0 && p == 0)
        {
            createDefaultGraph();
            calcNodesPos();
            return;
        }
        createRandomGraph(n, p);
        calcNodesPos();
    }

    void addNode(int x, int y)
    {
        if (nodes.size() != 0)
        {
            Node *nearest = findNearest(x, y);
            if (distForm2Points(x, y, nearest->pos.x, nearest->pos.y) < 50)
            {
                return;
            }
        }

        Node *a = new Node(nodes.size());
        a->pos.x = x;
        a->pos.y = y;
        nodes.push_back(a);
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

    void DFS(Node *x, bool verbose = false, SDL_Renderer *renderer = NULL)
    {
        if (verbose)
            cout << "\n-----START OF THE DFS------\n";
        vector<bool> vis;
        for (int i = 0; i < nodes.size(); i++)
        {
            vis.push_back(false);
        }
        DFSrec(x, vis, verbose, 0, renderer);
        if (verbose)
            cout << "\n-----END OF THE DFS------\n";
    }

    Node *findNear(int x, int y)
    {

        Node *nearest = nodes[0];
        int dist = distForm2Points(x, y, nearest->pos.x, nearest->pos.y);

        for (int i = 1; i < nodes.size(); i++)
        {
            int tmpDist = distForm2Points(nodes[i]->pos.x, nodes[i]->pos.y, x, y);

            if (tmpDist < dist)
            {
                dist = tmpDist;
                nearest = nodes[i];
            }
        }
        if (dist > 40)
            return NULL;
        return nearest;
    }

    Node *findNearest(int x, int y)
    {

        Node *nearest = nodes[0];
        int dist = distForm2Points(x, y, nearest->pos.x, nearest->pos.y);

        for (int i = 1; i < nodes.size(); i++)
        {
            int tmpDist = distForm2Points(nodes[i]->pos.x, nodes[i]->pos.y, x, y);

            if (tmpDist < dist)
            {
                dist = tmpDist;
                nearest = nodes[i];
            }
        }

        return nearest;
    }

    void addNearest(int x, int y)
    {
        Node *n;

        n = findNear(x, y);
        if (!n)
            return;
        nearest.push_back(n);

        n->selected = true;

        selected = n;
        if (nearest.size() == 2)
        {
            // cout << nearest[0]->id << nearest[1]->id;
            createEdge(nearest[0], nearest[1]);
            nearest[0]->selected = false;
            nearest[1]->selected = false;
            selected = NULL;
            nearest.clear();
        }
    }

    int distForm2Points(int x0, int y0, int x1, int y1)
    {
        return sqrt((((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0))));
    }

    void deleteNode(int x, int y)
    {
        Node *n = findNear(x, y);
        if (!n)
        {
            return;
        }

        eraseFromValue(nodes, n);

        for (int i = 0; i < nodes.size(); i++)
        {

            eraseFromValue(nodes[i]->adj, n);
        }
    }

    void eraseFromValue(vector<Node *> &vector, Node *value) // This function delete the given value from the given vector
    {

        int k = -1;
        for (int i = 0; i < vector.size(); i++)
        {
            if (vector[i] == value)
            {
                k = i;
            }
        }
        if (k != -1)
        {
            vector.erase(next(vector.begin(), k));
        }
    }
};