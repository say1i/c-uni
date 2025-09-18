#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("text1.txt");
    ofstream fout("text2.txt");
    char ch;
    int elCount=0;
    if(fin.is_open()&&fout.is_open())
    {
        while(fin.get(ch))
        {
            if(ch==' ')
            {
                fout << ch;
                while(ch==' ')
                {
                    fin.get(ch);
                    if(fin.eof())
                    {
                        return 0;
                    }
                }
                elCount++;
            }

            if(ch=='\n')
            {
                fout << ch;
                while(ch=='\n')
                {
                    fin.get(ch);
                    if(fin.eof())
                    {
                        return 0;
                    }
                }
                elCount++;
            }

            fout << ch;
        }
        if(elCount!=4)
        {
            cout << "wrong format" <<endl;
            return -1;
        }
    }
    else cout << "file did not open" <<endl;
    return 0;
}
