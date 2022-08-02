#include "pch.h"
#include "TheorGeom.h"

TheorGeom::TheorGeom(double p) {
	theor_size = MAX_SIZE;
	delete[] probs;
	probs = new double[MAX_SIZE+1];
	probs[0] = p;
	for (int i = 1; i < MAX_SIZE+1; ++i) {
		probs[i] = probs[i - 1] * (1 - p);
	}
}