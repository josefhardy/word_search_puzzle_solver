## Question 1 
Lab Book - Add your code and describe what you have done

### Solution 
#### PersonNode.h 
```cpp
#pragma once

#include <string>
using namespace std;

class AddressBookSLL;

class PersonNode
{
public:
	PersonNode(void);
	PersonNode(const string& name, int age);
	~PersonNode(void);

	void setName(const string& name) { m_name = name; }
	void setAge(int age) { m_age = age; }

	string getName(void) const { return m_name; }
	int getAge(void) const { return m_age; }


private:
	string m_name;
	int m_age;
	PersonNode* m_next;

	friend class AddressBookSLL;
};

```

### Reflection 
I implemented the PersonNode class to represent a node in a singly linked list. I added getter and setter methods for the name and age attributes. I also included a pointer to the next node (m_next) and ensured it is initialised to nullptr in the constructors. Additionally, I used a forward declaration and made the AddressBookSLL class a friend of PersonNode so it can directly access private members like m_next for efficient traversal.

## Question 2
[Lab Book - Add your code and describe what you have done]

### Solution 
#### AddressBookSLL.cpp
```cpp
#include "AddressBookSLL.h"

AddressBookSLL::AddressBookSLL(void) : m_head(nullptr)
{
}

void AddressBookSLL::AddPerson(const string& name, int age)
{
    PersonNode* newNode = new PersonNode(name, age);

    if (m_head == nullptr)
    {
        m_head = newNode;
    }
    else if (m_head->m_next == nullptr)
    {
        m_head->m_next = newNode;
    }
    else
    {
        PersonNode* current = m_head;

        while (current->m_next != nullptr)
        {
            current = current->m_next;
        }

        current->m_next = newNode;
    }
}

AddressBookSLL::~AddressBookSLL(void)
{
    if (m_head == nullptr) return;

    while (m_head->m_next != nullptr)
    {
        PersonNode* previous = m_head;
        PersonNode* current = m_head;

        while (current->m_next != nullptr)
        {
            previous = current;
            current = current->m_next;
        }

        delete current;
        previous->m_next = nullptr;
    }

    delete m_head;
    m_head = nullptr;
}
```
#### AddressBookSLL.h 
```cpp
#pragma once

#include "PersonNode.h"

class AddressBookSLL
{
public:
	AddressBookSLL(void);
	~AddressBookSLL(void);

	void AddPerson(const string& name, int age);

private:
	PersonNode* m_head;
};

```

### Output 
People added to address book.

### Reflection 
I implemented the AddressBookSLL class to manage a singly linked list of PersonNode objects using a head pointer. The AddPerson method adds new nodes to the end of the list by checking if the list is empty or traversing to the last node. I also implemented a destructor to delete all dynamically allocated nodes and prevent memory leaks. This task improved my understanding of linked lists, pointers, and memory management in C++.

## Question 3 
[Lab Book - Add your code and describe what you have done]

### Solution 
#### AddressBookSLL.h 
```cpp
#pragma once

#include "PersonNode.h"

class AddressBookSLL
{
public:
	AddressBookSLL(void);
	~AddressBookSLL(void);

	void AddPerson(const string& name, int age);
	const PersonNode* FindPerson(const string& name) const;
	bool DeletePerson(const string& name);
	void PrintAll() const;

private:
	PersonNode* m_head;
};
```
#### AddresssBookSLL.cpp
```cpp
#include "AddressBookSLL.h"
#include <iostream>

AddressBookSLL::AddressBookSLL(void) : m_head(nullptr)
{
}

void AddressBookSLL::AddPerson(const string& name, int age)
{
    PersonNode* newNode = new PersonNode(name, age);

    if (m_head == nullptr)
    {
        m_head = newNode;
    }
    else if (m_head->m_next == nullptr)
    {
        m_head->m_next = newNode;
    }
    else
    {
        PersonNode* current = m_head;

        while (current->m_next != nullptr)
        {
            current = current->m_next;
        }

        current->m_next = newNode;
    }
}

AddressBookSLL::~AddressBookSLL(void)
{
    if (m_head == nullptr) return;

    while (m_head->m_next != nullptr)
    {
        PersonNode* previous = m_head;
        PersonNode* current = m_head;

        while (current->m_next != nullptr)
        {
            previous = current;
            current = current->m_next;
        }

        delete current;
        previous->m_next = nullptr;
    }

    delete m_head;
    m_head = nullptr;
}

const PersonNode* AddressBookSLL::FindPerson(const string& name) const
{
    PersonNode* current = m_head;

    while (current != nullptr)
    {
        if (current->m_name == name)
        {
            return current;
        }
        current = current->m_next;
    }

    return nullptr;
}

bool AddressBookSLL::DeletePerson(const string& name)
{
    if (m_head == nullptr) return false;

    if (m_head->m_name == name)
    {
        PersonNode* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
        return true;
    }

    PersonNode* current = m_head;

    while (current->m_next != nullptr)
    {
        if (current->m_next->m_name == name)
        {
            PersonNode* temp = current->m_next;
            current->m_next = temp->m_next;
            delete temp;
            return true;
        }
        current = current->m_next;
    }

    return false;
}

void AddressBookSLL::PrintAll() const
{
    PersonNode* current = m_head;

    while (current != nullptr)
    {
        std::cout << current->m_name << " (" << current->m_age << ")\n";
        current = current->m_next;
    }
}
```

### Output
Darren (21)
Dawn (42)
Found: Dawn
Dawn (42)

### Reflection 
I added functionality to find, delete, and display people in the linked list. The find method searches through the list and returns a pointer if a match is found. The delete method removes a node by updating pointers and freeing memory. The output function traverses the list and prints each person’s details. This improved my understanding of traversal and pointer manipulation in linked lists.
