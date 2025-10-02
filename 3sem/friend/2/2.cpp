#include <iostream>
using namespace std;
class myclass2;
class myclass1
{
    int x;
public:
    myclass1(int x):x(x){};
    friend void show(myclass1 c1,myclass2 c2);
};
class myclass2
{
    int x;
public:
    myclass2(int x):x(x){};
    friend void show(myclass1 c1,myclass2 c2);
};
void show(myclass1 c1,myclass2 c2)
{
    cout << c1.x <<" "<< c2.x << endl;
}
int main()
{
    myclass1 c1(2);
    myclass2 c2(3);
    show(c1,c2);
}
