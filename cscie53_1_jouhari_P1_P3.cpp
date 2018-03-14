/*Assignment Feedback:
Good organization. Good use of constants (P1_SIZE). 
No points yet deducted for optimization issues, but we will be in later assignments:
 Your loop would be more optimal if you searched up to num/2, instead of num 
 (since nothing after num/2 will divide evenly into num). 
 And while it’s true there will never be more than P1_SIZE divisors the way 
 the problem is setup, it would be a good habit to get into to validate that 
 ‘index’ never exceeds P1_SIZE (pretend this is a real-world problem). 
 Problem 2: Why compute len_strip? It is guaranteed to be the same as ‘j’. 
 Consider breaking out the ‘sanitize’ portion of the input processing into 
 a separate function. */ 

/*
Name: Urvashi Jouhari
Assignment Name: CSCIE‐53 Problem Set 1 
File Name: Problem_Set1.cpp
*/

#include <iostream>
#include <ctype.h>
#include <string>
#include <vector>
using namespace std;

const int P1_SIZE = 50;
const int P2_SIZE = 5000;

void Problem1();
bool Problem2();
bool Problem3();


int main()
{
	Problem1();
	//Problem2();
	//Problem3();

	system("pause");
	return 0;
}

/*
Problem : Get all divisors for a number between 1 and 200, store them in an array, display the array.
Ground rules : You may fix the array size to 50.
User Input : The number to factor
*/

void Problem1()
{
	int divisors[P1_SIZE];
	int num;
	cout << "Enter a number:";
	cin >> num;

	// Check to ensure the number is between 1-200
	if (num < 1 || num > 200)
	{
		cout << "Please enter a number between 1 and 200 only" << endl;
		cout << "Enter a number:";
		cin >> num;
	}

	// If modulus of number is equal to zero then the number is a divisor. 
	int index = 0;
	for (int i = 1; i <= num; i++)
	{
		if ((num % i) == 0)
		{
			divisors[index] = i;
			index++;
		}
	}

	//Print divisors with no comma at end of the last element.
	cout << "The divisors are:";
	for (int i = 0; i < index - 1; i++)
	{
		cout << divisors[i] << ", ";
	}
	cout << divisors[index - 1];

	cout << endl;

}

/*
Problem: Get a string and determine if it is a palindrome (reads the same forward and backwards
disregarding white space or punctuation). The string must be able to include punctuation. First, parse
the string and strip out all white space and punctuation. Then determine if the string reads the same
forward and backward.
Ground Rules: You must use a character array (i.e., do not use the string class). You may constrain the
maximum size for the length of the string. Use cin.getline() to allow the user to enter multiple words.
User Input: text
Output: indicate whether the string is a palindrome
*/

bool Problem2()
{
	char user_input[P2_SIZE];
	char strip_string[P2_SIZE];

	cout << "Enter some text:";
	cin.getline(user_input, P2_SIZE);
	cout << endl;

	int len = strlen(user_input);

	// Create string stripped off spaces, punctuations and converted to lower case.
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (!(ispunct(user_input[i]) || isspace(user_input[i])))
		{
			strip_string[j] = tolower(user_input[i]);
			j++;
		}
	}
	// Add terminator to end of string. 
	strip_string[j] = '\0';

	int len_strip = strlen(strip_string);

	// Compare first half of char array to reverse second half of char array.
	for (int i = 0, j = (len_strip-1); i < len_strip/2; i++, j--)
	{
		if (strip_string[i] != strip_string[j])
		{
			cout << "The string is not a palindrome." << endl;
			return false;
		}
	}
	cout << "The string is a plaindrome." << endl;
	return true;
}

/*
Problem : Get a series of words from the user.Display the longest and shortest word.
Ground Rules : Use the string class to store each word. Use a vector to store the set of words.Do not
use any STL functions such as sort() to make this “easier”.
User Input : Series of words.Stop when the user enters “stop”.
Output : Display the longest and shortest word entered(do not include “stop” for a candidate for longest
	or shortest word)
*/
bool Problem3()
{
	string word;
	vector<string> words;
	
	cout << "Enter some words, enter \"stop\" when you are done:" ;
	while (word.compare("stop") != 0)
	{
		cin >> word;
		if (word.compare("stop") != 0)
		{
			words.push_back(word);
		}
	}

	if (words.size() == 0)
	{
		cout << endl << "Please enter atleast one word"<< endl;
		return false;
	}

	string shortest = words[0];
	string longest = words[0];

	for (int i = 1; i != words.size(); i++)
	{
		if (words[i].length() < shortest.length())
		{
			shortest = words[i];
		}
		if (words[i].length() > longest.length())
		{
			longest = words[i];
		}
	}
	
	cout << "Longest word:" << longest << endl;
	cout << "Shortest word:" << shortest << endl;
	return true;
}


