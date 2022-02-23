This is a function parser I am building for personal use in my other implemented math projects.

Main use case is when a user inputs a function as a string (like "x^2 + 2*x + 3") and then the program will find a local minimum or something relavent to the function. In order to do this, the library will give values at various x values that the function takes on so the optimization methods can run.

Just started but basic idea is:
- build a stack where the function is in postfix notation instead of infix
- use that stack to return a value at each point 

