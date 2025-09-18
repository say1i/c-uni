#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    ifstream fin("text1.txt");
    ofstream fout("text2.txt");

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
