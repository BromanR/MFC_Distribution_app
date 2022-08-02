#pragma once
#include <iostream>
const int MAX_SIZE = 100;
/// <summary>
/// The Theor class stores the theoretical probabilities.
/// </summary>
class Theor
{
protected:
/// <summary>
/// Theoretical probabilities
/// </summary>
	double* probs=nullptr;
/// <summary>
/// size of theoretical probabilities
/// </summary>
	int theor_size = 0;
public:
	~Theor(){ delete[] probs; }
	void print() { for (int i = 0; i < MAX_SIZE; ++i) { printf("%f\n",probs[i]); } }
	int getTheorSize() const { return theor_size; }
	double* getProbs() const { return probs; }
	double& operator[](const int index) const { return probs[index]; }
};

