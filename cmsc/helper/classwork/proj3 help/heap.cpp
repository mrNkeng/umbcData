
#include "heap.h"
Heap::~Heap(){

}
bool Heap::enqueue(int key, int data){
    
}
void Heap::upHeap(int anIndex){
    
}
Node Heap::dequeue(){
    
}
void Heap::downHeap(int anIndex){
    
}
Node Heap::min(){
    
}
int Heap::size(){
    return _numElements;
}
bool Heap::empty(){
    return (_numElements == 0);
}
void Heap::inOrderTraversal(int anIndex){
    
}
void Heap::dumpArray(){
    for(int i=_ROOT_INDEX; i<=_numElements; i++)
     {
          cout << "Element index" << i << ". key=" << _heap[i]._key << 
                    "  data=" << _heap[i]._data << endl;
     }
}
void Heap::inOrderDump(){
    inOrderTraversal(_ROOT_INDEX);
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getKey() << ":" << node.getData() << endl;
  return sout;
}