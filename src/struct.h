#include <vector>
#include <random>
#include <iostream>
#include <algorithm> 

#define DEFAULT_GRAPH -1

using namespace std;


struct Node{
    
        int id;
        vector<Node> adjacent;
        int x;
        int y;
        vector<Node*> adj;
        
       

};

class Graph{
    public :
        vector<Node> nodes;

        void createRandomGraph(int nodesNumber,int p){

            //The nodes number 

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

                    if(randInt<p && i!=j &&!isNodeInVector(nodes[i],nodes[j].adjacent)){          //Prob(i-j)= (p/nodesNumber)
                        nodes[i].adjacent.push_back(nodes[j]);
                        nodes[j].adjacent.push_back(nodes[i]);
                    }
                }
                
            }

        }


        void createRandomGraph(int p=8){

            int nodesNumber=rand() % 25 + 1; //The nodes number 

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

                    if(randInt<p && i!=j &&!isNodeInVector(nodes[i],nodes[j].adjacent)){          //Prob(i-j)= (p/nodesNumber)
                        nodes[i].adjacent.push_back(nodes[j]);
                        nodes[j].adjacent.push_back(nodes[i]);
                    }
                }
                
            }

        }


   
        
        Graph(){
            createRandomGraph(8);
        }

        Graph(int n,int p){
            createRandomGraph(n,p);
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

            a.adj.push_back(&b);b.adj.push_back(&a);
            a.adj.push_back(&c);c.adj.push_back(&a);
            d.adj.push_back(&c);c.adj.push_back(&d);
                
            nodes.push_back(a);
            nodes.push_back(b);
            nodes.push_back(c);
            nodes.push_back(d);
            
        }

        void showGraphInformation() {
			
			for (int i = 0; i < nodes.size(); i++) {
				cout << "\nvert id : " << nodes[i].id;
				if(nodes[i].adj.size()!=0) {
					cout << ", adjiacents : {";

					for (int j = 0; j < nodes[i].adj.size(); j++) {
                        
						//cout << (*nodes[i].adj[j]).id;

						if (j!= nodes[i].adj.size()-1) { cout << ", "; }
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

        bool isIntInVector(int a,vector<int> b){ //Return true if a is in the adjiacent list of b
            for(int i=0;i<b.size();i++){
                if(b[i]==a)return true;
            }
            return false;
        }
        void updateNodePos(int i,int x, int y){
            nodes[i].x=x;nodes[i].y=y;
        }
        bool isNodeInVector(Node a,vector<Node> b){ //Return true if a is in the adjiacent list of b
            for(int i=0;i<b.size();i++){
                if(b[i].id==a.id)return true;
            }
            return false;
        }

        Node getNode(int i){return nodes[i];}
        
        /*void DFS(Node x,int verbose=0){

            vector<int> visitedNodes;

            if(verbose==1){
                cout<<"\n---- Start of the DFS ----\n";
            }
            
            DFSrec(x.id,visitedNodes,verbose);
            cout<<"\n";
        }

        void DFSrec(int x,vector<int> visitedNodes,int verbose=0){

            visitedNodes.push_back(x);
            if(verbose!=0){
                cout<<"\n node "<<x<<" visited";
            }

            for(int i = 0;i<nodes[x].adjacent.size();i++){
                if(!isIntInVector(nodes[x].adjacent[i].id,visitedNodes)){
                    //cout<<"found adjiacent"<<x.adjacent[i].id<<"in "<<x.id<<" list\n";
                    DFSrec(nodes[x].adjacent[i].id,visitedNodes,verbose);
                }
                
            }

        }*/

        void test(Node &a,int i = 0){
            cout<<"\nvert "<<a.id<<" have "<<a.adjacent.size()<<" adj\n";

            if(i==0){
                i=1;test(a.adjacent[0],i);
            }

        }
        

    
};