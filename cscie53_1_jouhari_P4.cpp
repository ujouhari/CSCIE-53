/*
Name: Urvashi Jouhari
Assignment Name: CSCIE‐53 Problem Set 1 
File Name: Problem_Set1_P4.cpp
*/

/*
Problem:
Create a Rock - Paper - Scissors game score keeper.
The score is determined as follows:
Rock beats Scissors (by blunting them)
Scissors beat Paper (by cutting it)
Paper beats Rock (by covering it)
Two of the same item is a tie (no score)
Two players will play 5 rounds and “report” the results to the program after each round. The report will
be in the form of two letters using R for rock, S for scissors and P for paper. For example, SP means
that player one chose scissors and player 2 chose paper, and player 1 would “win” that round scoring 1
point. At the end of the 5 rounds, the program will announce the score and the winner.
Allow the player choices to be reported with upper or lowercase letters.
Input must be two letters adjacent (no spaces)

Part 2: (required for grad students, extra credit for undergraduate students)
Modify the program to function for any number of rounds with the score displayed every 5 rounds. Stop
when input is “quit” (case insensitive) and display the final score.
Next, lets add some artificial intelligence to the program. Analyze the behavior for player 1 only and
create a weight for how often player 1 chose each option. For example, you may determine that scissors
was selected 40% of the time, rock selected 50% of the time and paper selected 10% of the time.
Based on your analysis, create a series of random/weighted computer moves to defeat the player 1
move and then run your moves against the actual player 1 moves. Compute the new score. Display the
overall score and whether your “intelligent” play faired better than the play against player 2.
*/

#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>


using namespace std;

const int SIZE = 5000;

bool Problem4_Part1();
bool Problem4_Part2();
char Generate_Computer_Moves(char p1_moves[], int rounds);
int CalculateScores(char p1_move, char p2_move);

int main()
{
	//Problem4_Part1();
	Problem4_Part2();
	system("pause");
	return 0;
}

/*Create a Rock - Paper - Scissors game score keeper.*/
bool Problem4_Part1()
{
	char user_input[SIZE];
	char input_lc[SIZE];
	char p1_moves[SIZE];
	char p2_moves[SIZE];
	int p1_score = 0;
	int p2_score = 0;

	cout << "Enter Player Rounds:";
	cin.getline(user_input, SIZE);

	int len = strlen(user_input);
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (!(isspace(user_input[i])))
		{
			input_lc[j] = tolower(user_input[i]);
			j++;
		}
	}
	// Add terminator to end of string. 
	input_lc[j] = '\0';

	len = strlen(input_lc);

	// Check if user entered valid entries.
	for (int i = 0; i < len; i++)
	{
		if (!((input_lc[i] == 's') || (input_lc[i] == 'r') || (input_lc[i] == 'p')))
		{
			cout << "Please enter valid game entries." << endl;
			return false;
		}
	}
	// All even entries will be P1 entries
	// All odd entries will be P2 entries
	int k = 0, l = 0;
	for (int i = 0 ; i < len; i++)
	{
		if ((i % 2) == 0)
		{
			p1_moves[k] = input_lc[i];
			k++;
		}
		else
		{
			p2_moves[l] = input_lc[i];
			l++;
		}
	}

	// Number of rounds will be input string/2 ( 2 player entries )
	int rounds = strlen(input_lc)/2;
	cout << endl;
	
	for (int i = 0; i <= rounds; i++)
	{
		/*if (p1_moves[i] == p2_moves[i])
		{
			p1_score++;
			p2_score++;
		}*/
		if (p1_moves[i] == 's' && p2_moves[i] == 'p')
		{
			p1_score++;
		}
		else if (p1_moves[i] == 's' && p2_moves[i] == 'r')
		{
			p2_score++;
		}
		else if (p1_moves[i] == 'r' && p2_moves[i] == 's')
		{
			p1_score++;
		}
		else if (p1_moves[i] == 'r' && p2_moves[i] == 'p')
		{
			p2_score++;
		}
		else if (p1_moves[i] == 'p' && p2_moves[i] == 'r')
		{
			p1_score++;
		}
		else if (p1_moves[i] == 'p' && p2_moves[i] == 's')
		{
			p2_score++;
		}
	}

	cout << "P1 score:" << p1_score << endl;
	cout << "P2 Score:" << p2_score << endl;

	if (p1_score > p2_score)
	{
		cout << "Player 1 won." << endl;
	}
	else if (p1_score < p2_score)
	{
		cout << "Player 2 won." << endl;
	}
	else
	{
		cout << "Game was a tie." << endl;
	}

	return true;
}

