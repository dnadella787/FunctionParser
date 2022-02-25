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

    std::string ifix_func;
    std::string pfix_func;
    std::string eval_var; 


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
    fparser(const std::string& f, const std::string& input_var) : ifix_func(f), eval_var(input_var)
    {
        //first initialize all the operators and their lambdas 
        operators['+'] = [](T x, T y){return x + y;};
        operators['-'] = [](T x, T y){return x - y;};
        operators['*'] = [](T x, T y){return x * y;};
        operators['/'] = [](T x, T y){return x / y;};
        operators['^'] = [](T x, T y){return pow(x,y);};

        //produce the function in infix notation to perform calculations
        std::stack<char> f_stack;
        for (size_t i = 0; i < f.size(); ++i)
        {
            if (f[i] == ' ')
                continue; 

            else if (isalnum(f[i]))
                pfix_func += f[i];

            else if (f[i] == '(' || f[i] == '^')
                f_stack.push(f[i]);

            else if (f[i] == ')')
            {
                while (!f_stack.empty() && f_stack.top() != '(')
                {
                    pfix_func += f_stack.top();
                    f_stack.pop();
                }
                f_stack.pop();
            }

            else
            {
                if (preced(f[i]) > preced(f_stack.top()))
                    f_stack.push(f[i]);
            
                else
                {
                    while (!f_stack.empty() && preced(f[i]) <= preced(f_stack.top()))
                    {
                        pfix_func += f_stack.top();
                        f_stack.pop();
                    }
                    f_stack.push(f[i]);
                }
            }
        }

        while (!f_stack.empty())
        {
            pfix_func += f_stack.top();
            f_stack.pop();
        }
    }


    //gives a y value given a specifici x value, only a single 
    //value, to do multuple input a vector, overloaded func is 
    //below 
    T calculate(const T& x_val)
    {
        T y_val;
        std::stack<T> s;

        for (int i = 0; i < pfix_func.size(); ++i)
        {
            auto iter = operators.find(pfix_func[i]);

            //if the current char in the pfix_func string is an operator
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
                if (pfix_func.substr(i,1) == eval_var)
                    s.push(x_val);
                // otherwise it is a constant just add to stack
                else
                {
                    std::string curr_dig = "";
                    while (std::isdigit(pfix_func[i]))
                    {
                        curr_dig += pfix_func[i];
                        ++i;
                    }
                    --i;

                    s.push(convert_to(curr_dig));
                }
            }
        }

        return s.top();
    }


    //overloaded version of calculate that takes in multiple x vals
    //returns vector of all outputted y values in order 
    std::vector<T> calculate(const std::vector<T>& x_vals)
    {
        std::vector<T> y_vals(x_vals.size());
        for (size_t i = 0; i < x_vals.size(); ++i)
        {
            y_vals[i] = calculate(x_vals[i]);
        }

        return y_vals;
    }
};

}
