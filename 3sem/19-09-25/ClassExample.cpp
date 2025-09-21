#include <iostream>

using namespace std;

class example
{
    int value1 = 0;
    int value2 = 0;
public:
    void setValue1(int valueA)
    {
        value1 = valueA;
    }
    int getValue1()
    {
        return value1;
    }
    void setValue2(int valueA)
    {
        value2 = valueA;
    }
    int getValue2()
    {
        return value2;
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
    ex.setValue1(10);
    ex.setValue2(20);
    cout << ex.getValue1() << endl;
    cout << ex.getValue2() << endl;
    ex.func(10);
    ex.func("stakan");
    ex.func(10,20);
    ex.func(10,20,30);
    return 0;
}
