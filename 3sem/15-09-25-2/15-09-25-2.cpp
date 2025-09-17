#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char** argv)
{
    if(argc!=3)
    {
        cout << "not enough input" <<endl;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    cout << argv[1] <<" "<<argv[2]<<endl;

    char ch;
    int spaceCount=0;
    int slashNCount = 0;
    if(fin.is_open()&&fout.is_open())
    {
        while(fin.get(ch))
        {
            if(ch==' ')spaceCount++;
            if(ch=='\r')slashNCount++;
            fout << ch;
        }
        if(spaceCount!= 2||slashNCount!=2)
        {
            cout << spaceCount <<endl;
            cout << slashNCount <<endl;
            cout << "wrong format" <<endl;
            return -1;
        }
    }
    else cout << "file did not open" <<endl;
    return 0;
}
