#include<iostream>
#include"DNAseq.h"
using namespace std;
/******************************************************************************
Sabanci  University CS204 Advanced Programming Homework4 – Operator Overloading
for DNA sequences
Coded by: Osman Kantarcioglu    -   30891   - Section:B2
Date: 04.04.2024
******************************************************************************/
//Default constructor - creates empty sequence
DNAseq::DNAseq()
{
	length = 0;
	sequence = NULL;
}
//Parametric constructor - creat sequence according to given string
DNAseq::DNAseq(const string& seq)
{
	length = seq.length();
	sequence = new Nucleotide[length];
	//fill sequence 1D array with the elements of the string
	for (int idx = 0; idx < length; idx++)
	{
		//when matching is found in string, add it to sequence
		if (seq[idx] == 'A')
		{
			sequence[idx] = Nucleotide::A;
		}
		else if (seq[idx] == 'C')
		{
			sequence[idx] = Nucleotide::C;
		}
		else if (seq[idx] == 'G')
		{
			sequence[idx] = Nucleotide::G;
		}
		else if (seq[idx] == 'T')
		{
			sequence[idx] = Nucleotide::T;
		}
	}
}

//Deep copy constructor - creats new object from previously defined object
DNAseq::DNAseq(const DNAseq& copy)
{
	length = copy.length;
	if (length == 0)
	{
		sequence = NULL;
	}
	else
	{
		sequence = new Nucleotide[length];
		for (int idx = 0; idx < length; idx++)
		{
			sequence[idx] = copy.sequence[idx];
		}
	}
}

//Destructer
DNAseq::~DNAseq()
{
	length = 0;
	//Deletes all dynamically allocated memory and returns them back to the heap.
	delete[] sequence;
	sequence = NULL;
}
/******************************************************************************
This is given in homework file.
This function checks wheterher left hand-side (lhs) operand is a subsequence
of its right hand-side (rhs) operand.
******************************************************************************/
const bool DNAseq::operator<=(const DNAseq& rhs)
{
	int charPosition = 0;
	while (charPosition <= rhs.length - length)//start from first nucleotid of rhs and goes up until rhs.lenght - lenght because last position that lhs exist in rhs is rhs.lenght - lenght
	{
		bool is_it_subsequence = true;
		bool stop_search = false;
		for (int idx = 0; idx < length && stop_search == false; idx++)
		{
			if (sequence[idx] != rhs.sequence[idx + charPosition])
			{
				is_it_subsequence = false;
				stop_search = true;
			}
		}
		if (is_it_subsequence)
		{
			return true;
		}
		charPosition++;
	}
	return false;
}
/******************************************************************************
This is given in homework file.
This function checks wheterher left hand-side (lhs) operand is a subsequence
of its right hand-side (rhs) operand.
******************************************************************************/
const DNAseq DNAseq::operator*(int rhs)
{
	DNAseq result;
	result.length = length * rhs;		//new lenght of the sequence have been updated
	result.sequence = new Nucleotide[length * rhs];

	int counter = 0;
	while (counter < rhs)//for rhs times
	{
		for (int idx = 0; idx < length; idx++)//elements of the lhs added to sequence
		{
			result.sequence[counter * length + idx] = sequence[idx];
		}
		counter++;
	}
	return result;
}
/******************************************************************************
This is not given in homework file.
This function is used to get private member
******************************************************************************/
int& DNAseq::getLenght()
{
	return length;
}
/******************************************************************************
This is not given in homework file.
This function is used to get private member
******************************************************************************/
const Nucleotide DNAseq::getNucleotide(int loc)
{
	return sequence[loc];
}
/******************************************************************************
This is given in homework file.
This function is used to find number of occurance of rhs in lhs
******************************************************************************/
int operator % (const DNAseq& lhs, Nucleotide rhs)
{
	int counter = 0;
	int currentLocation = 0;

	DNAseq copy = DNAseq(lhs);
	while (currentLocation < copy.getLenght())
	{
		if (copy.getNucleotide(currentLocation) == rhs)
		{
			counter++;
		}
		currentLocation++;
	}
	return counter;
}

/******************************************************************************
This is given in homework file.
This function is used to take complement of DNA sequence
******************************************************************************/
const DNAseq DNAseq::operator!()
{
	DNAseq CompDNA;
	CompDNA.length = length;
	CompDNA.sequence = new Nucleotide[length];


	for (int idx = 0; idx < length; idx++)
	{
		if (sequence[idx] == Nucleotide::A)
		{
			CompDNA.sequence[idx] = Nucleotide::T;
		}
		else if (sequence[idx] == Nucleotide::C)
		{
			CompDNA.sequence[idx] = Nucleotide::G;
		}
		else if (sequence[idx] == Nucleotide::G)
		{
			CompDNA.sequence[idx] = Nucleotide::C;
		}
		else if (sequence[idx] == Nucleotide::T)
		{
			CompDNA.sequence[idx] = Nucleotide::A;
		}
	}
	return CompDNA;
}

