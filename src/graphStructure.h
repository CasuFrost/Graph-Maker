#include <vector>
#include <random>
#include <iostream>
#define DEFAULT_GRAPH -1
using namespace std;

struct Node{

    int id;
    vector<Node*> adj;
    

};

class Graph{

    
private :

    

    void createDefaultGraph(){
        size=4;
        nodes2 = new Node[size];
        Node a;a.id=48;
        Node b;b.id=96;
        Node c;c.id=97;
        Node d;d.id=98;

        a.adj.push_back(&b);
        a.adj.push_back(&c);
        b.adj.push_back(&c);
        
        nodes2[0]=a;
        nodes2[1]=b;
        nodes2[2]=c;
        nodes2[3]=d;
        
        nodes.push_back(&a);
        nodes.push_back(&b);
        nodes.push_back(&c);
        nodes.push_back(&d);
        
    }

public:

    vector<Node*> nodes;
    int size;
    Node* nodes2 ;

    Graph(int n=DEFAULT_GRAPH){
        if(n==DEFAULT_GRAPH){createDefaultGraph();return;}


    }

    
    void showGraphInformation() {

        

        
    
        //cout<<(*nodes[1]).id<<"\n";
        //cout<<(*nodes[1]).id<<"\n";
        for (int i = 0; i < size; i++) {
            cout << "\nvert id : " << nodes2[i].id;
            if( nodes2[i].adj.size()!=0) {
					cout << ", adjiacents : {";

                    for (int j = 0; j <  (nodes2[i]).adj.size(); j++) {
                        
                        cout<<nodes2[i].adj[j]->id;
						

						if (j!=  nodes2[i].adj.size()-1) { cout << ", "; }
						else { cout << "}"; }
					}
            }
        }
        
        
        
        

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
			cout << "\n";*/
		}
};