#pragma once
#include "Sample.h"

/// <summary>
/// The Binomial class inherits from the Sample class 
/// and stores the Binomial distribution parameters (model)
/// </summary>

class Binomial: public Sample {
protected:
	/// <summary>
	/// Number of trials
	/// </summary>
	int n_trials=0;
	/// <summary>
	///  Success probability for each trial
	/// </summary>
	double prob=0;
public:
	Binomial(int n_trials, double prob, int sample_size):prob(prob), n_trials(n_trials) {
		this->sample_size = sample_size;
	}
	~Binomial() {}
};