/******************************************************************************
This is given in homework file.
I insired from our lecture slides 4.1 (slide 35)
This function is used to make both rhs and lhs same.
******************************************************************************/
const DNAseq& DNAseq::operator=(const DNAseq& rhs)
{
	if (this != &rhs)//If it is not self-assignment
	{
		//delete existing sequence
		delete[] sequence;
		//create new sequence
		length = rhs.length;
		sequence = new Nucleotide[length];

		//add all elements in rhs to lhs
		for (int idx = 0; idx < rhs.length; idx++)
		{
			sequence[idx] = rhs.sequence[idx];
		}
	}
	return *this; //return left hand side
}
/******************************************************************************
This is given in homework file.
This function is used to add rhs to lhs
1) If first nucleotide exists rhs object sequence inserted just after the first
occurrence of this first nucleotide.
2) Else, concatenate the sequence of the rhs after the end of the sequence of
the lhs
******************************************************************************/
DNAseq DNAseq::operator+ (const DNAseq& rhs)
{
	bool exist = false;
	int foundLocation = 0;
	for (int idx = 0; idx < length && exist == false; idx++)
	{
		if (sequence[idx] == rhs.sequence[0])
		{
			exist = true;
			foundLocation = idx;
		}
	}
	DNAseq result;
	result.length = length + rhs.length; //lenght updated
	// if exists
	if (exist)
	{
		result.sequence = new Nucleotide[result.length];
		//copy lhs until first occurance
		for (int idx = 0; idx <= foundLocation; idx++)
		{
			result.sequence[idx] = sequence[idx];
		}
		//copying rhs 
		for (int idx2 = 0; idx2 < rhs.length; idx2++)
		{
			result.sequence[foundLocation + idx2 + 1] = rhs.sequence[idx2];
		}
		//after copying rhs, keep copying remaining lhs
		for (int idx3 = foundLocation + 1; idx3 < length; idx3++)
		{
			result.sequence[rhs.length + idx3] = sequence[idx3];
		}
	}
	//if does not exists
	else
	{
		//creating new sequnce to concatenate
		result.sequence = new Nucleotide[result.length];
		//first adding lhs to new sequence
		for (int idx = 0; idx < length; idx++)
		{
			result.sequence[idx] = sequence[idx];
		}
		//then, add rhs to new sequence
		for (int idx2 = 0; idx2 < rhs.length; idx2++)
		{
			result.sequence[length + idx2] = rhs.sequence[idx2];
		}
	}
	return result;
}

/******************************************************************************
This is NOT given in homework file.
This function is used to get sequence
******************************************************************************/
Nucleotide*& DNAseq::getSequence()
{
	return sequence;
}
/******************************************************************************
This is given in homework file.
This function is used to add nucleotid to begining of the sequence
******************************************************************************/
DNAseq operator+(Nucleotide lhs, const DNAseq& rhs)
{

	DNAseq copy = DNAseq(rhs);
	DNAseq result;

	int length = copy.getLenght() + 1;

	Nucleotide* seq = new Nucleotide[length];
	seq[0] = lhs;
	for (int idx = 0; idx < copy.getLenght(); idx++)
	{
		seq[idx + 1] = copy.getNucleotide(idx);
	}
	result.getSequence() = seq;
	result.getLenght() = length;
	return result;

}

/******************************************************************************
This is given in homework file.
This function is used to remove occurence of rhs in lhs
******************************************************************************/
DNAseq DNAseq::operator-(const DNAseq& rhs)
{
	DNAseq result;
	//I inspired from my previous function operator<= to find occurence 
	int foundPosition = -1;
	int i = 0;
	//start from first nucleotid of rhs and goes up until rhs.lenght - lenght because last position that lhs exist in rhs is rhs.lenght - lenght
	while (i <= length - rhs.length && foundPosition == -1) {
		bool found = true;
		int j = 0;
		bool stop_search = false;
		while (j < rhs.length && stop_search == false) {
			if (sequence[i + j] != rhs.sequence[j]) {
				found = false;
				stop_search = true;
			}
			++j;
		}
		if (found) {
			foundPosition = i;
		}
		++i;
	}
	//up until this part it is very similar to operator<= function
	if (foundPosition != -1) {// if it is found
		result.length = length - rhs.length;
		result.sequence = new Nucleotide[result.length];

		int k = 0;
		//add elements before rhs
		while (k < foundPosition) {
			result.sequence[k] = sequence[k];
			++k;
		}
		// add elements after rhs
		int l = foundPosition + rhs.length;
		while (l < length) {
			result.sequence[k] = sequence[l];
			++k;
			++l;
		}
	}
	else {
		//if rhs do not exist in lhs, copy only elments of lhs
		result.length = length;
		result.sequence = new Nucleotide[result.length];
		int m = 0;
		while (m < length) {
			result.sequence[m] = sequence[m];
			++m;
		}
	}

	return result;
}

/******************************************************************************
This is given in homework file.
This function is used to modifies its current lhs DNAseq object by adding (+)
the rhs DNAseq object to it.
******************************************************************************/
DNAseq DNAseq::operator+=(const DNAseq& rhs)
{
	*this = *this + rhs;

	return *this;
}
/******************************************************************************
This is given in homework file.
This function is used to display the content of a DNA sequence
******************************************************************************/
ostream& operator<<(ostream& os, const DNAseq& rhs)
{
	DNAseq copy = DNAseq(rhs);
	for (int idx = 0; idx < copy.getLenght(); idx++)
	{
		Nucleotide nuc = copy.getNucleotide(idx);
		if (nuc == A)
		{
			os << 'A';
		}
		else if (nuc == C)
		{
			os << 'C';
		}
		else if (nuc == G)
		{
			os << 'G';
		}
		else if (nuc == T)
		{
			os << 'T';
		}
	}
	return os;
}