// ------------------------------------------------------------------------------------------------
// IMPORT LIBRARIES

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
 * Program "decodon" reads a stream of codon numbers from the console and prints out
 * 1. the codon number, codon mnemonic and amino-acid name
 */

 // ------------------------------------------------------------------------------------------------
 // FUNCTIONS DECLARATION

  /* Get nucleotide from the given assigned number.
  For example, n = 0, return 'A'. */
char getNucleotide(int);

/* From a group of 3 nucleotides, get the corresponding amino acid term.
For example, "nucleotide" is "AAT", return "Asparagine". */
char* getAminoAcid(char* nucleotide);

// ------------------------------------------------------------------------------------------------
// MAIN FUNCTION -- ENTRY POINT OF PROGRAM

int main() {
	char codon[] = "abc";
	int digits[3] = { 0, 0, 0 };
	int n, i, j;
	j = 0;
	while (scanf_s("%d", &n) == 1) {
		// n is beyond bound [0...63], ignore it
		if (n < 0 || n > 63)
			continue;
		// n is 1-digit number, print a space character
		if (n < 10)
			printf(" ");
		// print the number itself
		printf("%d ", n);
		// determines the digits f, s and t
		// assign them to the corresponding elements in "digits"
		for (i = 2; i > 0; i--) {
			while ((n - j) % 4 != 0)
				j++;
			digits[i] = j;
			n -= j;
			j = 0;
			n /= 4;
		}
		digits[i] = n;
		// look up tables, determine the corresponding characters in "codon"
		for (i = 0; i < 3; i++)
			codon[i] = getNucleotide(digits[i]);
		// print the string "codon"
		printf("%s ", codon);
		// print the amino acid
		printf("%s\n", getAminoAcid(codon));
	}
	return 0;
}

// ------------------------------------------------------------------------------------------------
// FUNCTIONS DEFINITION

char getNucleotide(int n) {
	switch (n)
	{
	case 0:
		return 'A';
	case 1:
		return 'C';
	case 2:
		return 'G';
	case 3:
		return 'T';
	default:
		return 'X';
	}
}

char* getAminoAcid(char* nucleotide)
{
	if (nucleotide[0] == 'G' && nucleotide[1] == 'C')
		return "Alanine";
	else if (nucleotide[0] == 'C' && nucleotide[1] == 'G' || strcmp(nucleotide, "AGA") == 0 || strcmp(nucleotide, "AGG") == 0)
		return "Arginine";
	else if (strcmp(nucleotide, "AAT") == 0 || strcmp(nucleotide, "AAC") == 0)
		return "Asparagine";
	else if (strcmp(nucleotide, "GAT") == 0 || strcmp(nucleotide, "GAC") == 0)
		return "Aspartic acid";
	else if (strcmp(nucleotide, "TGT") == 0 || strcmp(nucleotide, "TGC") == 0)
		return "Cysteine";
	else if (strcmp(nucleotide, "CAA") == 0 || strcmp(nucleotide, "CAG") == 0)
		return "Glutamine";
	else if (strcmp(nucleotide, "GAA") == 0 || strcmp(nucleotide, "GAG") == 0)
		return "Glutamic acid";
	else if (nucleotide[0] == 'G' && nucleotide[1] == 'G')
		return "Glycine";
	else if (strcmp(nucleotide, "CAT") == 0 || strcmp(nucleotide, "CAC") == 0)
		return "Histidine";
	else if (strcmp(nucleotide, "ATT") == 0 || strcmp(nucleotide, "ATC") == 0 || strcmp(nucleotide, "ATA") == 0)
		return "Isoleucine";
	else if (strcmp(nucleotide, "ATG") == 0)
		return "Methionine";
	else if (nucleotide[0] == 'C' && nucleotide[1] == 'T' || strcmp(nucleotide, "TTA") == 0 || strcmp(nucleotide, "TTG") == 0)
		return "Leucine";
	else if ((strcmp(nucleotide, "AAA") == 0 || strcmp(nucleotide, "AAG") == 0))
		return "Lysine";
	else if (strcmp(nucleotide, "TTT") == 0 || strcmp(nucleotide, "TTC") == 0)
		return "Phenylalanine";
	else if (nucleotide[0] == 'C' && nucleotide[1] == 'C')
		return "Proline";
	else if (nucleotide[0] == 'T' && nucleotide[1] == 'C' || strcmp(nucleotide, "AGT") == 0 || strcmp(nucleotide, "AGC") == 0)
		return "Serine";
	else if (nucleotide[0] == 'A' && nucleotide[1] == 'C')
		return "Threonine";
	else if (strcmp(nucleotide, "TGG") == 0)
		return "Tryptophan";
	else if (strcmp(nucleotide, "TAT") == 0 || strcmp(nucleotide, "TAC") == 0)
		return "Tyrosine";
	else if (nucleotide[0] == 'G' && nucleotide[1] == 'T')
		return "Valine";
	else if (strcmp(nucleotide, "TAG") == 0)
		return "Stop (Amber)";
	else if (strcmp(nucleotide, "TAA") == 0)
		return "Stop (Ochre)";
	else if (strcmp(nucleotide, "TGA") == 0)
		return "Stop (Opal)";
	else
		return "";
}
