#include <iostream>
using namespace std;

class foo {
   public:
    string str;
    foo(string inStr) {
        str = inStr;
    }
    void print() {
        cout << str << endl;
    }
};

int main() {
    foo Foo("That's a string");
    Foo.print();
    return 0;
}
