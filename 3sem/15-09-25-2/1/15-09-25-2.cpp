#include <iostream>
#include <fstream>
using namespace std;

bool isValidFIO(const string fio) {
    for (int i = 0; i < fio.length();i++)
    {
        if (!isalpha(fio[i])) {
            return false;
        }
    }
    return true;
}
bool isValidInt(const string num) {
    int state = 0;
    for (int i = 0; i < num.length();i++)
    {
        if (!isdigit(num[i]))
        {
            return false;
        }
    }
    return true;
}
bool isValidDouble(const string num) {
    int state = 0;
    for (int i = 0; i < num.length();i++)
    {
        if (isdigit(num[i]))
        {
            continue;
        }
        else if(num[i]=='.')
        {
            if(state==1)return false;//точка два раза
            if(i==0||i==num.length()-1)return false;//точка вначале или в конце
            state=1;
        }
        else return false;
    }
    return true;
}

int main(int argc,char** argv)
{
    if(argc!=3)
    {
        cout << "not enough input" <<endl;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    string name;
    string surname;
    string fathername;

    string date;
    string ball;

    fin >> name >> surname >> fathername >> date >> ball;
    if (name.empty() || surname.empty() || fathername.empty() || date.empty() || ball.empty()) {
        cout << "wrong format" << endl;
        return -1;
    }
    string fio = surname+name+fathername;

    if (!isValidFIO(fio) || !isValidInt(date) || !isValidDouble(ball)) {
        cout << "wrong format" << endl;
        return -1;
    }

    fout << name << " " << surname << " " << fathername << " " << date << " " << ball << endl;

    fin >> ws;
    string test;
    if(fin>>test)
    {
        cout<<"wrong format"<<endl;
        return -1;
    }
    else if(fin.eof())
    {
        cout<<"good"<<endl;
    }
    else
    {
        cout<<"bad"<<endl;
        return -1;
    }
    return 0;
}
