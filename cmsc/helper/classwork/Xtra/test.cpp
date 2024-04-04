#include <iostream>
using namespace std;
int main() {
  int * p = new int;
  *p = 1;
  cout << *p << endl;
  delete p;
  return 0;
}
