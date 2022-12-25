#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX

using namespace std;

class ShortestP2P {
    unsigned int V;
    vector<vector<int>> conj;

    void centerIteration(unsigned origin);

    void update(unsigned start, unsigned end, int weight);

    void invalid_graph() {cout << "Invalid graph. Exiting." << endl; exit(0);}
public:
    ShortestP2P() {}

    /* Read the graph from stdin
    * The input has the following format:
    *
    * Firstline: 1 unsigned int, the total number of verticies, X.
    * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
    * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
    *
    * Example:
    * 4
    * 4
    * 0 1 5
    * 1 2 -1
    * 2 3 4
    * 3 1 6
    * 
    * 
    * 
    *
    * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
    * 
    * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
    * cout << "Invalid graph. Exiting." << endl;
    *
    * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
    */
    void readGraph();

    /* Input: 2 vertices A and B
    * Output: distance between them.
    * cout << dist << endl;
    *
    * When the A and B are not connected print INF:
    * cout << "INF" << endl;
    */
    void distance(unsigned int A, unsigned int B);

};


void ShortestP2P::centerIteration(unsigned a){
    for (unsigned i = 0; i<V; i++){
        if (a!=i){
            for (unsigned j=0; j<V; j++){
                if (i==j && conj[i][j]<0) invalid_graph();
                if(a!=j && conj[i][a]!=INF && conj[a][j]!=INF && conj[i][a]+conj[a][j]<conj[i][j]) {
                    conj[i][j] = conj[i][a]+conj[a][j];
                }
            }
        }
    }
}


void ShortestP2P::readGraph(){
    unsigned int E;
    cin>>V>>E;
    conj.resize(V, vector<int>(V, INF));
    for (unsigned i=0; i<E; i++){
        unsigned start,end;
        int dis;
        cin>>start>>end>>dis;
        conj[start][end] = dis;
    }

    for (unsigned i=0; i<V; i++) centerIteration(i);
}

void ShortestP2P::distance(unsigned int A, unsigned int B){
    if(conj[A][B]!=INF) cout<<conj[A][B]<<endl;
    else cout << "INF" << endl;
}