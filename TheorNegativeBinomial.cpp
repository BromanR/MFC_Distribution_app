#include "pch.h"
#include "TheorNegativeBinomial.h"

TheorNegativeBinomial::TheorNegativeBinomial(int r, double p) {
	theor_size = MAX_SIZE;
	delete[] probs;
	probs = new double[MAX_SIZE+1] {};
	probs[0] = pow(p, r);
	for (int i = 1; i < theor_size; ++i) {
		probs[i] = probs[i - 1] * (i-1 + r) * (1 - p) / (i);
	}
}