#include <iostream>
using namespace std;
class stak
{
    public:
    int* mas;
    int n;
    int p = -1;
    stak(int s)
    {
        mas = new(nothrow) int[s];
        if(!mas)
        {
            cout << "mas error" << endl;
            n=0;
        }
        else n=s;
    }
    stak(const stak& other)
    {
        n=other.n;
        p=other.p;
        mas = new int[n];
        for(int i = 0; i < n;i++)
        {
            mas[i]=other.mas[i];
        }
    }
    ~stak()
    {
        delete[] mas;
    }
    stak& operator=(const stak& other)
    {
        if(&other==this)return *this;
        delete[] mas;
        n=other.n;
        p=other.p;
        mas = new int[n];
        for(int i = 0; i < n;i++)
        {
            mas[i]=other.mas[i];
        }
        return *this;
    }
    stak operator+(const stak& other)
    {
        int s = p+other.p;
        int* mac = new int[s];
        int i = 0;
        for(; i <= p;i++)
        {
            mac[i]=mas[i];
        }
        int l = 0;
        for(int j = i;j<s;j++,l++)
        {
            mac[j]=other.mas[l];
        }
        delete[] mas;
        mas=mac;
    }
    bool full()
    {
        return p==n-1;
    }
    bool null()
    {
        return p==-1;
    }
    void push(int x)
    {
        if(!full())
        {
            p++;
            mas[p]=x;
        }
        else cout << "no space" << endl;
    }
    void pull()
    {
        if(!null())
        {
            p--;
        }
        else cout << "already empty" << endl;
    }
    void last()
    {
        if(!null())
        {
            cout << mas[p] << endl;
        }
        else cout << "already empty" << endl;
    }
    void show()
    {
        for(int i = 0; i <=p;i++)
        {
            cout << mas[i]<< endl;
        }
    }
};
int main()
{
    stak s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.show();
}
