#include "pch.h"
#include "TheorPoisson.h"

TheorPoisson::TheorPoisson(double lambda) {
	theor_size = MAX_SIZE;
	delete[] probs;
	probs = new double[MAX_SIZE+1]{};
	probs[0] = exp(-lambda);
	for (int i = 1; i < theor_size; ++i) {
		probs[i] = probs[i - 1] * lambda / (i);
	}
}