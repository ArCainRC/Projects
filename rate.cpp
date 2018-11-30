#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;

int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns)
{
	if (nPatterns < 0)	// if nPatterns is negative, we are supposed to treat it like 0
	{
		nPatterns = 0;
	}

	for (int i = 0; i < nPatterns; i++)	// a loop for checking if each cstring of word1 and word2 is invalid(empty or containing non-alphabetical characters)
	{
		int skipCheck = 0;	// an integer used to check if the rest of the loop should be executed or move to the next iteration, necessary to exit double loops

		// cerr << " I access " << i << endl;
		if (separation[i] < 0)	// if the separation value is negative
		{
			// cerr << "negative sep" << endl;
			for (int j = i; j < nPatterns-1; j++)	// to effectively remove the empty cstring, its corresponding cstring in the other array, and their seperation number
			{
				strcpy(word1[j], word1[j + 1]);
				strcpy(word2[j], word2[j + 1]);
				separation[j] = separation[j + 1];
			}
			nPatterns--;	// to reduce the count of valid element pairs of the arrays
			i--;	// to start out from the same position on the next loop iteration, in order to check the new element moved here
			continue;	// skips the rest of loop, and starts a new iteration, as we need to recheck all conditions
		}		
		
		
		if (strlen(word1[i]) == 0 || strlen(word2[i]) == 0)	// if the cstring of either word1 or word2 is empty
		{
			// cerr << "empty" << endl;
			for (int j = i; j < nPatterns-1; j++)	// to effectively remove the empty cstring, its corresponding cstring in the other array, and their seperation number
			{
				strcpy(word1[j], word1[j + 1]);
				strcpy(word2[j], word2[j + 1]);
				separation[j] = separation[j + 1];
			}
			nPatterns--;	// to reduce the count of valid element pairs of the arrays
			i--;	// to start out from the same position on the next loop iteration, in order to check the new element moved here
			continue;	// skips the rest of loop, and starts a new iteration, as we need to recheck all conditions
		}

		for (int j = 0; word1[i][j] != '\0'; j++)	// to check if all the cstrings of word1 consist solely of alphabets 
		{
			if (!isalpha(word1[i][j]))
			{
				// cerr << "error found at " << word1[i] << endl;
				for (int j = i; j < nPatterns-1; j++)	// to effectively remove the empty cstring, its corresponding cstring in the other array, and their seperation number 
				{
					strcpy(word1[j], word1[j + 1]);
					strcpy(word2[j], word2[j + 1]);
					separation[j] = separation[j + 1];
				}
				nPatterns--;	// to reduce the count of valid element pairs of the arrays
				i--;	// to start out from the same position on the next loop iteration, in order to check the new element moved here
				skipCheck = 1;	// to be able to restart the outer for loop
				break;	// to exit the inner for loop
			}
		}
		if (skipCheck == 1)	// if skipCheck is 1, a new iteration of this loop will occur, so that all the conditions are rechecked for the new cstring in this same position
		{
			continue;
		}
	


		for (int j = 0; word2[i][j] != '\0'; j++)	// same as the previous for loop, except applied on word2
		{
			if (!isalpha(word2[i][j]))
			{
				// cerr << "error found at " << word2[i] << endl;
				for (int j = i; j < nPatterns-1; j++)
				{
					strcpy(word1[j], word1[j + 1]);
					strcpy(word2[j], word2[j + 1]);
					separation[j] = separation[j + 1];
				}
				nPatterns--;
				i--;
				skipCheck = 1;
				break;
			}
		}
		if (skipCheck == 1)
		{
			continue;
		}
	}

	for (int i = 0; i < nPatterns; i++)	// to make all the characters of each string lowercase
	{
		for (int j = 0; j < strlen(word1[i]); j++)
		{
			char b = tolower(word1[i][j]);
			word1[i][j] = b;
		}
		for (int j = 0; j < strlen(word2[i]); j++)
		{
			char b = tolower(word2[i][j]);
			word2[i][j] = b;
		}
	}

	for (int i = 0; i < nPatterns; i++)	// to remove duplicate instances of pairs
	{
		for (int j = 0; j < i; j++)
		{
			if ((strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0)	// duplicate check condition
				|| (strcmp(word1[i], word2[j]) == 0 && strcmp(word2[i], word1[j]) == 0))
			{
				if (separation[i] > separation[j])	// if-else statement used to remove the duplicate with lower seperation value
				{
					for (int k = j; k < nPatterns-1; k++)
					{
						strcpy(word1[k], word1[k + 1]);
						strcpy(word2[k], word2[k + 1]);
						separation[j] = separation[j + 1];
					}
					nPatterns--;	// to reduce the count of valid element pairs of the arrays
					i--;	// to start out from the same position on the next loop iteration, in order to check the new element moved here
				}
				else  // if both seperation values are equal, we remove the later instance of the word pair
				{
					for (int k = i; k < nPatterns-1; k++)
					{
						strcpy(word1[k], word1[k + 1]);
						strcpy(word2[k], word2[k + 1]);
						separation[j] = separation[j + 1];
					}
					nPatterns--;	// to reduce the count of valid element pairs of the arrays
					i--;	// to start out from the same position on the next loop iteration, in order to check the new element moved here
				}
			}
		}
	}
	return nPatterns;	// returns the number of valid cstring pairs from the arrays
}

