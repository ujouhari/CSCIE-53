/*
Name: Urvashi Jouhari
Assignment Name: CSCIE‐53 Problem Set 3 
File Name: cscie53_6_jouhari_P3.cpp
*/

/*
PROBLEM 3:
Create a class called SmartArray that can dynamically grow and shrink. SmartArray is modeled
after the STL vector class.
Your Smart Array class should have the following data members:
 size of the array
 pointer to a block of memory to store the data
and methods:
 constructors – two overloads
- input is size of block and data value to populate each element (defaults to 0)
- input is initializer_list - make array large enough to accommodate all items in initializer
list
 default constructor
 copy constructor
 destructor
 addElements (int size, int value=0)
o increases the size of the array by the specified size – new items have the specified value
 replaceElements (int *fromArray, int howMany, int pos)
o Extracts howMany items from fromArray and places them at position: pos. Overwrite
current elements in the array. Grow the array if needed to store all values.
Example:
given current SmartArray data is: 1,2,3,4
pArray contains 101, 102, 103, 104, 105
replaceElements(pArray, 4, 2);
results in SmartArray data: 1,2,101, 102, 103, 104
 removeElements (int howMany, int pos=-1)
o removes howMany items from the array starting at position pos. Remove from the end if
pos is -1
 push_back(int value)
o adds space for one element at the end of the array and then stores the specified data
value
 pop_back()
o removes the last element from the array and returns its value
 valueAt(int pos)
o returns the data value at the specified position.
 at(int pos)
o returns a reference to the element at the specified position
 isEmpty()
o true if the array has 0 size
 empty()
o remove all elements – deallocate memory as needed
 size()
o returns the number of items in the array
Ground Rules: You may create any additional methods for the class that you feel will be helpful. All
data members should be private. Show test code to exercise all methods.
*/

#include <iostream>
#include <ctype.h>
#include<vector>
using namespace std;

const int SIZE = 5;

class SmartArray {
private:
	int m_capacity;
	int m_size;
	int *m_parray;
	
public:
	SmartArray();
	SmartArray(int a[]);
	SmartArray(int size, int element);
	SmartArray(const SmartArray & a);

	void addElements(int size, int value);
	void replaceElements(int *fromArray, int howMany, int pos);
	void removeElements(int howMany, int pos);
	void push_back(int value);
	int pop_back();
	int valueAt(int pos);
	int* at(int pos);
	bool isEmpty();
	void empty();
	int size();
	void show();
	~ SmartArray();
};

SmartArray::SmartArray()
	: m_capacity(0), m_parray(new int[m_capacity]), m_size(m_capacity)
{ }

SmartArray::SmartArray(int a[])
{
	m_capacity = SIZE;
	m_parray = new int[m_capacity];
	for (int i = 0; i < SIZE; i++)
	{
		m_parray[i] = a[i];
	}
	m_size = m_capacity;

}

SmartArray::SmartArray(int size, int element=0)
	: m_capacity(size), m_parray (new int[m_capacity]),m_size(m_capacity)
{
	for (int i = 0; i < m_capacity; i++)
	{
		m_parray[i] = element;
	}
}


SmartArray::SmartArray(const SmartArray &a)
{
	 m_capacity = a.m_capacity;
	 m_parray = a.m_parray;
	 m_size = a.m_size;
}

//increases the size of the array by the specified size – new items have the specified value
void SmartArray::addElements(int size, int value = 0)
{
	int *pnew_array;
	m_size = m_capacity + size;
	pnew_array = new int[m_size];
	//copy old values
	for (int i = 0; i < m_capacity; i++)
	{
		pnew_array[i] = m_parray[i];
	}
	//initialize remaining array with value
	for (int i = m_capacity; i < m_size; i++)
	{
		pnew_array[i] = value;
	}
	//delete old array
	delete[]m_parray;
	//reassign to new array
	m_parray = pnew_array;
	m_capacity = m_size;
}

/*Extracts howMany items from fromArray and places them at position: pos. Overwrite
current elements in the array.Grow the array if needed to store all values.
Example:
given current SmartArray data is: 1,2,3,4
pArray contains 101, 102, 103, 104, 105
replaceElements(pArray, 4, 2);
results in SmartArray data: 1,2,101, 102, 103, 104
*/
void SmartArray::replaceElements(int *fromArray, int howMany, int pos)
{
	int extra=0;
	//how much space does the array have
	int space = m_capacity - pos;
	//how many extra elements are we adding. If we have less space, we need to grow the array by extra
	if (space < howMany)
	{
		extra = howMany - space;
	}

	if (extra == 0)
	{
		//add howMany values fromArray into SmartArray
		for (int i = pos,j = 0; j < howMany; i++,j++)
		{
			m_parray[i] = fromArray[j];
		}
	}
	else
	{
		//increase size of the array by extra
		addElements(extra);

		//add howMany values fromArray into SmartArray
		for (int i = pos, j = 0; j < howMany; i++, j++)
		{
			m_parray[i] = fromArray[j];
		}
	}
}

