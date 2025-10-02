#include <iostream>
using namespace std;

class myclass
{
    int x;
public:
    myclass(int x):x(x){};
    friend void show(myclass c);
};
void show(myclass c)
{
    cout << c.x << endl;
}
int main()
{
    myclass cl(2);
    show(cl);
}
