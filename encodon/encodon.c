// ------------------------------------------------------------------------------------------------
// IMPORT LIBRARIES

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

// ------------------------------------------------------------------------------------------------
// DOCUMENTATION

/*
 * Author/Coder: Hai Nguyen
 * StudentID: 0904995
 * Class/Course: INFO-1156 Object-oriented Programming in C++
 * Professor: Trinh Han
 * Assigned date: May 13th 2019
 * Due date: May 31st 2019 by 11:59 PM
 *
 * Description:
 * Program "encodon" reads a nucleotide sequences from the console and:
 * 1. outputs codon numbers to the console
 * 2. Non-GCAT nucleotides in the input stream are ignored
 */

 // ------------------------------------------------------------------------------------------------
 // FUNCTIONS DECLARATION

  /* Returns true if the character is either A, C, G or T. */
bool isValidNucleotide(char ch);

/* Converts a group of three nucleotides into a single code number, known as codon. */
int toCodonNumber(char* str);

/* Gets the assigned number of a nucleotide. In particular, A is 0, C is 1, G is 2, T is 3. */
int getNucleotideNumber(char ch);

// ------------------------------------------------------------------------------------------------
// MAIN FUNCTION -- ENTRY POINT OF PROGRAM

int main()
{
	// "i" is a counter variable, denoting the current index in char* "codon".
	// "i" should never exceeds 2. Because we wish to group 3 characters together to form a codon.
	// "ch" is a dummy variable. It stores a character from input stream one at a time.
	// "codon" is a character array. It contains a group of three letters in the set {A, C, G, T}.
	int ch, i;
	i = 0;
	char codon[3] = "   ";
	// As long as we have not reached the EOF character, execute the code block.
	// Get the next character from input stream
	while ((ch = getchar()) != EOF)
	{
		// Uppercase the character if needed
		if ('a' <= ch && ch <= 'z')
			ch = toupper(ch);
		// If ch is not a nucleotide, then skip
		if (!isValidNucleotide(ch))
			continue;
		// If the character "ch" is valid, i.e it is either A, C, G or T,
		// we store in the "codon" and update the counter "i".
		codon[i++] = ch;
		// When "i" reaches 3, it is out of bound, we reset it back to 0.
		// This also implies that a group of 3 nucleotides are found; 
		// Thus, we print the corresponding codon number.
		if (i == 3)
		{
			printf("%d ", toCodonNumber(codon));
			i = 0;
		}
	}
	return 0;
}

// ------------------------------------------------------------------------------------------------
// FUNCTIONS DEFINITION

bool isValidNucleotide(char ch)
{
	return (ch == 'G' || ch == 'C' || ch == 'A' || ch == 'T');
}

int toCodonNumber(char* str)
{
	return (getNucleotideNumber(str[0]) * 4 + getNucleotideNumber(str[1])) * 4 + getNucleotideNumber(str[2]);
}

int getNucleotideNumber(char ch)
{
	if (ch == 'A')
		return 0;
	else if (ch == 'C')
		return 1;
	else if (ch == 'G')
		return 2;
	else if (ch == 'T')
		return 3;
	else
		return INT_MIN;
}