#include <iostream>
using namespace std;
int main () {
    int array1[10];
    array1[3]=300;
     cout << array1[3] << endl;
     int * array2 = new int [10];
     array2[5] = 500;
     cout << array2[5] << endl;
     delete [] array2;
     int ** array3 = new int*[10];
     int* aPointer = new int;
     *aPointer = 600;
     array3[6] = aPointer;
     cout << array3[6] << endl;
     cout << *array3[6] << endl;
     delete aPointer;
     delete [] array3;
     return 0;

}