bool Problem4_Part2()
{
	char user_input[SIZE];
	char input_lc[SIZE];
	char p1_moves[SIZE];
	char p2_moves[SIZE];
	char computer_moves[SIZE];

	int p1_score = 0;
	int p2_score = 0;
	int computer_score = 0;

	cout << "Enter Player Rounds:";
	cin.getline(user_input, SIZE, 'quit');
	//cout << endl << "User_input:" << user_input;

	int len = strlen(user_input);
	int j = 0;
	// Subtract 4 from length to not account for length.
	for (int i = 0; i < len-4; i++)
	{
		if (!(isspace(user_input[i])))
		{
			input_lc[j] = tolower(user_input[i]);
			j++;
		}
	}
	// Add terminator to end of string. 
	input_lc[j] = '\0';

	//cout << endl << "Input_lc:" << input_lc;

	len = strlen(input_lc);

	// Check if user entered valid entries.
	for (int i = 0; i < len; i++)
	{    
		if (!((input_lc[i] == 's') || (input_lc[i] == 'r') || (input_lc[i] == 'p')))
		{
			cout << "Please enter valid game entries." << endl;
			return false;
		}
	}
	// Number of rounds will be input string/2 ( 2 player entries )
	int rounds = len / 2;

	int k = 0, l = 0;
	for (int i = 0; i < len; i++)
	{
		// All even entries will be P1 entries
		if ((i % 2) == 0)
		{
			p1_moves[k] = input_lc[i];
			k++;
		}
		// All odd entries will be P2 entries.
		else
		{
			p2_moves[l] = input_lc[i];
			l++;
		}
	}
	p1_moves[rounds] = '\0';
	p2_moves[rounds] = '\0';

	//DEBUG PRINT
	/*for (int i = 0; i < rounds; i++)
	{
		cout << p2_moves[i] << endl;
	}*/
	
	//Create an array to store computer moves. 
	for (int i = 0; i < rounds; i++)
	{
		computer_moves[i] = Generate_Computer_Moves(p1_moves, rounds);
	}
	computer_moves[rounds] = '\0';

	//DEBUG PRINT
	/*cout << "Computer moves:";
	for (int i = 0; i < rounds; i++)
	{
		cout << computer_moves[i];
	}
	cout << endl;*/


	// Calculate score and declare Player 1 or Player 2 as winner. 
	int winner;
	for (int j = 0, index = 0; j < rounds/5; index + 5, j++)
	{
		p1_score = 0;
		p2_score = 0;
		cout << "Result for round " << j+1 << " between Player 1 and Player 2:" << endl;
		for (int i = index; i < index + 5; i++)
		{
			winner = CalculateScores(p1_moves[i], p2_moves[i]);
			if (winner == 1)
			{
				p1_score++;
			}
			if (winner == 2)
			{
				p2_score++;
			}
		}
	    
		cout << "P1 score:" << p1_score << endl;
		cout << "P2 Score:" << p2_score << endl;

		if (p1_score > p2_score)
		{
			cout << "Player 1 won." << endl;
		}
		else if (p1_score < p2_score)
		{
			cout << "Player 2 won." << endl;
		}
		else
		{
			cout << "Game was a tie." << endl;
		}
		cout << endl;
	}

	// Calculate if Player 1 did  better or Computer did. 
	p1_score = 0;
	computer_score = 0;
	for (int j = 0, index = 0; j < rounds / 5; index + 5, j++)
	{ 
		p1_score = 0;
		computer_score = 0;
		// Print out game
		cout << "Round" << j + 1 << " between Player 1 and Computer:" << endl;

		for (int i = index; i < index + 5; i++)
		{
			cout << p1_moves[i] << computer_moves[i] << " ";
		}
		cout << endl;

		cout << "Result for round " << j + 1 << " between Player 1 and Computer:" << endl;
		for (int i = index; i < index + 5; i++)
		{   
			winner = CalculateScores(p1_moves[i], computer_moves[i]);
			if (winner == 1)
			{
				p1_score++;
			}
			if (winner == 2)
			{
				computer_score++;
			}
		}

		cout  << "P1 score:" << p1_score << endl;
		cout  << "Computer Score:" << computer_score << endl;

		if (p1_score > computer_score)
		{
			cout << "Player 1 won." << endl;
		}
		else if (p1_score < computer_score)
		{
			cout << "Computer won against Player 1." << endl;
		}
		else
		{
			cout << "Game was a tie." << endl;
		}
	    cout << endl;
	}

	// Calculate if Computer did better or Player 2.
	p2_score = 0;
	computer_score = 0;
	for (int j = 0, index = 0; j < rounds / 5; index + 5, j++)
	{
		p2_score = 0;
		computer_score = 0;
		cout << "Result for round " << j + 1 << " between Computer and Player 2:" << endl;
		for (int i = index; i < index + 5; i++)
		{
			winner = CalculateScores(p2_moves[i], computer_moves[i]);
			if (winner == 1)
			{
				p2_score++;
			}
			if (winner == 2)
			{
				computer_score++;
			}
		}

		cout << "p2 score:" << p2_score << endl;
		cout << "computer Score:" << computer_score << endl;
		if (p2_score > computer_score)
		{
			cout << "Player 2 did better than Computer." << endl;
		}
		else if (p2_score < computer_score)
		{
			cout << "Computer did better than Player 2." << endl;
		}
		else
		{
			cout << "Computer and Player 2 tied." << endl;
		}
		cout << endl;

	}	
	return true;
}

