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

    void showGraphInformation()
    {

        cout << (nodes[1])->id << endl;
        cout << (nodes[1])->id << endl;
        cout << (nodes[0])->id << endl;
        cout << (nodes[1])->id << endl;
        /*for (int i = 0; i < size; i++) {
            cout << "\nvert id : " << nodes2[i].id;
            if( nodes2[i].adj.size()!=0) {
                    cout << ", adjiacents : {";

                    for (int j = 0; j <  (nodes2[i]).adj.size(); j++) {

                        cout<<nodes2[i].adj[j]->id;


                        if (j!=  nodes2[i].adj.size()-1) { cout << ", "; }
                        else { cout << "}"; }
                    }
            }
        }*/

        /*for (int i = 0; i < nodes.size(); i++) {
            cout << "\nvert id : " << (*nodes[i]).id;



            if( (*nodes[i]).adj.size()!=0) {
                cout << ", adjiacents : {";

                for (int j = 0; j <  (*nodes[i]).adj.size(); j++) {

                    cout << (* (*(nodes[i])).adj[j]).id;

                    if (j!=  (*nodes[i]).adj.size()-1) { cout << ", "; }
                    else { cout << "}"; }
                }
            }
        }
        cout << endl;*/
    }
};