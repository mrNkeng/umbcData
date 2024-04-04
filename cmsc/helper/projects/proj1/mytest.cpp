#include "graph.h"

class Tester{ // Tester class to implement test functions
    public:
    
};

int main(){
    //cout << "hello" << endl;
    Graph aGraph("testdata.txt"); // Test building a graph by the alternative constructor for a normal case.
    aGraph.findPath(0,5);
    cout << "Finding the path from node 0 to node 5: " << endl;
    aGraph.dump();

    Graph bGraph; // Test creating an empty graph object.
    bGraph.findPath(3,6); // Test finding a path which does not exist in the graph.
    cout << "Finding the path from node 1 to node 14 in an empty Graph object: " << endl;
    bGraph.dump();

    bGraph.buildGraph("testdata.txt");// Test building a graph in an empty Graph object.

    cout << "Trying to build a graph with an empty graph object" << endl;

    aGraph.findPath(4,0); //Test finding a path which exists in the graph.
    cout << "Finding the path from node 4 to node 0: " << endl;
    aGraph.dump();

    aGraph.findPath(2,2); //Test finding a path from a node to itself.
    cout << "Finding the path from node 2 to itself: " << endl;
    aGraph.dump();

    aGraph.findPath(16,2); //Test finding a path in which the start node does not exist.
    cout << "Finding the path from node 2 to itself: " << endl;
    aGraph.dump();

     aGraph.findPath(2,16); //Test finding a path in which the end node does not exist.
    cout << "Finding the path from node 2 to itself: " << endl;
    aGraph.dump();
    
    

    
    
    

    
    return 0;
}