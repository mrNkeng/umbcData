// CMSC 341 - Fall 2021 - Project 3 - MQueue Class 

#include "mqueue.h"
using namespace std;
using std::domain_error;

MQueue::MQueue(prifn_t priFn) {
  m_heap = nullptr;
  m_size = 0; 
  m_priorFunc = priFn;
}

MQueue::~MQueue(){
  clear();
}

MQueue::MQueue(const MQueue& rhs) {
//shallow copy member pointers share memory *they point to the ame thing*
//deep copy allocate new memory so the new object doesn't get modified
// rhs represent the old object
m_priorFunc = rhs.m_priorFunc;
m_heap = nullptr;
m_size = rhs.m_size; 

MqHelp(rhs.m_heap, m_heap);
}

void MQueue::MqHelp(const Node* rhs, Node*& lhs){
  if (rhs == nullptr) {
  return;
  }
  lhs = new Node(rhs->m_order);
  MqHelp(rhs->m_left, lhs->m_left);
  MqHelp(rhs->m_right, lhs->m_right);
}

MQueue& MQueue::operator=(const MQueue& rhs){
    if (&rhs != this) { // we get the memory address of rhs to see if its 
       clear();         //the same as the current object which would mean self assigment.
       m_priorFunc = rhs.m_priorFunc;
       m_heap = nullptr;
       m_size = rhs.m_size; 

      MqHelp(rhs.m_heap, m_heap);

    }
    return *this; // The "*this" dereferences the "this" keyword. this function return an MQueue object
}


void MQueue::insertOrder(const Order& input) {
Node* temp = new Node(input);
m_heap = mergeHelper(m_heap, temp);
m_size++;
}
   

Order MQueue::getNextOrder() {
  /*Extract (remove the node) and return the highest priority order from the queue. 
  Must maintain the min-heap property. Should throw a domain_error exception if 
  the queue is empty when the function is called.
  */
  if (m_size == 0){
      throw std::domain_error("the queue is empty");
  }
  Order oTemp = m_heap->getOrder();
  Node* temp = mergeHelper(m_heap->m_left, m_heap->m_right);
  delete m_heap;
  m_heap = temp;
  m_size--;
  return oTemp;
}

Node* MQueue::mergeHelper(Node* nodeA, Node* nodeB){ // responsible for merging the nodes
    if (nodeA == nullptr) {
      return nodeB;
    }
    else if (nodeB == nullptr){
      return nodeA;
    }
    if (m_priorFunc(nodeA->m_order) > m_priorFunc(nodeB->m_order)){
      Node* temp = nodeA;
      nodeA = nodeB; 
      nodeB = temp;// the 3 lines are responsible for swapping the nodes
    }
    Node* temp = nodeA->m_left;
    nodeA->m_left = nodeA->m_right; 
    nodeA->m_right = temp; // if the if statement above isn't met we want to do these
    nodeA->m_left = mergeHelper(nodeA->m_left, nodeB);
    return nodeA;
}


void MQueue::mergeWithQueue(MQueue& rhs) {
  // m_priorFunc tells us the priority in the heap
  // we want to check that the priority functions are the same
  if(m_priorFunc != rhs.m_priorFunc){
    throw std::domain_error("The roots have different priorities");
  }
  else if (rhs.m_heap == nullptr){
      return;
  }
  else if (m_heap == nullptr){
    m_heap = rhs.m_heap;
    rhs.m_heap = nullptr;
    return;
  }
  else if (rhs.m_heap == m_heap){ // protection against self assignment
    return;
  }
  m_heap = mergeHelper(m_heap, rhs.m_heap);

  m_size = m_size + rhs.m_size;
  rhs.m_size = 0;
  rhs.m_heap = nullptr; // the purpose of these lines of code is to clear out rhs
  
}// end function

void MQueue::clear() {
  //delete m_heap;
  //m_heap = nullptr
  clearHelp(m_heap);
  m_heap = nullptr;
}

void MQueue::clearHelp(Node* cleaner) {
if (cleaner != nullptr) {
        clearHelp(cleaner->m_left);
        clearHelp(cleaner->m_right);
        delete cleaner;
        cleaner = nullptr;
    }// end if
}// end clearHelp

int MQueue::numOrders() const {
  return m_size;
}

void MQueue::printHelper(Node* printer) const{
    if ( printer != nullptr ) {
    cout << m_priorFunc(printer->m_order) << " " << *printer << endl;
    printHelper(printer->m_left);
    printHelper(printer->m_right);
  }
}

void MQueue::printOrderQueue() const {
  printHelper(m_heap);
}

prifn_t MQueue::getPriorityFn() const {
  return m_priorFunc;
}

void MQueue::setPriorityFn(prifn_t priFn) {
     //rebuilds the heap and needs a place to store the new data
    // remove all data from current queue into new queue
    MQueue newQueue(priFn);
      while (m_heap != nullptr){
          newQueue.insertOrder(getNextOrder()); // inserting into the new heap
      }
    m_heap = newQueue.m_heap;
    m_size = newQueue.m_size;
    newQueue.m_heap = nullptr;
    m_priorFunc = priFn;
    newQueue.m_size = 0;
}

// overloaded insertion operator for Order class
ostream& operator<<(ostream& sout, const Order& order) {
  sout << "Order: " << order.getCustomer() << ", PM priority: " << order.getPMPriority()
       << ", quantity: " << order.getQuantityValue() 
       << ", material availability: " << order.getAvailabilityProbablity() << "%"
       << ", arrival time: " << order.getArrivalTime();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getOrder();
  return sout;
}

// for debugging
void MQueue::dump() const
{
  if (m_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(m_heap);
    cout << endl;
  }
}

// for debugging
void MQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getCustomer();
    dump(pos->m_right);
    cout << ")";
  }
}

