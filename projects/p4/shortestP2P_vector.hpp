#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX

using namespace std;

class ShortestP2P {
    
    typedef struct{
        unsigned point;
        int dis;
    } Edge;
    typedef struct{
        vector<list<Edge>> to;
        vector<list<Edge>> from;
    } Conj;
    unsigned V = 0;
    Conj conj;

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
    for (auto i = conj.to[a].begin(); i!=conj.to[a].end(); i++){
        for (auto j=conj.from[a].begin(); j!=conj.from[a].end(); j++){
            update(j->point, i->point, i->dis+j->dis);
        }
    }
}

void ShortestP2P::update(unsigned start, unsigned end, int weight){
    if (start == end && weight<0) invalid_graph();
    auto i=conj.to[start].begin();
    for (; i!=conj.to[start].end();i++){
        if (i->point==end){
            if (weight<i->dis) i->dis = weight;
            break;
        }
    }
    if (i==conj.to[start].end()){
        conj.to[start].push_back({end, weight});
        conj.from[end].push_back({start, weight});
        return;
    }
    
    i=conj.from[end].begin();
    for (; i!=conj.from[end].end();i++){
        if (i->point==start){
            if (weight<i->dis) i->dis = weight;
            break;
        }
    }
}

void ShortestP2P::readGraph(){
    unsigned int E;
    cin>>V>>E;
    conj.from.resize(V);
    conj.to.resize(V);
    for (unsigned i=0; i<E; i++){
        unsigned start,end;
        int dis;
        cin>>start>>end>>dis;
        conj.to[start].push_back({end, dis});
        conj.from[end].push_back({start, dis});
    }

    for (unsigned i=0; i<V; i++) centerIteration(i);
}

void ShortestP2P::distance(unsigned int A, unsigned int B){
    for (auto i = conj.to[A].begin(); i != conj.to[A].end(); i++){
        if(i->point == B){
            cout<<i->dis<<endl;
            return;
        }
    }
    cout << "INF" << endl;
}