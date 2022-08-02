#include "pch.h"
#include "TheorBinomial.h"

TheorBinomial::TheorBinomial(int n_trials, double p) {
	theor_size = n_trials;
	delete[] probs;
	probs = new double[theor_size+1] {};
	probs[0] = (pow(1 - p, n_trials));
	for (int i = 1; i < theor_size+1; ++i) {
		probs[i] = probs[i - 1] * (double(n_trials) - i + 1) * p / ((double(i)) * (1.0 - p));
	}
}
