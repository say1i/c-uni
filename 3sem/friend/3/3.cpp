#include <iostream>
using namespace std;

class truck;
class car
{
    int passenger, speed;
public:
    car(int p, int s):passenger(p), speed(s){}
    int sp_greater(truck t);
};

class truck
{
    int weight, speed;
public:
    truck(int w, int s):weight(w), speed(s) {}
    friend int car::sp_greater(truck t);
};
int car::sp_greater(truck t) {return speed-t.speed;}
int main ()
{
    int t;
    car c1(4,90), c2(5,70);
    truck t1(2000,20), t2(7000,80);
    t=c1.sp_greater(t1);
    cout << t << endl;
}
