#include <iostream>

using namespace std;

class example
{
    int value = 0;
public:
    void setValue(int value1)
    {
        value = value1;
    }
    int getValue()
    {
        return value;
    }
    void func(int a)
    {
        cout << a << endl;
    }
    void func(string a)
    {
        cout << a << endl;
    }
    void func(int a,int b,int c = 0)
    {
        cout << a <<" "<< b <<" "<< c <<endl;
    }
};
int main()
{
    example ex;
    ex.setValue(20);
    cout << ex.getValue() << endl;
    ex.func(10);
    ex.func("stakan");
    ex.func(10,20);
    ex.func(10,20,30);
    return 0;
}
