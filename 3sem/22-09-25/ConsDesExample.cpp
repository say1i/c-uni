#include <iostream>
#include <stdlib.h>
using namespace std;
class stol
{
public:
    stol()
    {
        cout << "stol added" << endl;
    }
};
class kover
{
public:
    stol stoleshnica;
    int* a;
    kover(stol stolik,int n):stoleshnica(stolik)
    {
        a = (int*)malloc(n*sizeof(int));
        if(!a)
        {
            cout<<"error"<<endl;
        }
        cout << "kover added" << endl;
    }
};

int main()
{
    stol stul;
    for(int i = 0; i < 1000000;i++)
    {
        kover kovrik(stul,20000);
    }

}
