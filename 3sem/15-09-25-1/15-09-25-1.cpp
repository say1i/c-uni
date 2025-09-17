#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("text1.txt");
    ofstream fout("text2.txt");
    char ch;
    int spaceCount=0;
    int slashNCount = 0;
    if(fin.is_open()&&fout.is_open())
    {
        while(fin.get(ch))
        {
            if(ch==' ')spaceCount++;
            if(ch=='\n')slashNCount++;
            fout << ch;
        }
        if(spaceCount!= 2||slashNCount!=2)
        {
            cout << "wrong format" <<endl;
            return -1;
        }
    }
    else cout << "file did not open" <<endl;
    return 0;
}
