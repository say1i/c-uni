#include <iostream>
#include<cstdlib>
using namespace std;
class Array
{
    int n;
    int* p;
public:
    Array(int num)
    {
        p = new int[num];
        if(!p)
        {
            cout << "error1\n";
            exit(1);
        }
        n = num;
        for(int i = 0; i < n;i++)p[i]=i;
    }
    ~Array(){delete [] p;}
    void show ()
    {
        for( int i=0; i<n;i++) cout<<i<<": "<<p[i]<<endl;
    }
    Array(const Array &other)
    {
        n=other.n;
        p=new int[n];
        for(int i=0;i<n;i++)p[i]=other.p[i];
    }
};

int main()
{
    Array a(10);
    a.show();
    Array b(a);
    b.show();
    return 0;
}
