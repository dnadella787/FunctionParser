#include <iostream>
#include <string>
#include <stack>
#include <ctype.h>

template <typename T>
class fparser
{
protected:
    std::string func;
    std::stack<std::string> f_stack({"#"}); 
    char var; 
    
public:
    fparser(const std::string& f, const char& variable) : func(f), var(variable)
    {
        std::string postfix = "";
        for (std::string::iterator it = f.begin(), it != f.end(), it++)
        {
            if (isalnum(*it))
                postfix += *it;
            else if (*it == "(" || *it = "^")
                f_stack.push(*it);
            else if (*it == ")")
            {
                while (f_stack.top() != "#" && stack.top() != "(")
                {
                    postfix += f_stack.top();
                    f_stack.pop();
                }
            }
            else
            {
                
            }

        }

    }

};
