/*
Name: Urvashi Jouhari
Assignment Name: CSCIE‐53 Problem Set 3 
File Name: cscie53_6_jouhari_P1.cpp
*/

/*
PROBLEM 1:
The problem: Create a function to replace a substring within a character array string.
char * replaceSubstring (char *original, char *subString, char *replaceString, int numOccurences);
input: the original string, the string to be replaced, the new string that will replace it, the number of
occurrences to replace.
Make as many replacements as specified – stop when the substring is no longer in the original string or
when the specified number of occurrences has been replaced. If the number of occurrences is 0,
replace all occurrences.
output: the updated string
Make the following assumptions:
1. The original string has been dynamically allocated
2. All input text is null terminated
3. numOccurences defaults to 0
3. The function should allocate enough space to store the new string after all replacements have been
made.
*/

#include <iostream>
#include <ctype.h>
#include <string.h>
using namespace std;

char *replaceSubstring(char *s, char *sub_string, char *new_string, int num_occurences);
char *findSubstring(char *s, char*sub_string);
void testReplaceSubString();

int main()
{
	testReplaceSubString();

	system("pause");
	return 0;
}

/*Make as many replacements as specified – stop when the substring is no longer in the original string or
when the specified number of occurrences has been replaced. If the number of occurrences is 0,
replace all occurrences.*/
char *replaceSubstring(char *s, char *sub_string, char *new_string, int num_occurences = 0)
{
	int s_len = strlen(s);
	int sub_string_len = strlen(sub_string);
	int new_string_len = strlen(new_string);
	int diff = 0;
	int padding = 5;
	char *psub_string = nullptr;
	char *psub_string_copy = nullptr;
	char *pnew_string = new_string;
	char *p_s_end = s + s_len -padding;

	int count = 1;

	//Replace all occurences if num_occurence is set to default value of zero.
	if (num_occurences == 0)
	{
		psub_string = findSubstring(s, sub_string);
		psub_string_copy = psub_string;
		int shift = sub_string_len - 1;

		if (psub_string == nullptr and count == 1)
		{
			cout << "Replace unsuccessful - Sub string not found in string" << endl;
			return s;
		}
		
		if (new_string_len > sub_string_len)
		{
			diff = new_string_len - sub_string_len;

			while (shift != 0)
			{
				psub_string_copy++;
				shift--;
			}//Now psub_string_copy should point to end of sub_string word.

			while (p_s_end != psub_string_copy)
			{
				*(p_s_end + diff) = *p_s_end;
				p_s_end--;
			}//shift string to the right by "diff"

			while (psub_string != nullptr)
			{
				for (int i = 0; i < new_string_len; i++)
				{
					*psub_string = new_string[i];
					psub_string++;
				}
				count++;
				psub_string = findSubstring(s, sub_string);
			}//This actually replaces the sub_string with new_string.
			return s;
		}

		else if (new_string_len < sub_string_len)
		{
			diff = sub_string_len - new_string_len;
			//left shift value
			int shift = new_string_len;
			while (shift != 0)
			{
				psub_string_copy++;
				shift--;
			}//Now psub_string_copy should point to middle of sub_string word where it is equal to length of new string.

			while (psub_string != nullptr)
			{
				for (int i = 0; i < new_string_len; i++)
				{
					*psub_string = new_string[i];
					psub_string++;
				}
				count++;
				psub_string = findSubstring(s, sub_string);
			}//This actually replaces the sub_string with new_string.

			while (psub_string_copy != p_s_end)
			{
				*psub_string_copy = *(psub_string_copy + diff);
				psub_string_copy++;
			}//shift string to the left by "diff"

			return s;
		}

		//default case sub-string = new_string
		else
		{
			while (psub_string != nullptr)
			{
				for (int i = 0; i < new_string_len; i++)
				{
					*psub_string = new_string[i];
					psub_string++;
				}
				count++;
				psub_string = findSubstring(s, sub_string);
			} //This actually replaces the sub_string with new_string.
			return s;
		}
	}

	//Replace string with substring num_occurence number of times.
	else
	{
		count = 1;
		while (num_occurences != 0)
		{
			
			psub_string = findSubstring(s, sub_string);
			psub_string_copy = psub_string;
			int shift = sub_string_len - 1;

			if (psub_string == nullptr and count == 1)
			{
				cout << "Replace unsuccessful - Sub string not found in string" << endl;
				return s;
			}//Fail if sub_string not found

			else if (psub_string == nullptr and count > 1)
			{
				cout << "Replace unsuccessful - Only " << count << " occurences of " << "\'" << sub_string << "\'" << " found" << endl;
				return s;
			}//Fail if num-occurences > actual number of times sub string occurs in string.

			if (new_string_len > sub_string_len)
			{
				diff = new_string_len - sub_string_len;

				while (shift != 0)
				{
					psub_string_copy++;
					shift--;
				}//Now psub_string_copy should point to end of sub_string word.

				while (p_s_end != psub_string_copy)
				{
					*(p_s_end + diff) = *p_s_end;
					p_s_end--;
				}//shift string to the right by "diff"

				for (int i = 0; i < new_string_len; i++)
				{
					*psub_string = new_string[i];
					psub_string++;
				}//replace sub-string once.
				//decrement num_occurences and re-do loop
				num_occurences--;
				count++;
			}

			else if (new_string_len < sub_string_len)
			{
				diff = sub_string_len - new_string_len;
				//left shift value
				int shift = new_string_len;
				
				while (shift != 0)
				{
					psub_string_copy++;
					shift--;
				}//Now psub_string_copy should point to middle of sub_string word where it is equal to length of new string.

				for (int i = 0; i < new_string_len; i++)
				{
					*psub_string = new_string[i];
					psub_string++;
				}//replace sub-string once.
				//decrement num_occurences and re-do loop
				num_occurences--;
				count++;

				while (psub_string_copy != p_s_end)
				{
					*psub_string_copy = *(psub_string_copy + diff);
					psub_string_copy++;
				}//shift string to the left by "diff"
			}
			//default case
			else 
			{
				for (int i = 0; i < sub_string_len; i++)
				{
					*psub_string = new_string[i];
					psub_string++;
				}
				num_occurences--;
				count++;
			}
		}
		return s;
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
				i = pos + 1;
				pos = 0;
				begin_pos = nullptr;
			}
		}
	}
	return begin_pos;
}


