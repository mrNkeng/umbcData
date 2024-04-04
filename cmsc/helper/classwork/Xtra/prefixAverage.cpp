#include <iostream>
using namespace std;
void prefixAverage1 (int x[], int A[], int n) {
    int counter = 0;
    for (int i=0; i<n; i++) {
        int s = X[0];
        for (int j=1;j<=i; j++) {
            s = s + X[j];
            counter++;
        }
        A[i] = s / (i+1);
    }
}
void prefixAverage2(int X[], int A[], int n){
    int counter = 0;
    int s = 0;
    for (int i=0; i<n; i++){
        s = s + X[i];
        A[i] = s / (i+1);
        counter++;
    }
    cout << "prefix Average1: " << counter << endl;
}
int main() {
    const int n = 10;
    int A[n] = {0};
    int X[n];
    for (int i=0; i<n; i++){
        X[i] = 1;
    }
    prefixAverage1(X,A,n);
    prefixAverage2(X,A,n);
    return 0;
}