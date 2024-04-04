
#include "bst.h"
using namespace std;

int main(){
    
    string inputSrt[] = {"D","B","F","A","C","E","G"};
    BST aTree;
    for (int i=0;i<7;i++)
        aTree.insert(inputSrt[i]);
    aTree.dump();
    cout << endl;
    aTree.remove("D");
    aTree.dump();
    cout << endl;
    //aTree.findMin();
    
    return 0;
}