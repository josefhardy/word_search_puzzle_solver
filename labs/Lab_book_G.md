## Question 1 
[Lab Book - Add screenshots of the Parasoft violation output. Then describe the corrections you made to remove the Parasoft Severity 1 and 3 violations]

### Solution 
```cpp
#pragma once
#include <iostream>

class Utility
{
public:
    Utility();
    ~Utility();

    Utility(const Utility&) = delete;            
    Utility& operator=(const Utility&) = delete;

    void SetSize(const int size);
    void Process() const;
    int Mult(int a, int b) const;

private:
    int* m_numberArray;
    int  m_size;
};
```
### Report View 
<img width="938" height="565" alt="image" src="https://github.com/user-attachments/assets/16ea7cc6-b3a7-47c4-b90d-6a699f2cfb33" />
<img width="953" height="365" alt="image" src="https://github.com/user-attachments/assets/8925f06f-7437-4271-817a-edd466dadb39" />

### Code Fixes 
#### Severity 1 violations 
Declare a copy assignment operator for classes with dynamically allocated memory (MRM-37-1): The class contained a raw pointer and a destrcutor this means that class manages dynamic memory 
which requires a copy assignment operator. The code has been changed to not allow the objet to be copied so no two objects can share the same pointer and potentially cause memory problems. 

Declare a copy constructor for classes with dynamically allocated memory (MRM-38-1): The error was generated because a class with a destrcutor and a raw pointer must declare a copy constructor. 
A copy constructor was created but is ended with =delete, to make sure the program does not allow copying of the Utility class 

#### Severity 3 violations 
If a function has no parameters, use ( ) instead of ( void ) (CODSTA-07-3): removed void from within the paranthesis 
  
Declare local variable as const whenever possible (CODSTA-CPP-53-3): object values were changed to const inside the Mult function to ensure they cannot be modified inside the fucntion 

If a public destructor of a class is non-virtual, then the class should be declared final (CODSTA-MCPP-23-3): The class has a pubic, non-virtual destructor which can be an issue if a class is built 
with inheritance in mind, however when the class was made non-copyable parasoft recognises it as closes so it does not require final. 

Both copy constructor and copy assignment operator should be declared for classes with a nontrivial destructor (MRM-40_d-3): There is explicit declaration of both fucntions and therefore satifies the rule

A copy constructor and a copy assignment operator shall be declared for classes that contain pointers to data items or nontrivial destructors (MRM-49-3): the class had a raw pointer and a 
nontrivial destrcutor and then exactly the same as before the appropriate functions were declared so the rule is satisfied 

### Reflection 

Fixing the Parasoft violations taught me the importance of writing safe and intentional C++ code. I learned how destructors, copy constructors, and copy assignment operators work together under the Rule of 3, especially when a class manages dynamic memory. I also improved my understanding of modern C++ practices, such as using () instead of (void) and avoiding unnecessary variables. The process showed me how static analysis tools can highlight hidden design issues, not just syntax problems. Overall, resolving these violations helped me produce cleaner, safer, and more maintainable C++ code.
