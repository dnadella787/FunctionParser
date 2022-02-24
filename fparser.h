#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <sstream>


template <typename S> S convert_to (const std::string str)
{
    std::istringstream ss(str);
    S num;
    ss >> num;
    return num;
}



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
            if (isalnum(*it))
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


    //SOMETHING IS WRONG WITH CALCULATE HERE NEED TO DEBUG
    //SEGFAULTING ON ITSELF
    T calculate(const T& x_val)
    {
        T y_val;
        std::stack<std::string> s;

        for (const char c : postfix)
        {
            auto iter = operators.find(c);
            if (iter != operators.end())
            {
                auto func = iter->second;
                T second = convert_to<T>(s.top());
                s.pop();
                T first = convert_to<T>(s.top());
                s.pop();
                T result = func(first, second);
                s.push(std::to_string(result));
            }
            else
            {
                if (std::to_string(c) == var)
                    s.push(std::to_string(x_val));
                else
                    s.push(std::to_string(c));
            }
        }

        return convert_to<T>(s.top());
    }



    void print()
    {
        std::cout << postfix << std::endl;
    }

};

}
