#include "pch.h"
#include "Sample.h"
#include "R32M.h"


void Sample::generateSample(Theor* pTheor) {
	double* cum_sum = new double[pTheor->getTheorSize()+1]{};
	double* probs = pTheor->getProbs();
	cum_sum[0] = probs[0];
	for (int i = 1; i < pTheor->getTheorSize()+1; ++i) {
		cum_sum[i] =cum_sum[i-1]+probs[i];
	}
	delete[] sample;
	sample = new int[sample_size];
	for (int j = 0; j < sample_size; ++j) {
		int k = 0;
		double a = rnunif();
		while (a>cum_sum[k]) {
			++k;
		}
		sample[j] = k;
	}
	delete[] cum_sum;
}
