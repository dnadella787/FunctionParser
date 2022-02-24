#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <sstream>
#include <cassert>



//error when fparser::fparser<int> fp("x^2 + 3*x + 3", "x");
namespace fparser 
{

template <typename T>
class fparser
{
protected:
    static_assert(std::is_arithmetic<T>::value, "fparser template parameter must be numeric (int, float, long, etc).");

    std::string func;
    std::string postfix;
    std::string var; 


    std::map<char, T (*) (T x, T y)> operators;


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


    T convert_to(const std::string& str)
    {
        std::istringstream ss(str);
        T num;
        ss >> num;
        return num;
    }


public:
    fparser(const std::string& f, const std::string& input_var) : func(f), var(input_var)
    {
        //first initialize all the operators and their lambdas 
        operators['+'] = [](T x, T y){return x + y;};
        operators['-'] = [](T x, T y){return x - y;};
        operators['*'] = [](T x, T y){return x * y;};
        operators['/'] = [](T x, T y){return x / y;};
        operators['^'] = [](T x, T y){return pow(x,y);};

        //produce the function in infix notation to perform calculations
        std::stack<char> f_stack;
        for (std::string::const_iterator it = f.begin(); it != f.end(); ++it)
        {
            if (*it == ' ')
                continue; 

            else if (isalnum(*it))
                postfix += *it;

            else if (*it == '(' || *it == '^')
                f_stack.push(*it);

            else if (*it == ')')
            {
                while (!f_stack.empty() && f_stack.top() != '(')
                {
                    postfix += f_stack.top();
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
                    while (!f_stack.empty() && preced(*it) <= preced(f_stack.top()))
                    {
                        postfix += f_stack.top();
                        f_stack.pop();
                    }
                    f_stack.push(*it);
                }
            }
        }

        while (!f_stack.empty())
        {
            postfix += f_stack.top();
            f_stack.pop();
        }
    }


    // this currently works but need to make it so you can have 
    // multiple digits for coefficients (like 32*x)
    // also needs to be refactored to use iterators instead of 
    // just an int
    T calculate(const T x_val)
    {
        T y_val;
        std::stack<T> s;

        for (int i = 0; i < postfix.size(); ++i)
        {
            auto iter = operators.find(postfix[i]);

            //if the current char in the postfix string is an operator
            if (iter != operators.end())
            {
                assert(s.size() >= 2);
                auto func = iter->second;
                T second = s.top();
                s.pop();
                T first = s.top();
                s.pop();
                T result = func(first, second);
                s.push(result);
            }
            else
            {
                // if its not an operator, check if its a variable
                if (postfix.substr(i,1) == var)
                    s.push(x_val);
                // otherwise it is a constant just add to stack
                else
                    s.push(convert_to(postfix.substr(i,1)));
            }
        }

        return s.top();
    }
};

}
