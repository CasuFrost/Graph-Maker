#include <vector>
#include <random>
#include <iostream>
#include <algorithm> 

#define DEFAULT_GRAPH -1

using namespace std;

class Node{
    public:
        int id;
        vector<Node> adjacent;
        int visited=0;

};

class Graph{
    private :
        vector<Node> nodes;
        vector<int> Vis;


        void createRandomGraph(int p=8){

            int nodesNumber=rand() % 50 + 1; //The nodes number 

            //Create nodes
            for(int i = 0;i<nodesNumber;i++){
                Node a;
                a.id=i;
                nodes.push_back(a);
            }

            //Create edges
            for(int i = 0;i<nodesNumber;i++){
                for(int j = 0;j<nodesNumber;j++){

                    int randInt=rand() % 100 + 1;

                    if(randInt<p){          //Prob(i-j)= (p/nodesNumber)
                        nodes[i].adjacent.push_back(nodes[j]);
                    }
                }
                
            }

        }


    public:
        
        Graph(){
            createRandomGraph(8);
        }

        Graph(int p){

            if(p==-1){

                createDefaultGraph();
                
                return;

            }

            
            createRandomGraph(p);
        }

        void createDefaultGraph(){
            Node a; a.id=0;
            Node b; b.id=1;
            Node c; c.id=2;
            Node d; d.id=3;
            a.adjacent.push_back(b); a.adjacent.push_back(c);
            d.adjacent.push_back(c);
                
            nodes.push_back(a);
            nodes.push_back(b);
            nodes.push_back(c);
            nodes.push_back(d);
            
            setupGraph();
            for (int i = 0; i < nodes.size(); i++) {
                Vis.push_back(0);
            }

        }

        void showGraphInformation() {
			
			for (int i = 0; i < nodes.size(); i++) {
				cout << "\nvert id : " << nodes[i].id;
				if(nodes[i].adjacent.size()!=0) {
					cout << ", adjiacents : {";
					for (int j = 0; j < nodes[i].adjacent.size(); j++) {
						cout << nodes[i].adjacent[j].id;
						if (j!= nodes[i].adjacent.size()-1) { cout << ", "; }
						else { cout << "}"; }
					}
				}
			}
			cout << "\n";
		}


        void setupGraph(){ //This function fill in the correct way  the adjacent list of all the nodes
            for(int i=0;i<nodes.size();i++){
                for(int j=0;j<nodes[i].adjacent.size();j++){

                    int check=0;

                    Node a = nodes[i];
                    Node b = nodes[i].adjacent[j];

                    for(int k = 0;k<b.adjacent.size();k++){
                        if(a.id==b.adjacent[k].id){
                            check=1;
                            
                            
                        }
                    }

                    if(check==0){
                        //cout<<"\nadded "<<nodes[i].id<<" in "<<nodes[i].adjacent[j].id<<" adj. List";
                        int container = nodes[i].adjacent[j].id;
                        int added = nodes[i].id;
                        nodes[container].adjacent.push_back(nodes[added]);
                    }
                    
                    

                }
            }
            
            //cout<<"\n-----------------\n\n";
            
        }

        void DFS(){
            cout<<"\n";
            DFSrec(nodes[0]);
        }

        void DFSrec(Node x){
            
            x.visited=1;
            cout<<"\n il nodo "<<x.id<<" e' stato visitato,gli adiacenti del nodo "<<x.id<<" sono :\n";
            
             for(int k = 0;k<x.adjacent.size();k++){
                
                cout<<x.adjacent[k].id<<"\n";
                
                if(x.adjacent[k].visited==0){
                    DFSrec(x.adjacent[k]);
                }
                
             }
        }

    
};