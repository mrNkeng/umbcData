//blah
//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
#include "graph.h"
Graph::Graph(){
    m_numNodes = 0;
    m_dataFile = "";
    m_head = nullptr;
    //m_path = new stack <int>;

}

Graph::Graph(string dataFile){
    m_dataFile = dataFile;
    loadData();
}

Graph::~Graph(){
    this->clearGraph();
}

void Graph::loadData(){
    int numNodes;
    int node, n, e, s, w; 
    ifstream dataFile;
    dataFile.open(m_dataFile);
    if (dataFile.is_open()) {
        dataFile >> numNodes;
        m_numNodes = numNodes;
        for (int i = 0; i < numNodes; i++) {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open
        //please note: not all platforms are providing the same message
        cerr << "Error: " << strerror(errno) << endl;
}

Node * Graph::insertHelper(int value){
    if (m_head != nullptr) {
        if (value < 0){
                return nullptr;
        }
        else {
                Node * finder = findNode(value);
                    if (finder == nullptr) {
                        Node * finder1 = new Node(value); 
                        return finder1;
                    }// end if

                    return finder;

            }// end else
            
    }// end if
    else {
        Node * head = new Node(value);
        insertAtHead(head);
        return head;
    }
}// end insertHelper

void Graph::insert(int node, int n, int e, int s, int w){
    Node * sorter;
    sorter = insertHelper(node);

    if (sorter != nullptr) {
        Node * temp = m_head;
        while (temp->m_next != nullptr){
            temp = temp->m_next;
        }// end while
        temp->m_next = sorter;
        sorter->setNorth(insertHelper(n));
        sorter->setSouth(insertHelper(s));
        sorter->setEast(insertHelper(e));
        sorter->setWest(insertHelper(w));
    }// end if


}

void Graph::insertAtHead(Node * aNode){
    aNode->m_next = m_head;
    m_head = aNode;
}

Node * Graph::findNode(int nodeValue){
    Node * temp = m_head;
    while(temp != nullptr){
        if(temp->m_value == nodeValue){
            return temp;
        }
        temp = temp->m_next;
    }
    return nullptr;
}

bool Graph::findPath(int start, int end){
    Node * temp = findNode(start);
    clearResult();
    clearVisited();
    return findPath(temp, end);
}

bool Graph::findPath(Node* aNode, int end){
    if(aNode == nullptr){
       // cout << aNode->m_value << endl;
        return false;
    }
    if(aNode->m_value == end){
        m_path.push(aNode->m_value);
        return true;
    }// end if
    if(aNode->m_visited){
        return false;
    }// end if
    aNode->m_visited = true;
    //cout << aNode->m_value << endl;
    if(findPath(aNode->getEast(), end) == true){
        m_path.push(aNode->m_value);
        return true;
    }
    if(findPath(aNode->getNorth(), end) == true){
        m_path.push(aNode->m_value);
        return true;
    }
    if(findPath(aNode->getWest(), end) == true){
        m_path.push(aNode->m_value);
        return true;
    }
    if(findPath(aNode->getSouth(), end) == true){
        m_path.push(aNode->m_value);
        return true;
    }
    return false;
}

void Graph::dump(){
    stack <int> temp;
    while(!m_path.empty()){
      cout <<  m_path.top();
      temp.push(m_path.top());
        m_path.pop();
    }
    while(!temp.empty()){
        m_path.push(temp.top());
        temp.pop();
    }
} // end dump

void Graph::clearResult(){
    while(!m_path.empty()){
        m_path.pop();
    }
}

void Graph::clearVisited(){
    Node * resetter = m_head;
        if(resetter == nullptr) {
            return;
        }
    while(resetter->m_next != nullptr){
        resetter->m_visited = false;
        resetter = resetter->m_next;
    }
    resetter->m_visited = false;
} // end clear visited

void Graph::buildGraph(string file){
    clearGraph();
    m_dataFile = file;
    loadData();
}

void Graph::clearGraph(){
    Node * eraser = m_head;
    Node * racer = m_head;

    if(!(m_head == nullptr)){
    while ( racer->m_next != nullptr) {
        racer = racer->m_next; //goes to the next node so I can delete the first one
        eraser->m_north = nullptr;
        eraser->m_south = nullptr;
        eraser->m_east = nullptr;
        eraser->m_west = nullptr;
        delete eraser;
        eraser = racer;
    }// end while

    delete racer;
    m_head = nullptr;
    m_dataFile = "";
    m_numNodes = 0;
    clearResult();
    }// end if
}

const Graph & Graph::operator=(const Graph & rhs){
    if (this != &rhs) {
        clearGraph();
        Node * t_head = rhs.m_head;
        if(t_head != nullptr) {
            while(t_head->m_next != nullptr) {
                int n,e,s,w;
                if (t_head->m_north != nullptr){
                     t_head->m_north->m_value;
                }
                else {
                    n = -1;
                }
                if (t_head->m_south != nullptr){
                     t_head->m_south->m_value;
                }
                else {
                    s = -1;
                }
                if (t_head->m_east != nullptr){
                     t_head->m_east->m_value;
                }
                else {
                    e = -1;
                }
                if (t_head->m_west != nullptr){
                     t_head->m_west->m_value;
                }
                else {
                    w = -1;
                }
                insert(t_head->m_value,n,s,e,w);
            }// end while
         }// end if
        m_numNodes = rhs.m_numNodes;
        m_dataFile = rhs.m_dataFile;
        m_path = rhs.m_path;
        return * this;
    }//end if
    return * this;
}
    
bool Graph::empty() const		// is the list empty?
    { return m_head == nullptr; }