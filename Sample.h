#pragma once
#include <iostream>
#include "Theor.h"

/// <summary>
/// The abstract base class Sample
/// </summary>

class Sample {
protected:
	/// <summary>
	/// Sample
	/// </summary>
	int* sample = nullptr;
	/// <summary>
	/// Sample size
	/// </summary>
	int sample_size = 0;
public:
/// <summary>
/// Clear virtual function that takes as input 
/// a pointer to theoretical distribution. With theoretical probabilities 
/// the cumulative sum will calculate and then sample will be simulated
/// 
/// </summary>
	void generateSample(Theor* pTheor);
	virtual ~Sample() {
		delete[] sample;
	};
	void printSample() {
		for (int i = 0; i < sample_size; ++i) { printf("%d\n", sample[i]); }
	}
	int getSampleSize() const { return sample_size; }
	int* getSample() const { return sample; }
	int& operator[](const int index) const { return sample[index]; }
};