/*general recursive DFS:
DFS(T):

for nodes vin T:
	// initialize some properties of v
for edges e in T
	// initialize some properties of v
DFS(T,r)

DFS-STRINGS(T, v)
// set some property/update some property of v

if v is a leaf of T
	// set some property/update some property of v
	for every (i,j) in v.suffixIndexes
		v.strings <— v.strings U {i}
for each child u of v:
	DFS(T,u)
	// update some property of v
	v.strings <— v.strings U DFS-STRINGS (T,u)
return v.strings */


bool search(string pattern, string Input, unordered_map <long, Edge> &hash) {
    int len = pattern.length();
    // Starting from 0 we start searching the pattern.
    Edge e = Edge::findEdge(0, pattern[0],hash);
    // index until where we have matched on edge.
    int iter = 0;
    int i = -1;
    if (e.startNode != -1) {
        while(i < len) {
             cout << "Search:\tEdge: " << e.startNode << " " << e.endNode << " : " 
                 << Input[e.startLabelIndex]  << " " << Input[e.endLabelIndex] << " I: " << i << endl;
            // Match the pattern on this edge.
            iter = 0;
            // Match this edge as much as possible.
            while (e.endLabelIndex >= e.startLabelIndex + iter)   
                    {
                         cout << "Search:\tmatching " << Input[e.startLabelIndex + iter] << " " 
                             << pattern[i + iter + 1]
                            << " at index: " << e.startLabelIndex + iter << endl;
                        // If character matches we increase the iterator
                        // otherwise we are done. No match.
                        if (Input[e.startLabelIndex + iter] == pattern[i + iter + 1]) { 
                            iter++;
                            // If we have a match in the middle then we are done.
                            if (i + iter  + 1 >= len) {
                                 cout << "Search:\tWe have a match ending at " 
                                      << e.startLabelIndex + iter  - 1 << endl;
                                return true;
                            }
                        }
                        else {
                            cout << "Search:\tMatch not found, matched only upto index:" << i+iter << endl;
                            return false;     
                        }
                   }
            // We have done all possible matches on this edge. We can proceed
            // only if the entire label matches.
            assert(iter = (e.endLabelIndex - e.startLabelIndex + 1));

            // Now we need to find another edge to match.
            e = Edge::findEdge(e.endNode, pattern[i + iter + 1], hash);
            if (e.startNode == -1) {
                cout << "Search:\tMatch not found, matched only upto " << i + iter  
                     << " " << pattern[i + iter + 1]<< endl;
                return false;    
                }
            i+=(iter);
        }
    }
    cout << "Search:\tMatched :D " << iter << " " << pattern << endl;
    return true;
}


/*

http://www.programming-techniques.com/2012/07/depth-first-search-in-c-algorithm-and.html
#include <iostream>
#include <ctime>
#include <malloc.h> 
using namespace std;
struct node{
    int info;
    struct node *next;
}; 
 
class stack{
    struct node *top;
    public:
        stack();
        void push(int);
        int pop();
        bool isEmpty();
        void display();
}; 
 
stack::stack(){
    top = NULL;
} 
 
void stack::push(int data){
    node *p;
    if((p=(node*)malloc(sizeof(node)))==NULL){
        cout<<"Memory Exhausted";
        exit(0);
    }
    p = new node;
    p->info = data;
    p->next = NULL;
    if(top!=NULL){
        p->next = top;
    }
    top = p;
} 
 
int stack::pop(){
    struct node *temp;
    int value;
    if(top==NULL){
        cout<<"\nThe stack is Empty"<<endl;
    }else{
        temp = top;
        top = top->next;
        value = temp->info;
        delete temp;
    }
    return value;
} 
 
bool stack::isEmpty(){
    return (top == NULL);
} 
 
void stack::display(){
    struct node *p = top;
    if(top==NULL){
        cout<<"\nNothing to Display\n";
    }else{
        cout<<"\nThe contents of Stack\n";
        while(p!=NULL){
            cout<<p->info<<endl;
            p = p->next;
        }
    }
} 
 
class Graph {
    private:
        int n;
        int **A;
    public:
        Graph(int size = 2);
        ~Graph();
        bool isConnected(int, int);
        void addEdge(int x, int y);
        void DFS(int , int);
}; 
 
Graph::Graph(int size) {
    int i, j;
    if (size < 2) n = 2;
    else n = size;
    A = new int*[n];
    for (i = 0; i < n; ++i)
        A[i] = new int[n];
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            A[i][j] = 0;
} 
 
Graph::~Graph() {
    for (int i = 0; i < n; ++i)
    delete [] A[i];
    delete [] A;
} 
 
bool Graph::isConnected(int x, int y) {
    return (A[x-1][y-1] == 1);
} 
 
void Graph::addEdge(int x, int y) {
    A[x-1][y-1] = A[y-1][x-1] = 1;
} 
 
void Graph::DFS(int x, int required){
    stack s;
    bool *visited = new bool[n+1];
    int i;
    for(i = 0; i <= n; i++)
        visited[i] = false;
    s.push(x);
    visited[x] = true;
    if(x == required) return;
    cout << "Depth first Search starting from vertex ";
    cout << x << " : " << endl;
    while(!s.isEmpty()){
        int k = s.pop();
        if(k == required) break;
        cout<<k<<" ";
        for (i = n; i >= 0 ; --i)
            if (isConnected(k, i) && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
    }
    cout<<endl;
    delete [] visited;
} 
 
int main(){
    Graph g(8);
    g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(1, 4);
    g.addEdge(2, 5); g.addEdge(2, 6); g.addEdge(4, 7);
    g.addEdge(4, 8);
    g.DFS(1, 4);
    return 0;
}
*/