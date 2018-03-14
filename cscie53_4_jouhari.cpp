/*
Name: Urvashi Jouhari
Assignment Name: CSCIE‐53 Problem Set 2 
File Name: Problem_Set2.cpp
*/

#include <iostream>
#include <ctype.h>
#include <string>
#include <vector>
using namespace std;

void updatePay(vector<double> &v_pay, int raise);
void displayVector(vector<double> &v_pay);
void raisePay();
bool isStringPalindrome(char input_str[]);
void testPalindrome();
void insertNumbers(int *array, initializer_list<int> moreNumbers, int *insert_loc);
void testInsertNumbers();
bool replaceSubstring(char *s, char *sub_string, char *new_string);
char *findSubstring(char *s, char*sub_string);
bool replaceSubstringPart2(char *s, char *sub_string, char *new_string, int num_occurences);
void testReplaceSubString();

const int SIZE = 5000;
const int A_SIZE = 20;

int main()
{
	raisePay();

	testPalindrome();

	testInsertNumbers();

	testReplaceSubString();

	system("pause");
	return 0;
}

/*PROBLEM 1
The problem: Create a function called updatePay that takes as input a vector of doubles that represent
salary values and a raise percentage (as an integer). Update each salary value in the vector by the
amount of the raise. The function should have no return value.
Create a second function to display the values in the vector.
Create a test program that displays the vector, updates the values, and then displays the updated vector.
Ground Rules: Truncate values if needed after applying the update
*/
void updatePay(vector<double> &v_pay, int raise)
{
	for (auto &i: v_pay)
	{
		i += (i * raise / 100);
		i = static_cast<int> (i);
	}
}

//Function to display vector values.
void displayVector(vector<double> &v_pay)
{
	for (auto &i : v_pay)
	{
		cout << i << " ";
	}
	cout << endl;
}
// Function to calculate vector values after raise. 
void raisePay()
{
	vector<double> v_pay = { 300,350,420,275 };
	// Create a reference to v_pay
	vector<double> &rv_pay = v_pay;
	cout << "Vector before raise: ";
	displayVector(rv_pay);
	int raise = 5;
	updatePay(rv_pay, raise);
	cout << "Vector after raise: ";
	displayVector(rv_pay);
	cout << endl;
}

/*PROBLEM 2
The problem : Create a function that takes a character array string as input and returns true / false to
indicate whether the string is a palindrome.Disregard punctuation / white space.This is very similar to
problem2 in problem set 1 - except, you must use pointers not indexes to access the array elements. 
*/
bool isStringPalindrome(char input_str[])
{
	if (input_str[0] == '\0') 
	{
		//cout << "Please enter a non-empty string";
		return false;
	}

	//cout << "Input string received:" << input_str << endl;

	char strip_string[SIZE];
	int len = strlen(input_str);

	// Create string stripped off spaces, punctuations and converted to lower case.
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (!(ispunct(input_str[i]) || isspace(input_str[i])))
		{
			strip_string[j] = tolower(input_str[i]);
			j++;
		}
	}
	// Add terminator to end of string. 
	strip_string[j] = '\0';

	int len_strip = strlen(strip_string);
	//pointer to begining of strip_string
	char *pbegin = strip_string;
	//pointer to last char (before null terminator) of strip_string
	char *pend = &strip_string[len_strip - 1];

	while (pbegin < pend)
	{
		//cout << "Comparing characters:" << *pbegin << *pend << endl;

		if (*pbegin == *pend)
		{
			pbegin++;
			pend--;
		}
		else
		{
			//cout << "String is not a plaindrome" << endl;
			return false;
		}
	}
	//cout << "String is a palindrome" << endl;
	return true;

}

// Test function for Problem 2.
void testPalindrome()
{
	char test_string1[SIZE] = "A Man, A Plan, A Canal-Panama!";
	isStringPalindrome(test_string1);

	char test_string2[SIZE] = "Am I a palindrome?";
	isStringPalindrome(test_string2);

	char test_string3[SIZE] = "When the going gets tough, the tough get going";
	isStringPalindrome(test_string3);

	char test_string4[SIZE] = "Doc, note, I Dissent. A fast never prevents a fatness. I diet on cod.";
	isStringPalindrome(test_string4);

	char test_string5[SIZE] = "God, Art! Name no pup 'One Mantra Dog.'";
	isStringPalindrome(test_string5);

	char test_string6[SIZE] = "";
	isStringPalindrome(test_string6);
	
}

