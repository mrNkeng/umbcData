#include "heapHW4.h"

Heap::~Heap(){delete [] _heap;}

bool Heap::enqueue(int key, int data){
    if (_heapSize > _numElements){
        Node aNode(key, data);
        _numElements++;
        _heap[_numElements] = aNode;
        upHeap(_numElements);
        return true;
    }
    else
        return false;
}
void Heap::upHeap(int anIndex){
    int p = anIndex / 2;
    if (anIndex > _ROOT_INDEX) { 
        if (_heap[anIndex].getKey() >= _heap[p].getKey()) {
            return;
        }
        else {
          Node swapper(_heap[p].getKey(), _heap[p].getData());
        _heap[p] = _heap[anIndex];
        _heap[anIndex] = swapper;
        upHeap(p);  
        }
    }
   return;
}


Node Heap::dequeue(){
    Node temp;
    if (!empty()){
        temp = _heap[_ROOT_INDEX];
        _heap[_ROOT_INDEX] = _heap[_numElements];
        _numElements--;
        downHeap(_ROOT_INDEX);
    }
    return temp;
}
void Heap::downHeap(int anIndex){
        int lower = anIndex;
        int r = anIndex * 2 + 1;
        int l = anIndex * 2;
 
        // comparing the left and right child and getting the largest value

        if (l < size() && _heap[l].getKey() < _heap[anIndex].getKey()) {
            lower = l;
        }
        else if (r < size() && _heap[r].getKey() < _heap[lower].getKey()) {
            lower = r;
        }
        // This code does the swap with a child having lower value and
        else if (lower != anIndex) {
            Node swapper(_heap[lower].getKey(), _heap[lower].getData());
            _heap[lower] = _heap[anIndex];
            _heap[anIndex] = swapper;
            downHeap(lower);
        }
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

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getKey() << ":" << node.getData() << endl;
  return sout;
}