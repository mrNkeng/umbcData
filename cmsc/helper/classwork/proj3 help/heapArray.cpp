
#include "heap.h"
Heap::~Heap(){delete [] _heap;}
bool Heap::enqueue(int key, int data){
    
}
void Heap::upHeap(int anIndex){
    
}
Node Heap::dequeue(){
    
}
void Heap::downHeap(int anIndex){
    
}

void Heap::downHeap1(int anIndex){
	
}

Node Heap::min(){
    return _heap[_ROOT_INDEX];
}
int Heap::size(){
    return _numElements;
}
bool Heap::empty(){
    return (_numElements == 0);
}
void Heap::inOrderTraversal(int anIndex){
    if (anIndex <= _numElements){
        cout << "(";
        inOrderTraversal(anIndex*2);//visit left
        cout << _heap[anIndex]._key << ":" << _heap[anIndex]._data; //visit node
        inOrderTraversal(anIndex*2+1);//visit right
        cout << ")";
    }
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

void Heap::heapSort(){
    
}
void Heap::downHeap2(int anIndex, int end){
    
}

void Heap::reHeapify(){
    // Build heap (rearrange array) using downheap
    // we can use this function if the array was rearranged
    // for some reason, for example we sorted the array 
    // using heapSort()
	for (int i = _numElements / 2 ; i >= _ROOT_INDEX; i--)
		downHeap(i);
}
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getKey() << ":" << node.getData() << endl;
  return sout;
}