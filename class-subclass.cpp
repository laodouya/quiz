#include<iostream>
using namespace std;

class A{
    public:
        A(){
            cout << "a" << endl;
        }
        ~A(){
            cout << "~a" << endl;
        }
};
class B{
    public:
        B(){
            cout << "b" << endl;
        }
        ~B(){
            cout << "~b" << endl;
        }
};
class C{
    public:
        B b;
        A a;
        C():a(){
            b = B();
            cout << "c" << endl;
        }
        ~C(){
            cout << "~c" << endl;
        }
};
class D:public C{
    public:
        D(){
            cout << "d" << endl;
        }
        ~D(){
            cout << "~d" << endl;
        }
};
int main()
{
    const int num=2;
    C *p = new D;
    delete p;
}
