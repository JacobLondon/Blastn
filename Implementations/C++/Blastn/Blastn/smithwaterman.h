#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include <string.h>

#define MATCH 2
#define MISMATCH -1
#define GAP -1

#define DIAG 1
#define UP 2
#define LEFT 3

int* zeros(int);
int max(int, int, int);
void append(char*, char);

int match(char, char);
void water(char*, char*, int);

// initialize an array with zeros of given size
int* zeros(int size)
{
	int* mat = new int[size];
	int i;
	for (i = 0; i < size; i++)
		mat[i] = 0;
	return mat;
}

// get max between three integers
int max(int val1, int val2, int val3)
{
	int max = 0;

	if (val1 > max)
		max = val1;
	if (val2 > max)
		max = val2;
	if (val3 > max)
		max = val3;

	return max;
}

void append(char* str, char c)
{
	int len = strlen(str);
	str[len] = c;
	str[len + 1] = '\0';
}

int match(char a, char b)
{
	if (a == b)
		return MATCH;
	else if (a == '-' || b == '-')
		return GAP;
	else
		return MISMATCH;
}

void water(char* seqA, char* seqB, int length)
{
	// strings to put gaps in
	char* alignA = new char[length];
	char* alignB = new char[length];
	char charA, charB;

	// matrices are 1 larger in each direction
	length++;
	int size = length * 2;
	int* scoreMat = zeros(size);
	int* pointMat = zeros(size);
	
	// scoring
	int i, j;
	int maxScore = 0;
	int max_i = 1, max_j = 1;
	int diag, up, left;
	int tindex;

	// traverse score matrix and calculate scores
	for (i = 1; i < length; i++)
		for (j = 1; j < length; j++)
		{
			// hold the index so it doesn't need to be recalculated
			tindex = i * length + j;

			// get max point at each index
			diag = scoreMat[(i - 1) * length + (j - 1)] + match(seqA[i - 1], seqB[j - 1]);
			up   = scoreMat[i * length + (j - 1)] + GAP;
			left = scoreMat[(i - 1) * length + j] + GAP;
			scoreMat[tindex] = max(diag, up, left);

			// record the direction in the point matrix
			if (scoreMat[tindex] == 0)
				pointMat[tindex] = 0;
			if (scoreMat[tindex] == diag)
				pointMat[tindex] = DIAG;
			if (scoreMat[tindex] == up)
				pointMat[tindex] = UP;
			if (scoreMat[tindex] == left)
				pointMat[tindex] = LEFT;
							
			// record max index and value
			if (scoreMat[tindex] >= maxScore)
			{
				max_i = i;
				max_j = j;
				maxScore = scoreMat[tindex];
			}
		}

	// traceback
	i = max_i;
	j = max_j;

	while (pointMat[i * length + j] != 0)
	{
		switch (pointMat[i * length + j])
		{
		case DIAG:
			charA = seqA[--i];
			charB = seqB[--j];
			break;
		case UP:
			charA = '-';
			charB = seqB[--j];
			break;
		case LEFT:
			charA = seqA[--i];
			charB = '-';
			break;
		}

		append(alignA, charA);
		append(alignB, charB);
	}

	// reverse order of alignA/B
	// TODO

	delete scoreMat, pointMat;
	delete alignA, alignB;
}

#endif // SMITHWATERMAN_H