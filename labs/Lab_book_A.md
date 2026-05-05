# Week one - Lab A

## Question one 
### Question 1.1:
Comment out the statement:

```c++
#include <iostream>
```

Compile the program.

What is the effect?

### Solution
```c++
//#include <iostream>
using namespace std;
```
### Sample Output
C2065 error messages, stating that cout and endl are undeclared identifiers. 
### Reflection
iostream is a header that declares the input & output system in C++, with it commented out the compiler can not recognise the cout and endl commands that are trying to write to the console.   

### Question 1.2
Now remove the statement

```c++
using namespace std;
```

Compile the program.  

What is the effect? 
### Solution
#include <iostream>

int main (int argc, char **argv) {

	cout << "Hello World" << endl;

	return 0;
}
### Sample Output
same errors as previous question 
### Reflection
cout and endl live inside the namespace std, with the namspace declaration missing the commands can not be declared as the compiler does nto recognise them. however you can use std:: before any use of cout and endl

## Question 2

Also what happens if you dividing two integers?

### Solution 
```cpp
#include <iostream> 

using namespace std;
int main(int argc, char** argv) 
{
	float fahrenheit, celsius; 

	cout << "Enter temperature in Fahrenheit: ";
	cin >> fahrenheit;

	celsius = 5.0 / 9.0 * (fahrenheit - 32);

	cout << "Temperature in Celsius: " << celsius << endl;
```
### Test Data 
100 (degrees in fahrenheit

### Sample output 
Temperature in Celsius: 37.7778

### Reflection 
The program is simple, however the provided formula for temperature conversion will result in a bug. The program sees '5/9' and recognises this as integer divisdion and the value is less than one and bigger than 0 so the value 0 is automatically assigned as the resiult and therefor corrupting the formulas reliability because any value entered will result in 0. 

## Question 3

Using the “Hello World” program as a starting point, write a program that prints out the size in bytes of each of the fundamental data types in C++.

### Solution 
```cpp
#include <iostream>
using namespace std;

int main (int argc, char **argv) 
{
	char c;
	signed char sc;
	unsigned char uc;

	short s;
	unsigned short us;

	int i;
	unsigned int ui;

	long l;
	unsigned long ul;
	long long ll;
	unsigned long long ull;

	float f;
	double d;
	long double ld;

	bool b;

	cout << "Size of different data types in C++:\n\n";
	cout << "char: "<<sizeof(c)<< " byte" << endl;
	cout << "signed char: "<<sizeof(sc)<<" byte" << endl;
	cout << "unsigned char: "<<sizeof(uc)<<" byte" << endl;
	cout << "short: "<<sizeof(s)<< " bytes" << endl;
	cout << "unsigned short: "<<sizeof(us)<<" bytes" << endl;
	cout << "integer: "<<sizeof(i)<< " bytes" << endl;
	cout << "unsigned integer: "<<sizeof(ui)<< " bytes" << endl;
	cout << "long: "<<sizeof(l)<< " bytes" << endl;
	cout << "unsigned long: "<<sizeof(ul)<< " bytes" << endl;
	cout << "long long: "<<sizeof(ll)<<" bytes" << endl;
	cout << "unsigned long long: "<<sizeof(ull)<< " bytes" << endl;
	cout << "float: "<<sizeof(f)<< " bytes" << endl;
	cout << "double: "<<sizeof(d)<< " bytes " << endl;
	cout << "long double: "<<sizeof(ld)<< " bytes" << endl;
	cout << "bool: "<<sizeof(b)<< " bytes" << endl;


	return 0;
}
```
### Sample Output
Size of different data types in C++:

char: 1 byte
signed char: 1 byte
unsigned char: 1 byte
short: 2 bytes
unsigned short: 2 bytes
integer: 4 bytes
unsigned integer: 4 bytes
long: 4 bytes
unsigned long: 4 bytes
long long: 8 bytes
unsigned long long: 8 bytes
float: 4 bytes
double: 8 bytes
long double: 8 bytes
bool: 1 bytes

### Reflection 
Unsigned and signed variables are allocated the same amount of storage space, the difference in application comes in potential value. Unsigned variables have double the maximum value of their signed counterparts as all bits are used for magnitude, whereas signed variables use 1 byte for the sign (+/-). Unsigned variables can onlt represent value of 0 or greater. 

## Question 4 
Did the program execute as expected?
How small does y have to be before you get a “divide by zero” error? Does the value of x affect the result?
### Solution
```cpp
#include <iostream>
using namespace std;

int main() {
    const double x = 100000.123456789;
    const double a = 200000.123456789;
    double y = (x + a) / x;
    double z = 1.0 + (a / x);
    if (y == z)
        cout << "y and z are identical" << endl;
    cout << "y and z are not identical" << endl; 


    double x2 = 1.0;

    // Smallest positive double
    double small = 1e-308;     // very small but nonzero
    double tiny = 1e-324;     // smaller than smallest double = rounds to 0

    cout << "x / small = " << x2 / small << endl;// very large resutl but not dividing by zero 
    cout << "x / tiny  = " << x2 / tiny <<endl;// essentially dividing by zero 
}
```
### Sample Output
y and z are not identical
x / small = 1e+308
x / tiny  = inf
### Reflection
Floating points and doubles numbers are not real numbers. Real numbers are exact and can be infinite, floats and doubles have limited space allocated to store values and they do not have the capacity to store most real numbers in binary form. Because of this "==" should be avoided when dealing with floats and doubles, this is because when doubles and floats are computed there may be small amounts of rounding to store the numbers as accurately as possible, but when operations and comparisons are carried out on these numbers "==" may provide false negatives. For example:
```cpp

double x = 0.1
double y = 0.2
double z = 0.3

if((y + x) == z)
	cout<< "True" <<endl
cout<< "False" <<endl
```
This program will return false even though it is mathematically true. 

In maths a dividing by zero problem only comes about when the divisor is exactly 0 but in c++ if the number is too small to be stored in a double or a float then you will get a dividing by zero error. 

## Question 5
Port the above C# code in to C++ using the provided Main.cpp file.

## Solution 
```cp
#include <iostream>
using namespace std;

int main() {
    int factorialNumber = 5;
    int factorialTotal = 1;

    for (int n = 2; n <= factorialNumber; ++n) {
        factorialTotal *= n;
    }

    cout << factorialTotal << endl;
}
```
## Sample Output
120
## Reflection 
- The entry point was changed from the C# standard to int main(), no arguements were needed because the values are hardcoded. 
- Console.WriteLine() is changed to cout<< " " <<endl
- <iostream> header included to make use of cout

## Question 6 
calculate the average value of values provided by the user from the console

### Solution 
```cpp
#include <iostream>
using namespace std;

int main() {
    int factorialNumber = 5;
    int factorialTotal = 1;

    for (int n = 2; n <= factorialNumber; ++n) {
        factorialTotal *= n;
    }

    cout << factorialTotal << endl;

    int total = 0;
    int count = 0; 
    int n = 0;
    do
    {
        cout << "Please enter an int value, then press Enter press -1 to exit" << endl;
        cin >> n;

        if (n != -1) { total += n; count += 1; }
    } while (n != -1);
        
    cout << " The average is " << total / count << endl;
}
```
## Test Data 
5, 3, 2, 1, 4, -1

## Sample Output
Please enter an int value, then press Enter press -1 to exit
5
Please enter an int value, then press Enter press -1 to exit
3
Please enter an int value, then press Enter press -1 to exit
2
Please enter an int value, then press Enter press -1 to exit
1
Please enter an int value, then press Enter press -1 to exit
4
Please enter an int value, then press Enter press -1 to exit
-1
 The average is 3

 ## Reflection 
 Variables must be assigned a value at declaration to manipulate their value, int i; will not work. cin gets an input from the keyboard/user 
