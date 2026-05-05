## Question 1 
[LAB BOOK - Add your Grid.h code]

### Solution 

```cpp
#pragma once
#include <fstream>
using namespace std;

template<class T>
class Grid
{
public:
    Grid();
    ~Grid();

    void LoadGrid(const char filename[]);
    void SaveGrid(const char filename[]);

private:
    T m_grid[9][9];
};


template<class T>
Grid<T>::Grid()
{
}

template<class T>
Grid<T>::~Grid()
{
}

template<class T>
void Grid<T>::LoadGrid(const char filename[])
{
    ifstream fin(filename);

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            fin >> m_grid[x][y];
        }
    }

    fin.close();
}

template<class T>
void Grid<T>::SaveGrid(const char filename[])
{
    ofstream fout(filename);

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            fout << m_grid[x][y] << " ";
        }
        fout << endl;
    }

    fout.close();
}
```

### Reflection 
In this task I converted the Grid class into a template so it could store different number types instead of just int. At first the program failed to compile, which helped me understand that template classes need all of their code in the header file so the compiler can generate the correct type. After moving the method implementations into Grid.h and removing Grid.cpp, the program compiled successfully and produced the same output file as in Lab D.

## Question 2 
[LAB BOOK - Add your the code from your main() function. Add the output of OutGrid.txt. Add a screenshot of the debugger showing the contents of the grid instance in main() after it has successfully loaded the values from file.]

## Solution 
```cpp
#include <iostream>
#include "Grid.h"
using namespace std;

int main (int, char**) {
	Grid<float> grid;
	grid.LoadGrid("Grid1.txt");
	grid.SaveGrid("OutGrid.txt");

	return 0;
}
```
## Output
1.5 2 3 4 5 6 7 8 9
2 3.5 4 5 6 7 8 9 1
3 4 5 6.25 7 8 9 1 2
4 5 6 7 8 9.75 1 2 3
5 6 7 8 9 1 2 3.25 4
6 7 8 9 1 2 3 4 5
7 8 9 1 2 3 4 5 6
8 9 1 2 3 4 5 6 7
9 1 2 3 4 5 6 7 8

<img width="1919" height="858" alt="image" src="https://github.com/user-attachments/assets/1398e7c5-9c81-45eb-bd03-77faaced8158" />

## Reflection 
In this task I updated the main() function to create a templated Grid<float> and load values from a text file. Using the debugger helped me check that the grid was fully populated after the file was read, without stepping through every loop iteration. The output file confirmed that the template class correctly handled floating-point values as well as integers.

## Question 3 
[LAB BOOK - Add your the code and an apprporiate description. Reflect on your solution.]

### Solution 
```cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool binarySearchRecursive(int* list, int size, int value)
{
    if (size <= 0)
        return false;

    int mid = size / 2;

    if (list[mid] == value)
        return true;
    else if (value < list[mid])
        return binarySearchRecursive(list, mid, value);
    else
        return binarySearchRecursive(list + mid + 1, size - mid - 1, value);
}

bool binarySearchIterative(int* list, int size, int value)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (list[mid] == value)
            return true;
        else if (value < list[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return false;
}

int main()
{
    int numbers[100];
    ifstream fin("binarysearchIn.txt");

    for (int i = 0; i < 100; i++)
    {
        fin >> numbers[i];
    }

    fin.close();

    srand(static_cast<unsigned int>(time(nullptr)));

    int searchValue = (rand() % 100) + 1;

    cout << "Target Number: " << searchValue << endl;

    bool foundRecursive = binarySearchRecursive(numbers, 100, searchValue);
    bool foundIterative = binarySearchIterative(numbers, 100, searchValue);

    cout << "Recursive search result: " << foundRecursive << endl;
    cout << "Iterative search result: " << foundIterative << endl;

    return 0;
}
```

### Example Output 
Target Number: 35
Recursive search result: 1
Iterative search result: 1

### Reflection 
Implementing both recursive and iterative binary search helped me understand how the same algorithm can be expressed in different ways. While the recursive version closely matches the theoretical description, I found the iterative version clearer to read and easier to trace in the debugger. Using a random search value also made it easier to test both successful and unsuccessful search cases.