/*
PROBLEM 3
The problem : Create a function that inserts additional elements into an array of integers.You may
assume the array is large enough to accommodate the new elements.
void insertNumbers(int *array, initializer_list<int> moreNumbers, int *insert_loc);
where:
array is the original array of numbers
moreNumbers is a set of additional numbers to be inserted
insert_loc is a pointer into the array – new items should be inserted before the insertion point.If
insert_loc is null(nullptr), then items should be inserted at the front of the array*/
void insertNumbers(int *my_numbers, initializer_list<int> more_numbers, int *insert_loc=nullptr)
{	
	int *pend_loc = nullptr;
	auto len = more_numbers.size();

	//if pointer is null, point to first element in array.
	if (insert_loc == nullptr)
	{
		insert_loc = my_numbers;
	}

	int end_loc;
	for (int i = 0; i < A_SIZE; ++i)
	{
		if (my_numbers[i] == 0)
		{
			pend_loc = &my_numbers[i-1];
			end_loc = i;
			break;
		}
	}
	int *temp = insert_loc;

	int new_array_len;
	new_array_len = end_loc + len;

	int shift=1;
	for (int i = 0; i < A_SIZE; ++i)
	{
		//if insert_loc is at element 1, shift all elements
		if (insert_loc == my_numbers)
		{
			shift = new_array_len;
		}
		//if insert location is less that the last non-zero element of the array, shift only elements after the pointer
		else if (insert_loc < pend_loc)
		{
			while (temp != pend_loc)
			{
				temp++;
				shift++;
			}
		}
		//if insert_location is outside of non-zero array elements list, no need to shift. 
		else if (insert_loc > pend_loc)
		{
			shift = 0;
		}
	}

	while (shift != 0)
	{
		
	    //Copy value of end_location into array element at (end_loc + len) 
		*(pend_loc + len) = *pend_loc;
		pend_loc--;
		shift--;
	} 

	// pend_loc now should be same as insert_loc
	// insert initializer list elements into array.
	for (auto n : more_numbers)
	{
		*insert_loc = n;
		insert_loc++;
	}

	//Print new array
	cout << "New array is: ";
	for (int i = 0; i < A_SIZE; ++i)
	{
		cout << my_numbers[i] << " ";
	}
	cout << endl;
}

// Function to test Problem 3
void testInsertNumbers()
{
	cout << "Test with no insert location pointer:" <<endl;
	int my_numbers[20] = { 1,2,3,4,5,6,7,8,9,10 };
	insertNumbers(my_numbers, { 101, 102, 103});
	cout << endl;

	cout << "Test with insert location pointer set to 4" << endl;
	int my_numbers1[20] = { 1,2,3,4,5,6,7,8,9,10 };
    int *p1 = &my_numbers1[4];
	insertNumbers(my_numbers1, { 101, 102, 103 }, p1);
	cout << endl;

	cout << "Test with insert location pointer set to 15"<< endl;
	int my_numbers2[20] = { 1,2,3,4,5,6,7,8,9,10 };
	int *p2 = &my_numbers2[15];
	insertNumbers(my_numbers2, { 101, 102, 103 }, p2);
	cout << endl;

}

/*
PROBLEM 4
The problem: Create two functions that will replace a substring within a character array string.
a. Function1: bool replaceSubstring (char *s, char *subString, char *newString);
input: the original string, the string to be replaced, the new string that will replace it
output: true if the replace was successful, false if it is not
the replace can be unsuccessful if the substring is not found or if the newString is larger than the
original substring
note: this function should call findSubstring as a helper function.
b. Function2: char * findSubstring (char *s, char *substring);
input: the original string and the string to be found
output: a pointer to the beginning of the substring in the original string or nullptr if the substring
was not found
*/
bool replaceSubstring(char *s, char *sub_string, char *new_string)
{
	int s_len = strlen(s);
	int sub_string_len = strlen(sub_string);
	int new_string_len = strlen(new_string);
	int spaces = 0;
	char *psub_string = nullptr;

	if (new_string_len > sub_string_len)
	{
		cout << "Replace unsuccessful - New string is larger than the original sub string" << endl;
		return false;
	}

	psub_string = findSubstring(s, sub_string);

	if (psub_string == nullptr)
	{
		cout << "Replace unsuccessful - Sub string not found in string" << endl;
		return false;
	}

	for (int i = 0; i < sub_string_len; i++)
	{
		*psub_string = new_string[i];
		psub_string++;
	}
	cout << "Replaced string is: " << s << endl;
    return true;
}