//Function to test problem 1
void testReplaceSubString()
{
	cout << "Test case 1: Replace 'short' with 'longest'" << endl;
	//Add extra padding here to allow shifting right
	char tmp[] = "This is a short string    ";
	char *ps = new char[strlen(tmp)+1];
    char sub_str[] = "short";
	char new_str[] = "longest";
	strcpy_s(ps, strlen(tmp)+1, tmp);
	cout << replaceSubstring(ps, sub_str, new_str);
	cout << endl << endl;
	delete[] ps;
	ps = nullptr;

	cout << "Test case 2: Attempt to replace 'long' with 'wa'" << endl;
	char s1[] = "This is a long string     ";
	char *ps1 = new char[strlen(s1) + 1];
	strcpy_s(ps1, strlen(s1) + 1, s1);
	char sub_str1[] = "long";
	char new_str1[] = "wa";
	cout << replaceSubstring(s1, sub_str1, new_str1);
	cout << endl << endl;
	delete[] ps1;
	ps1 = nullptr;
	
	cout << "Test case 3: Replace 'is' with 'xx' two times." << endl;
	char s2[] = "This is a short string     ";
	char *ps2 = new char[strlen(s2) + 1];
	strcpy_s(ps2, strlen(s2) + 1, s2);
	char sub_str2[] = "is";
	char new_str2[] = "xx";
	int num_occurences = 2;
	cout << replaceSubstring(s2, sub_str2, new_str2, num_occurences);
	cout << endl << endl;
	delete[] ps2;
	ps2 = nullptr;
	
	cout << "Test case 4: Replace 'is' with 'xx' five times." << endl;
	char s3[] = "This is a short string";
	char *ps3 = new char[strlen(s3) + 1];
	strcpy_s(ps3, strlen(s3) + 1, s3);
	char sub_str3[] = "is";
	char new_str3[] = "xx";
	int num_occurences3 = 5;
	cout << replaceSubstring(s3, sub_str3, new_str3, num_occurences3);
	cout << endl << endl;
	delete[] ps3;
	ps3 = nullptr;

	cout << "Test case 5: Replace all occurences of 'is' with 'xxx'." << endl;
	char s4[] = "This is a short string      ";
	char *ps4 = new char[strlen(s4) + 1];
	strcpy_s(ps4, strlen(s4) + 1, s4);
	char sub_str4[] = "is";
	char new_str4[] = "xxx";
	cout << replaceSubstring(s4, sub_str4, new_str4);
	cout << endl << endl;
	delete[] ps4;
	ps4 = nullptr;

}

