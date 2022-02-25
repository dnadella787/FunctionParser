#include <iostream>
#include <string>
#include <vector>
#include "fparser.h"



int main()
{
    fparser::fparser<double> fp("x^x - 23*x + 3", "x");
    std::cout << fp.calculate(1.25) << std::endl;
    auto out = fp.calculate({1,2,3,4});
    for (auto y : out)
        std::cout << y << std::endl;
}