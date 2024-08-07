#ifndef DNASEQ_H
#define DNASEQ_H

#include <string>
using namespace std;

enum Nucleotide { A, C, G, T };

class DNAseq
{
public:
	DNAseq();//Default constructor - creates empty sequence
	DNAseq(const string& seq);//Parametric constructor - creat sequence according to given string
	DNAseq(const DNAseq& copy);//Deep copy constructor - creats new object from previously defined object
	~DNAseq();//Destructer

	const bool operator<=(const DNAseq& rhs);//This function checks wheterher left hand-side (lhs) operand is a subsequence	of its right hand - side(rhs) operand.
	const DNAseq operator*(int rhs);//This function checks wheterher left hand-side (lhs) operand is a subsequence of its right hand - side(rhs) operand.
	const DNAseq operator!();//This function is used to take complement of DNA sequence
	const DNAseq& operator=(const DNAseq& rhs);//This function is used to make both rhs and lhs same.
	DNAseq operator+(const DNAseq& rhs);//This function is used to add rhs to lhs
	DNAseq operator-(const DNAseq& rhs);//This function is used to remove occurence of rhs in lhs
	DNAseq operator+=(const DNAseq& rhs); //This function is used to modifies its current lhs DNAseq object by adding(+) the rhs DNAseq object to it.
	//Accessors (getters) functions
	int& getLenght(); //This function is used to get private member
	const Nucleotide getNucleotide(int loc); //This function is used to get private member
	Nucleotide*& getSequence(); //This function is used to get private member
private:
	int length;
	Nucleotide* sequence;
};
//Free functions
int operator % (const DNAseq& lhs, Nucleotide rhs);//This function is used to find number of occurance of rhs in lhs
ostream& operator <<(ostream& os, const DNAseq& rhs);//This function is used to display the content of a DNA sequence
DNAseq operator+(Nucleotide lhs, const DNAseq& rhs);//This function is used to add nucleotid to begining of the sequence

#endif