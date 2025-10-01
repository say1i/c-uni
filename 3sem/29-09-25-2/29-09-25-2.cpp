#include<iostream>
#include<cstdlib>

using namespace std;

class Array
{
    int n;
    char* p;
public:
    Array(int num)
    {
        p = new char[num];
        if(!p)
        {
            cout << "error1\n";
            exit (1);
        }
        n = num;
    }
    ~Array(){delete [] p;}
    char &put(int i);//амперсант нужен чтоб пут возвращал ссылку на p[i] и дальше мы по адрессу этой ссылки записывали х и r
    {
        if (i<0 || i>=n)
        {
            cout << "error2\n";
            exit(1);
        }
        return p[i];
    }
    char get(int i)
    {
        if (i<0 || i>=n)
        {
            cout << "error3\n";
            exit(1);
        }
        return p[i];
    }
}

int main()
{
    Array a(10);
    a.put(3) = 'X';
    a.put(2) = 'R';
    cout << a.get(3) << a.get(2);
    cout << "\n";
    a.put(11) = '!';
    return 0;
}
