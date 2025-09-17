#include <iostream>

namespace multiply
{
    double operation(double x,double y)
    {
        return x*y;
    }
}
namespace divide
{
    double operation(double x,double y)
    {
        return x/y;
    }
}

int main()
{
    std::cout<<multiply::operation(10,2)<<std::endl;
    std::cout<<divide::operation(10,2)<<std::endl;
}
