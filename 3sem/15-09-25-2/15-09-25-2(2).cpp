#include <iostream>
#include <fstream>

using namespace std;
int main(int argc,char** argv)
{
     cout <<argc<<endl;
    if(argc!=3)
    {
        cout << "not enough input" << endl;
    }
    cout <<argc<<endl;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    string name;
    string surname;
    string fathername;

    int date;
    double ball;
    fin >> name >> surname >> fathername >> date >> ball;
    fout << name << " " << surname << " " << fathername << " " << date << " " << ball << endl;

    fin >> ws;
    string test;
    if(fin.eof())
        cout<<"good"<<endl;
    else if(fin>>test)
    {
        cout<<"wrong format"<<endl;
        return -1;
    }
    else
    {
        cout<<"bad"<<endl;
        return -1;
    }
    return 0;
}