//Removes howMany items from the array starting at position pos. Remove from the end if pos is - 1
void SmartArray::removeElements(int howMany, int pos = -1)
{
	int *pnew_array;
	m_size = m_capacity - howMany;
	pnew_array = new int[m_size];
	
	if (pos != -1)
	{
		//copy values before position
		for (int i = 0; i < pos; i++)
		{
			pnew_array[i] = m_parray[i];
		}
		for (int i = pos; m_size < m_capacity; i++)
		{
			pnew_array[i] = m_parray[i + howMany];
			m_capacity--;
		}
	}
	else 
	{
		for (int i = 0; i<m_size; i++)
		{
			pnew_array[i] = m_parray[i];
		}
	}
	//delete old array
	delete[]m_parray;
	//reassign to new array
	m_parray = pnew_array;
	m_capacity = m_size;

}

//adds space for one element at the end of the array and then stores the specified data value
void SmartArray::push_back(int value)
{
	addElements(1, value);
}

//removes the last element from the array and returns its value
int SmartArray::pop_back()
{
	int last_element = m_parray[m_capacity];
	removeElements(1, -1);
	return last_element;
}

//returns the data value at the specified position.
int SmartArray::valueAt(int pos)
{
	return m_parray[pos];
}
//returns a reference to the element at the specified position.
int* SmartArray::at(int pos)
{
	return (m_parray + pos);
}

//true if the array has 0 size
bool SmartArray::isEmpty()
{
	if (m_capacity == 0)
	{
		return true;
	}
	return false;
}

//remove all elements – deallocate memory as needed
void SmartArray::empty()
{
	removeElements(m_capacity);
}
//returns the number of items in the array
int SmartArray::size()
{
	return m_capacity;
}

//show all elements of array;
void SmartArray::show()
{
	for (int i = 0; i < m_capacity; i++)
	{
		cout << m_parray[i] << ' ';
	}
	cout << endl;
}

SmartArray::~SmartArray()
{ }

int main()
{
	SmartArray s;
	cout << "Smart array from default constructor: ";
	s.show();
	//bool true is 1.
    cout << "Result of s.isEmpty: "<< s.isEmpty();
	cout << endl;

	SmartArray s1(9, 5);
	cout << "Smart array s1(9,5): ";
	s1.show();
	//bool false is zero.
	cout << "Result of s1.isEmpty: " << s1.isEmpty();
	cout << endl;

	SmartArray s2 = s1;
	cout << "Smart array from copy constructor is: ";
	s2.show();
	
	int a2[4] = { 100,101,102,104 };
	cout << "Smart array s1 after replaceElements(a2, 3, 2): ";
	s1.replaceElements(a2, 3, 2);
	s1.show();
	cout << "Smart array s1 after replaceElements(a2, 3, 8): ";
	s1.replaceElements(a2, 3, 8);
	s1.show();
	cout << endl;

	int a[SIZE] = { 1,2,3,4,5 };
	SmartArray s3(a);
	cout << "Smart array s3 is: ";
	s3.show();
	cout << "Smart array s3 after removeElements(2, -1): ";
	s3.removeElements(2, -1);
	s3.show();
	cout << endl;

	SmartArray s4(a);
	cout << "Smart array s4 is:";
	s4.show();
	cout << "Smart array s4 after removeElements(2, 1): ";
	s4.removeElements(2, 1);
	s4.show();
	cout << "Smart array s4 after push_back(101): ";
	s4.push_back(101);
	s4.show();
	cout << "Smart array s4 after pop_back(): ";
	s4.show();
	cout << "Pop back value: " << s4.pop_back() << endl;
	cout << endl;

	SmartArray s5(a);
	cout << "Smart array s3 is: ";
	s5.show();
	cout << "Value of s5 at position 2, using valueAt(2) is: " << s5.valueAt(2) << endl;

	int *p_at = s5.at(3);
	cout << "Value of s5 at position 2, using at(3) is: " << *(p_at) << endl;

	s5.empty();
	cout << "Value of s5 after s5.empty: ";
	s5.show();
	cout << "Value of s5.isEmpty: " << s5.isEmpty();
	cout << endl;

	system("pause");
	return 0;
}
