## Question 1
 Record the steps required to enter arguments into Visual Studio
 ## Solution 

 ```cpp
#include <iostream>
#include <fstream>
using namespace std;


bool Copy(char filenamein[], char filenameout[])
{
	return false;
}

int main(int argn, char* argv[])
{
	if (argn != 3) {
		cerr << "Usage: " << argv[0] << " <input filename> <output filename>" << endl;
		int keypress; cin >> keypress;
		return -1;
	}

	if (Copy(argv[1], argv[2]))
	{
		cout << "Copy successful" << endl;
	}
	else
	{
		cout << "Copy error" << endl;
	}

	system("PAUSE");
}
```

### Sample Output
Copy error

### Reflection 
Arguments can be passed into a C++ program through properties' debugging command line arguemnt's box. Values are not assigned unless explicity provided. Arguemnts are stored in the argv array, in this program argv[1] being the input file name and argv[2] being the output file name. argv[0] is the executable file name.  
The steps i took were to right click on the project, select properties and then debugging and copy the given arguements into the command line arguements box. 
## Question 2
Add you code to your lab book and reflect on how you tested your code
### Solution 
```cpp
bool Copy(char filenamein[], char filenameout[])
{
	ifstream inFile(filenamein);
	ofstream outFile(filenameout);

	if (!inFile || !outFile) { cout << " Failed to open files" << endl; return false; }

	char c;
	while (inFile.get(c))
	{
		outFile.put(c);
	}

	return true;

}
```
### Test Data 1
command line arguements = "fake.txt" and "output.txt"
### Sample Output 1
Failed to open files
Copy error
### Test Data 2
command line arguements = "input.txt" and "output.txt"
### Sample Output 2
Copy successful
### Reflection 
If arguements are passed that do not exist then the program will return an error message and crash unless handled correctly. ifstream and outstream are file stream variable types they create streams that reads data from a file into my program or vice versa. In this scenario inFile and outFile are variable names that represent the connection to the stream. 
## Question 3 
Add you code to your lab book and reflect on how you tested your code
### Solution 
```cpp
#include <iostream>
using namespace std;

void myFunction(int x, double y, char z) {
    cout << "x=" << x << ", y=" << y << ", z=" << z << endl;
}

int mymax(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int main(int, char**) {
    int a = 10;
    int b = 20;

    int max = mymax(a, b);

    cout << "a=" << a << ", b=" << b << endl;
    cout << "max=" << max << endl;

    int n = 5;
    double d = 3.14;
    char c = 'A';

    myFunction(n, d, c); 

    return 0;
}
```

### Sample Output
a=10, b=20
max=20
x=5, y=3.14, z=A
### Relflection
In this lab, I observed how C++ functions are executed at the assembly level using Visual Studio’s Debugger. I saw how variables are initialized, how function parameters are passed (via registers and stack), and how return values are stored in the EAX register. Stepping through mymax highlighted stack frame setup and conditional jumps corresponding to if(a > b).

Adding my own myFunction with different parameter types showed how the compiler handles various data types and memory alignment. Using the Registers and Memory windows helped me visualize the stack layout and argument placement.

Overall, this lab strengthened my understanding of how high-level C++ code maps to low-level operations, how the stack is managed, and how function calls work at a machine level. It improved my confidence in reading assembly and debugging programs.
