#include <iostream>
#include <string>
#include <stack>
#include <ctype.h>

namespace fparser 
{

template <typename T>
class fparser
{
protected:
    static_assert(std::is_arithmetic<T>::value, "fparser template parameter must be numeric (int, float, long, etc).");

    std::string func;
    std::string postfix;
    std::stack<char> pfix_stack;
    std::string var; 


    int preced(const char& ch) 
    {
        if (ch == '+' || ch == '-') 
            return 1;            //Precedence of + or - is 1
        else if(ch == '*' || ch == '/') 
            return 2;            //Precedence of * or / is 2
        else if(ch == '^') 
            return 3;            //Precedence of ^ is 3
        else 
            return 0;
    }
    
public:
    fparser(const std::string& f, const std::string& input_var) : func(f), var(input_var)
    {
        std::stack<char> f_stack;
        f_stack.push('#');

        //initialize the stack in infix notation to be evaluated later 
        for (std::string::const_iterator it = f.begin(); it != f.end(); ++it)
        {
            if (isalnum(*it))
                pfix_stack.push(*it);

            else if (*it == '(' || *it == '^')
                f_stack.push(*it);

            else if (*it == ')')
            {
                while (f_stack.top() != '#' && f_stack.top() != '(')
                {
                    pfix_stack.push(f_stack.top());
                    f_stack.pop();
                }
                f_stack.pop();
            }

            else
            {
                if (preced(*it) > preced(f_stack.top()))
                    f_stack.push(*it);
            
                else
                {
                    while (f_stack.top() != '#' && preced(*it) <= preced(f_stack.top()))
                    {
                        pfix_stack.push(f_stack.top());
                        f_stack.pop();
                    }
                    f_stack.push(*it);
                }
            }
        }

        while (f_stack.top() != '#')
        {
            pfix_stack.push(f_stack.top());
            f_stack.pop();
        }
    }

    T calculate(const T& x_val)
    {
        T y_val;

        


        return y_val;
    }



    void print()
    {
        while (!pfix_stack.empty())
        {
            std::cout << pfix_stack.top() << std::endl;
            pfix_stack.pop();
        }
    }

};

}