int rate(const char document[],
	const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[],
	int nPatterns)
{
	int rating = 0;	// the rating of the document, the number of patterns found in it
	char modDoc[251];	// an array with maximum size of 251 elements, as document[] has a maximum size of 251
	strcpy(modDoc, document);	// copies the constant array document onto modDoc, so that we can modify it in order to perform pattern checks
	
	for (int i = 0; modDoc[i] != '\0'; i++)	// a loop where we remove non-alphabetical characters that aren't spaces
	{
		if ((!isalpha(modDoc[i])) && modDoc[i] != ' ')	// checking for non-alphabetical characters
		{
			
				for (int j = i; modDoc[j] != '\0'; j++)	// removing them from the array by copying over them
				{
					char b = modDoc[j + 1];
					modDoc[j] = b;
				}
				i--;	// to start out from the same position on the next loop iteration, in order to check the new element moved here 
			
		}
	}

	for (int i = 0; modDoc[i] != '\0'; i++)	// turning all alphabetical characters of the modified document (modDoc) lowercase
	{
		char b = tolower(modDoc[i]);
		modDoc[i] = b;
	}

	char indiWords[251][251];	// a cstring array, where the individual words of the cstring modDoc will be placed, in order to check for patterns // to make a cstring array from the continuous cstring of modDoc, in order to check for patterns
								// since the maximum number of characters in the document is 250: 1. there will always be less than 251 words, and 2. a word from this array can only have 251 characters at most
	int p = 0;	// an integer to check the total number of words and also to help place words into the cstring array
	for (int i = 0; i < strlen(modDoc); i++)	// a loop to check every letter of modDoc
	{
		if (isalpha(modDoc[i]))	// if the character is a letter, begins a new cstring to accomodate a word
		{
			char newWord[251] = { "" };	// an empty cstring with a length of 251 characters, where the word will be placed

			for (int j = 0; isalpha(modDoc[i]); j++)	// a loop where all the characters of the word are added onto the cstring
			{
				if (modDoc[i] == '\0')	// if the zero byte is encountered, break the loop, to prevent an out-of-bounds error
				{
					break;
				}
				newWord[j] = modDoc[i];	// adding the char onto the cstring
				i++;	// increasing the position of i while the iterations of the for loop occur
			}

			strcpy(indiWords[p], newWord);	// copying the word extracted onto the cstring array
			p++;	// increasing the word count
		}
	}


	for (int i = 0; i < nPatterns; i++)	// a loop to check the number of patterns in the cstring array of the words of document
	{
		char wordToCheck[251] = {};	// creating an empty cstring and copying a cstring from word1 onto it
		strcpy(wordToCheck, word1[i]);		

		for (int j = 0; j < p; j++)	// creates a for loop to check every word of the array of document words, with p being the number of words, as we previously found out
		{
			int match = 0;	// an integer used to exit a pattern searching loop once a pattern for the corresponding word is found 
			char pat1[MAX_WORD_LENGTH + 1];	// creating an empty cstring and copying a word from indiWords onto it
			strcpy(pat1,indiWords[j]);
			if (strcmp(wordToCheck,pat1) ==0)	// checks if a word from from the document (pat1) is equal to a word from the pattern array word1(wordToCheck)
												// only words from word1 need to be checked, as once it finds a word from word1 in document, it searches for the second word of the pattern
			{
				int sep = separation[i] + 1;	// takes the seperation value alloted to that pattern
				// cerr << j << endl;
				int lowerPosition = j - sep;	// specifies the positions of words from the array that should be checked, with a lower and upper limit
				// cerr << lowerPosition << endl;
				int higherPosition = j + sep;
				// cerr << higherPosition << endl;
				for (int currentPos = lowerPosition; currentPos <= higherPosition; currentPos++)	// a loop to check the words as close to the first word of the pattern as seperation allows to see if one of them is the other word of the pattern
				{
					if (currentPos < 0)	// if the current position of word to be checked is a negative number, move to the next iteration of the loop to prevent an out-of-bounds error
					{
						continue;
					}

					if (currentPos >= p)	// if the current position is equal to or greater the number of words in the array, break the loop to prevent an out-of-bounds error 
					{
						break;
					}

					if (currentPos == j)	// if the current position is equal to the position of the first word of the pattern found, move to next iteration, as otherwise for patterns with two of the same words, this will register as a match
					{
						continue;
					}

					if (strcmp(word2[i],indiWords[currentPos])==0)	// if the other word of the pattern is found(cstring from word2 and cstring from document are equal), increase rating, set match=1 in order to move to the next pattern, and break the innermost loop
					{
						rating++;
						match = 1;
						// cerr << "It worked" << endl; 
						break;
					}
				}
				if (match == 1)	// if match is equal to 1, this means the pattern has already been found, so we move to the next pattern by breaking out of this middle loop and moving to the next iteration of the outermost loop
				{
					break;
				}
			}
		}
	}
	/*
	for (int i = 0; i < p; i++)
	{
		cerr << indiWords[i] << " ";
	}
	*/


	/* this shall be the future function for rate checks
	for (int i = 0; i < nPatterns; i++)
	{
		for (int j = 0; modDoc[j] != 0; j++)
		{	
			
			;

		}
	}
	*/
	   	
	/*
	for (int i = 0; modDoc[i] != '\0'; i++)
	{
		cerr << modDoc[i];
	}*/
	return rating;	// returns the number of patterns found in the document
	
}


int main()
{
	const int TEST1_NRULES = 3;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot"
	};
	int test1dist[TEST1_NRULES] = {
		-99,           3,          0
	};

	cout << makeProper(test1w1, test1w2, test1dist, 3);


	/*
	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("The mad U4CLA scientist unleashed    a deran5ged robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("**** 2018 ****",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("  That plot: NEFARIOUS!",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("deranged deranged robot deranged robot robot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	cerr << "All tests succeeded" << endl;
	*/
}