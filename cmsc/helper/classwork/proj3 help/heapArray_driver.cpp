
#include "heap.h"
using namespace std;

int main(){
    int array[]={9,5,6,2,7};
    Heap aHeap(1001);//remember the root is at index 1, not 0
    //for (int i=0;i<5;i++)
    //    aHeap.enqueue(array[i],array[i]*10);
    for (int i=10;i>0;i--)//insert 10 nodes
        aHeap.enqueue(i,i*10);
    aHeap.dumpArray();
    cout << "In order dump: ";aHeap.inOrderDump();cout << endl;
    //cout << "Dequeue returns: " << aHeap.dequeue();
    //cout << "In order dump: ";aHeap.inOrderDump();cout << endl;
    //cout << "The root is: " << aHeap.min();
    //for (int i=1000;i>0;i--)
    //    aHeap.dequeue();
    //aHeap.enqueue(1,10);
    //out << "In order dump: ";aHeap.inOrderDump();cout << endl;
    //cout << "The root is: " << aHeap.min();
    cout << endl;
    //aHeap.dequeue();
    //aHeap.dumpArray();
    //cout << "In order dump: ";aHeap.inOrderDump();cout << endl;
    aHeap.heapSort();
    aHeap.dumpArray();
    //cout << "In order dump: ";aHeap.inOrderDump();cout << endl;
    cout << endl;
    aHeap.reHeapify();
    aHeap.dumpArray();
    cout << "In order dump: ";aHeap.inOrderDump();cout << endl;
    return 0;
}