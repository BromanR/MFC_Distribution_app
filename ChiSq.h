#pragma once

#include <iostream>
#include "Sample.h"
#include "Theor.h"

/// <summary>
/// The ChiSq class, by sample and theoretical distribution, 
/// calculates the statistics of the chi-square test, 
/// the number of degrees of freedom, and the p-value.
/// </summary>

class ChiSq {
private:
	double p_value = -1;
	double stat =-1;
	int* emp_freq= nullptr;
	double* theor_freq = nullptr;
	int df = -1;
	int sample_size = -1;
	int theor_size= -1;
public:
	ChiSq(const Sample& distr, const Theor& theor);
	void calcEmpFreq(const Sample& distr);
	void calcTheorFreq(const Theor& theor);
	void calcStat();
	void calcPvalue();
	void printTheorFreq() const { printf("theor_freq\n"); for (int i = 0; i < theor_size + 1; ++i) { printf("%d %f\n", i, theor_freq[i]); } }
	void printEmpFreq() const { printf("emp_freq\n"); for (int i = 0; i < theor_size + 1; ++i) { printf("%d %d\n", i, emp_freq[i]); } }
	void printStat() const { printf("\n%f\n", stat); }
	void printPvalue() const { printf("\n%f\n", p_value); }
	int* getEmpFreq() const { return emp_freq; }
	double* getTheorFreq() const { return theor_freq; }
	double getPvalue() const { return p_value; }
	~ChiSq() { delete[] emp_freq; delete[] theor_freq; }
};