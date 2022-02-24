#include <iostream>
#include <string>
#include "fparser.h"





int main()
{
    fparser::fparser<double> fp("x^2 + 3*x", 'x');
    fp.print();
}