## Question 1 
[LAB BOOK - Copy your code for these functions into your lab book]
### Solution 
### Grid.h
```cpp
#pragma once
#include <iostream>

class Grid
{
public:
    Grid();
    ~Grid();

    void LoadGrid(const char filename[]);
    void SaveGrid(const char filename[]);

    friend std::istream& operator>>(std::istream& in, Grid& g);
    friend std::ostream& operator<<(std::ostream& out, const Grid& g);

private:
    int m_grid[9][9];
};
```
### Grid.cpp
```cpp
#include "Grid.h"
#include <fstream>

using namespace std;

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::LoadGrid(const char filename[])
{
    ifstream fin(filename);
    fin >> *this;         
    fin.close();
}

void Grid::SaveGrid(const char filename[])
{
    ofstream fout(filename);
    fout << *this;         
    fout.close();
}

istream& operator>>(istream& in, Grid& g)
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            in >> g.m_grid[x][y];
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Grid& g)
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            out << g.m_grid[x][y] << " ";
        }
        out << endl;
    }
    return out;
}
```

### Reflection
In this task, I added stream operators so the grid could be read from and written to any input or output stream. This helped me understand that files and the console both use the same stream system in C++. I also learned that the program does not show output unless the grid is explicitly sent to cout.

## Question 2
[LAB BOOK - Copy your code for your Fraction methods into your lab book]

## Solution 
```cpp
#include "Fraction.h"
#include <assert.h>

Fraction::Fraction() {
    m_num = 0;
    m_den = 1;
}

Fraction::Fraction(int num, int den) {
    assert(den != 0);
    m_num = num;
    m_den = den;
}

Fraction Fraction::Add(const Fraction& rhs) const {
    int num = m_num * rhs.m_den + rhs.m_num * m_den;
    int den = m_den * rhs.m_den;
    return Fraction(num, den);
}

Fraction Fraction::Subtract(const Fraction& rhs) const {
    int num = m_num * rhs.m_den - rhs.m_num * m_den;
    int den = m_den * rhs.m_den;
    return Fraction(num, den);
}

Fraction Fraction::Multiply(int scale) const {
    return Fraction(m_num * scale, m_den);
}

int Fraction::Num() const {
    return m_num;
}

int Fraction::Den() const {
    return m_den;
}

void Fraction::Num(int num) {
    m_num = num;
}

void Fraction::Den(int den) {
    assert(den != 0);
    m_den = den;
}

void Fraction::Write(ostream& sout) const {
    sout << m_num << "/" << m_den;
}

void Fraction::Read(istream& sin) {
    sin >> m_num >> m_den;
    assert(m_den != 0);
}
```

### Output
1/2 + 3/4 = 10/8
3/4 - 1/2 = 2/8
3/4 * 3 = 9/4

### Reflection 
In this task I implemented a Fraction class based on the example shown in lectures. I learned how to separate a class into a header file for declarations and a source file for method implementations. Writing the arithmetic, read, and write methods helped me understand how objects store data and interact with input and output. Overall, this exercise improved my understanding of basic object-oriented programming in C++.

## Question 3 
[LAB BOOK - Copy your code for your operators into your lab book. Reflect on the difference between class operators and auxiliary operators]

### Solution 
```cpp
Fraction Fraction::operator+(const Fraction& rhs) const {
    return Add(rhs);
}

Fraction Fraction::operator-(const Fraction& rhs) const {
    return Subtract(rhs);
}

Fraction Fraction::operator*(int scale) const {
    return Multiply(scale);
}

// Auxiliary operator
Fraction operator*(int scale, const Fraction& rhs) {
    return Fraction(rhs.m_num * scale, rhs.m_den);
}

// Stream operators
ostream& operator<<(ostream& out, const Fraction& rhs) {
    out << rhs.m_num << "/" << rhs.m_den;
    return out;
}

istream& operator>>(istream& in, Fraction& rhs) {
    in >> rhs.m_num >> rhs.m_den;
    assert(rhs.m_den != 0);
    return in;
```

### Sample Input
1, 2

### Output
1/2 + 3/4 = 10/8
3/4 - 1/2 = 2/8
3/4 * 3 = 9/4
3 * 3/4 = 9/4
1
2
Read = 1/2

### Reflection
I implemented class operators (operator+, operator-, operator*) to allow fractions to be added, subtracted, or multiplied by an integer using syntax like f1 + f2 or f2 * 3. I also added an auxiliary operator for 3 * f2, which is needed when the left-hand side is not a Fraction. This shows that class operators work on the object itself, while auxiliary operators handle cases where the object isn’t on the left.

## Question 4 
[LAB BOOK - Copy your code for pass-by-value and pass-by-ref into your lab book. Reflect on the difference between them]

### Solution 
```cpp
void myswap(int &lhs, int &rhs) {
	int temp = lhs;
	lhs = rhs;
	rhs = temp;
}
```

### Output 
a=10, b=20
a=20, b=10

### Reflection 
In this exercise, I learned the difference between passing by value and passing by reference. Passing by value creates copies of the variables, so changes inside the function don’t affect the originals. By using references (&), the function can directly modify the original variables, which allows myswap to successfully swap a and b. This demonstrates how references can be used to change data outside a function.

## Question 5
[LAB BOOK - Copy your code for return-by-value and return-by-ref into your lab book. Reflect on the difference between them]

### Solution 
```cpp
#include <iostream>
using namespace std;

void myswap(int& lhs, int& rhs) {
    int temp = lhs;
    lhs = rhs;
    rhs = temp;
}

int clamp(int value, int low, int high) {
    if (value < low)
        return low;
    if (value > high)
        return high;
    return value;
}

int& clamp_ref(int& value, int low, int high) {
    if (value < low)
        value = low;
    if (value > high)
        value = high;
    return value;
}

int main() {

    int a = 10;
    int b = 20;
    cout << "Before swap: a=" << a << ", b=" << b << endl;
    myswap(a, b);
    cout << "After swap:  a=" << a << ", b=" << b << endl << endl;

    int value1 = 10;
    int value2 = 20;
    int result1 = clamp(value1, 0, 30) + clamp(value2, 0, 30);
    cout << "Result1 (return by value) = " << result1 << endl;
    cout << "Original values after return by value: value1=" << value1 << ", value2=" << value2 << endl << endl;

    int result2 = clamp_ref(value1, 0, 5) + clamp_ref(value2, 0, 10);
    cout << "Result2 (return by reference) = " << result2 << endl;
    cout << "Original values after return by reference: value1=" << value1 << ", value2=" << value2 << endl;

    return 0;
}
```

### Output 
Before swap: a=10, b=20
After swap:  a=20, b=10

Result1 (return by value) = 30
Original values after return by value: value1=10, value2=20

Result2 (return by reference) = 15
Original values after return by reference: value1=5, value2=10

### Reflection 
n this exercise, I explored the difference between returning by value and returning by reference. Returning by value gives a copy of the result, so the original variable remains unchanged, as seen with clamp(). Returning by reference allows the function to modify the original variable and return its address, as shown with clamp_ref(). This demonstrates how references can be used to directly manipulate data, but also why returning references to local variables would be unsafe.
