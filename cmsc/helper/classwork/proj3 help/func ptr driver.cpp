#include <iostream>
using namespace std;
typedef int (*funcType)(int x);
int multiply(int x){return (x*2);}
int divide(int x){return (x/2);}
class A{
    public:
    A(funcType function){
        m_function = function;
    }
    int calc(int x){return m_function(x);}
    void setFunction(funcType function){
        m_function = function;
    }
    private:
    funcType m_function;
};
int main(){
    A o(multiply);
    cout << "Calling multiply: " << o.calc(20) << endl;
    o.setFunction(divide);
    cout << "Calling divide: " << o.calc(20) << endl;
    return 0;
}