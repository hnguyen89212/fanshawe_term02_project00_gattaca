// ------------------------------------------------------------------------------------------------
// IMPORT LIBRARIES

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
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
 * Program "codonanalyzer" reads a sequence of nucleotides from console
 * 1. then counts the number of each genre of codon, i.e AAA, CAG or TTT, etc.
 * 2. counts the number of each type of amino acid
 * 3. reports a table of codons showing
 *		3.1 codon mnemonic
 *		3.2 codon code
 *		3.3 count
 *		3.4 percentage of total sequence
 * 4. reports a table of amino acids representing:
 *		4.1 acid name
 *		4.2 acid count
 *		4.3 percentage of total
 */

 // ------------------------------------------------------------------------------------------------
 // GLOBAL VARIABLES

 /* The array of amino acids, sorted in alphabetical order */
const char* aminoAcids[] = { "Alanine", "Arginine", "Arginine", "Asparagine", "Aspartic acid", "Cysteine", "Glutamic acid", "Glutamine", "Glycine", "Histidine", "Isoleucine", "Leucine", "Lysine", "Methionine", "Phenylalanine", "Proline", "Serine", "Serine", "Stop (Amber)", "Stop (Ochre)", "Stop (Opal)", "Threonine", "Tryptophan", "Tyrosine", "Valine" };

// ------------------------------------------------------------------------------------------------
// FUNCTIONS DECLARATION

/* Returns true if the character is either A, C, G or T. */
bool isValidNucleotide(char ch);

/* Converts a group of three nucleotides into a single code number, known as codon. */
int toCodonNumber(char* str);

/* Gets the assigned number of a nucleotide. In particular, A is 0, C is 1, G is 2, T is 3. */
int getNucleotideNumber(char ch);

/* From a group of 3 nucleotides, get the corresponding amino acid term.
For example, "nucleotide" is "AAT", return "Asparagine". */
char* getAminoAcid(char* nucleotide);

/* Given the string "acid" as argument, find the index of the match in the array "aminoAcids".
Return -1, if there is no match. */
int findMatchingAminoAcid(char* acid);

// ------------------------------------------------------------------------------------------------
// MAIN FUNCTION -- ENTRY POINT OF PROGRAM

int main() {
	int ch, i = 0, j = 0, k = 0, total = 0;
	// acidCounts[idx] contains the appearances of aminoAcids[idx]
	int acidCounts[25];
	for (i = 0; i < 25; i++)
		acidCounts[i] = 0;
	// A char array to hold nucleotides from input
	char codon[4] = { ' ', ' ', ' ', '\0' };
	// counts[0] contains the appearances of 'AAA', counts[63] contains that of 'TTT'.
	int counts[64];
	for (i = 0; i < 64; i++)
		counts[i] = 0;
	// There are 64 * 3 = 192 characters
	// Assume AAA, CGT and TTT appears in the input stream.
	// codons has the form ['A', 'A', 'A', ..., 'C', 'G', 'T', ..., 'T', 'T', 'T', '\0'];
	// other characters not listed is empty character.
	char codons[193];
	// Initialize the "codons" array.
	for (i = 0; i < 192; i++)
		codons[i] = ' ';
	codons[192] = '\0';
	// Reset i, j
	i = 0;
	j = 0;
	while ((ch = getchar()) != EOF) {
		// Turn to uppercase if needed
		if ('a' <= ch && ch <= 'z')
			ch = toupper(ch);
		// If ch is not a nucleotide, then skip
		if (!isValidNucleotide(ch))
			continue;
		codon[i++] = ch;
		// When "i" reaches 3, it is out of bound, we reset it back to 0.
		// This also implies that a group of 3 nucleotides are found; 
		if (i == 3) {
			j = toCodonNumber(codon);
			// If this first codon is ever caught from input, then update "codons", 
			// by copying the content of "codon" to "codons" at correct index
			if (counts[j] == 0) {
				k = j * 3;
				for (int u = 0; u < 3; u++)
					codons[k++] = codon[u];
			}
			// update the appearance of codon in "counts"
			counts[j]++;
			// increment the total appearances of codons
			total++;
			// reset i
			i = 0;
		}
	}
	// Print Codon Table
	printf("\n\nCondon Table\n");
	for (i = 0; i < 64; i++) {
		if (counts[i] > 0) {
			k = i * 3;
			memcpy(codon, &codons[k], 3 * sizeof(char));
			char* acid = getAminoAcid(codon);
			printf("%s (", codon);
			if (i < 10)
				printf("00%d", i);
			else
				printf("0%d", i);
			printf(") %d (%7.3f%%) %s\n", counts[i], (counts[i] * 100.0f / total), acid);
			// Finally, take advantage of this loop to count the appearances of the amino acids
			// Find the index of the matching amino acid
			ch = findMatchingAminoAcid(acid);
			// Increment the appearance of the found acid, the increase = the appearance of the codon
			acidCounts[ch] += counts[i];
		}
	}
	// Reset the "total", count the total number of amino acids that appear
	total = 0;
	for (i = 0; i < 25; i++)
		total += acidCounts[i];
	// Print Amino Acid Table
	// Determine the length of the amino acid with longest name, for the sake of formatting output
	unsigned int maxLen = 0;
	for (i = 0; i < 25; i++)
		if (acidCounts[i] > 0 && maxLen < strlen(aminoAcids[i]))
			maxLen = strlen(aminoAcids[i]);
	printf("\n\nAmino Acid Table\n");
	for (i = 0; i < 25; i++) {
		if (acidCounts[i] > 0) {
			int diff = maxLen - strlen(aminoAcids[i]);
			// Print spaces beforehand if needed
			for (j = 0; j < diff; j++)
				printf(" ");
			printf("%s %d (%7.3f%%)\n", aminoAcids[i], acidCounts[i], (acidCounts[i] * 100.0f / total));
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

int findMatchingAminoAcid(char* acid) {
	for (int j = 0; j < 25; j++)
		if (strcmp(acid, aminoAcids[j]) == 0)
			return j;
	return -1;
}