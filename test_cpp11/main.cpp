#include <iostream>

using namespace std;

//c++ using == typedef;
struct DemoClass {
    int a_mem;
};

using DC = DemoClass;

int main() {
    DC a_demo_var;
    a_demo_var.a_mem = 10;

    cout << a_demo_var.a_mem << endl;
    return 0;
}