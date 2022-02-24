#include <iostream>
#include <string>
#include "fparser.h"





int main()
{
    fparser::fparser<std::string> fp("x^y/(5*z)+2", "x");
    fp.print();
}