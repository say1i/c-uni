#include <iostream>

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

    kover(stol& stolik)
    {
        stoleshnica = stolik;
        cout << "kover added" << endl;
    }
};

int main()
{
    stol stul;
    kover kovrik(stul);
}
