#include <iostream>

using namespace std;

//c++ using == typedef;
struct DemoClass {
    int a_mem;
};

using DC = DemoClass;

int Size()
{
    return 4;
}

int main() {
    DC a_demo_var;
    a_demo_var.a_mem = 10;

    cout << a_demo_var.a_mem << endl;

    decltype(a_demo_var) xt;
    xt.a_mem = 2;

    cout << xt.a_mem << endl;

    decltype(Size()) type_from_size = 4;
    cout << type_from_size << endl;

    return 0;
}