/* Function to generate computer moves based on probability of Player 1 moves.*/
char Generate_Computer_Moves(char p1_moves[], int rounds)
{
	int r_tot = 0, p_tot = 0, s_tot = 0;
	for (int i = 0; i < rounds; i++)
	{
		if (p1_moves[i] == 'p') p_tot++;
		if (p1_moves[i] == 'r') r_tot++;
		if (p1_moves[i] == 's') s_tot++;
	}
	//cout << "Rounds:" << rounds;
	//cout << "Score Totals: R:" << r_tot << "S:" << s_tot << "P:" << p_tot << endl;
	
	double r_prob, p_prob, s_prob;

	r_prob = (r_tot * 100) / rounds;
	p_prob = (p_tot * 100) / rounds;
	s_prob = (s_tot * 100)  / rounds;

	//cout << "Probabilities: R:" << r_prob << "S:" << s_prob << "P:" << p_prob << endl;

	double min, med, max;
	char min_char, med_char, max_char;

	if ((r_prob <= s_prob) && (r_prob <= p_prob))
	{
		min = r_prob;
		min_char = 'r';
	}
	else if ((s_prob <= r_prob) && (s_prob <= p_prob))
	{
		min = s_prob;
		min_char = 's';
	}
	else if ((p_prob <= s_prob) && (p_prob <= r_prob))
	{
		min = p_prob;
		min_char = 'p';
	}

	if ((r_prob >= s_prob) && (r_prob >= p_prob))
	{
		max = r_prob;
		max_char = 'r';
	}
	else if ((s_prob >= r_prob) && (s_prob >= p_prob))
	{
		max = s_prob;
		max_char = 's';
	}
	else if ((p_prob >= s_prob) && (p_prob >= r_prob))
	{
		max = p_prob;
		max_char = 'p';
	}
	//DEBUG print
	/*cout << "Sorted Values: Min:" << min << "Max:" << max << endl;
	cout << "Sorted Values: Min_Char:" << min_char << "Max_Char:" << max_char << endl;*/

	if ((min_char == 'r' && max_char == 'p') || (min_char == 'p' && max_char == 'r'))
	{
		med = s_prob;
		med_char = 's';
	}
	else if ((min_char == 's' && max_char == 'p') || (min_char == 'p' && max_char == 's'))
	{
		med = r_prob;
		med_char = 'r';
	}
	else if ((min_char == 'r' && max_char == 's') || (min_char == 's' && max_char == 'r'))
	{
		med = p_prob;
		med_char = 'p';
	}

	//DEBUG print
	/*cout << "Sorted Values: Min:" << min << "Med:" << med << "Max:" << max << endl; 
	cout << "Sorted Values: Min_Char:" << min_char << "Med_Char:" << med_char << "Max_Char:" << max_char << endl;*/

	int computer_gen = rand() % 100;

	if ((computer_gen >= 0) && (computer_gen <= min))
	{   
		//cout << "Returning:" << min_char << endl;
		return min_char;
	}
	else if ((computer_gen > min) && (computer_gen <= (med + min)))
	{
		//cout << "Returning:" << med_char << endl;
		return med_char;
	}

	else if ((computer_gen > med) && (computer_gen <= (max + med)))
	{
		//cout << "Returning:" << max_char << endl;
		return max_char;
	}

	else return 0;
}

/* Calulate Scores between two players. Return 1 for Player 1 and 2 for Player 2.*/
int CalculateScores(char p1_move, char p2_move)
{
	if (p1_move == 's' && p2_move == 'p')
	{
		return 1;
	}
	else if (p1_move == 's' && p2_move == 'r')
	{
		return 2;
	}
	else if (p1_move == 'r' && p2_move == 's')
	{
		return 1;
	}
	else if (p1_move == 'r' && p2_move == 'p')
	{
		return 2;
	}
	else if (p1_move == 'p' && p2_move == 'r')
	{
		return 1;
	}
	else if (p1_move == 'p' && p2_move == 's')
	{
		return 2;
	}
	else return 0;
}