/*
Change function1 as:
bool replaceSubstring (char *s, char *subString, char *newString, int numOccurences);
Make as many replacements as specified – stop when the substring is no longer in the original string or
when the specified number of occurrences has been replaced. If the number of occurrences is 0,
replace all occurrences.
Hint: Make the numberOccurences parameter default to 0*/
bool replaceSubstringPart2(char *s, char *sub_string, char *new_string, int num_occurences=0)
{
	int s_len = strlen(s);
	int sub_string_len = strlen(sub_string);
	int new_string_len = strlen(new_string);
	int spaces = 0;
	char *psub_string = nullptr;

	if (new_string_len > sub_string_len)
	{
		cout << "Replace unsuccessful - New string is larger than the original sub string" << endl;
		return false;
	}

	int count = 1;

	//Replace all occurences if num_occurence is set to default value of false.
	if (num_occurences == 0)
	{
		psub_string = findSubstring(s, sub_string);

		if (psub_string == nullptr and count == 1)
		{
			cout << "Replace unsuccessful - Sub string not found in string" << endl;
			return false;
		}

		while (psub_string != nullptr)
		{
			for (int i = 0; i < sub_string_len; i++)
			{
				*psub_string = new_string[i];
				psub_string++;
			}
			cout << "Replaced string is: " << s << endl;
			count++;
			psub_string = findSubstring(s, sub_string);
		}
		return true;
	}
	
	//Replace string with substring num_occurence number of times.
	else
	{
		count = 1;
		while (num_occurences != 0)
		{
			psub_string = findSubstring(s, sub_string);

			if (psub_string == nullptr and count == 1)
			{
				cout << "Replace unsuccessful - Sub string not found in string" << endl;
				return false;
			}
			else if (psub_string == nullptr and count > 1)
			{
				cout << "Replace unsuccessful - Only " << count << " occurences of " << "\'" << sub_string << "\'" << " found" << endl;
				return false;
			}
			else
			{
				for (int i = 0; i < sub_string_len; i++)
				{
					*psub_string = new_string[i];
					psub_string++;

				}
				cout << "Replaced string is: " << s << endl;
				num_occurences--;
				count++;
			}
		}
		return true;
	}
}

// Function to find substring in given string. Returns pointer to begining of substring in original string. 
char *findSubstring(char *s, char*sub_string)
{
	char *begin_pos = nullptr;

	int len = strlen(s);

	int pos = 0;
	for (int i = 0; i < len; i++)
	{
		int j = 0;
		if (s[i] == sub_string[j])
		{
			begin_pos = &s[i];
			pos = i; 

			while (s[i] == sub_string[j])
			{
				i++;
				j++;
			}
			if (sub_string[j] == '\0')
			{
				//cout << "Substring found at: " << pos << endl;
				return begin_pos;
			}
			else
			{
				i = pos+1;
				pos = 0;
				begin_pos = nullptr;
			}
		}
	}
	return begin_pos;
}

//Function to test problem 4
void testReplaceSubString()
{
	cout << "Test case 1: Replace 'short' with 'long '" << endl;
	char s[SIZE] = "This is a short string";
	char sub_str[SIZE] = "short";
	char new_str[SIZE] = "long ";
	replaceSubstring(s, sub_str, new_str);
	cout << endl;
	
	cout << "Test case 2: Attempt to replace 'long' with 'short'" << endl;
	char s1[SIZE] = "This is a long string";
	char sub_str1[SIZE] = "long";
	char new_str1[SIZE] = "short";
	replaceSubstring(s1, sub_str1, new_str1);
	cout << endl;

	cout << "Test case 3: Replace 'is' with 'xx' two times." << endl;
	char s2[SIZE] = "This is a short string";
	char sub_str2[SIZE] = "is";
	char new_str2[SIZE] = "xx";
	int num_occurences = 2;
	replaceSubstringPart2(s2, sub_str2, new_str2, num_occurences);
	cout << endl;

	cout << "Test case 4: Attempt to replace 'is' with 'xx' five times." << endl;
	char s3[SIZE] = "This is a short string";
	char sub_str3[SIZE] = "is";
	char new_str3[SIZE] = "xx";
	int num_occurences3 = 5;
	replaceSubstringPart2(s3, sub_str3, new_str3, num_occurences3);
	cout << endl;

	cout << "Test case 3: Replace all occurences of 'is' with 'xx'." << endl;
	char s4[SIZE] = "This is a short string";
	char sub_str4[SIZE] = "is";
	char new_str4[SIZE] = "xx";
	replaceSubstringPart2(s4, sub_str4, new_str4);
	cout << endl;

}

