#include <iostream>
#include <string>
#include <map>
#include "fparser.h"


// class tester
// {
//     std::map<char, double (*)(double x, double y)> operators;

// public:
//     tester(std::string s)
//     {
//         operators['+'] = [](double x, double y){return x + y;};
//         for (int i = 0; i < s.size(); i++)
//         {
//             std::map<char, double (*)(double x, double y)>::iterator iter = operators.find(s[i]);
//             if (iter == operators.end())
//             {
//                 continue;
//             }
//             else 
//             {
//                 auto func = iter->second;
//                 int x = std::stoi(s.substr(i-1, 1));
//                 int y = std::stoi(s.substr(i-2, 1));

//                 std::cout << func(x, y) << std::endl;
//             }
//         }
//     }
// };


int main()
{
    // tester("a12+");
    fparser::fparser<double> fp("x^2 + 2*x + 3", "x");
    fp.calculate(1.25);
}