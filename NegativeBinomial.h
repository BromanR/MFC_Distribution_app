#pragma once
#include "Sample.h"

/// <summary>
/// The NegativeBinomial class inherits from the Sample class 
/// and stores the Negative Binomial distribution parameters (model)
/// </summary>

class NegativeBinomial :
    public Sample
{
protected:
	/// <summary>
	/// Success probability
	/// </summary>
	double p=0;
	/// <summary>
	/// Number of success
	/// </summary>
	int r=0;
public:
	NegativeBinomial(int r, double p, int sample_size) :p(p), r(r) {
		this->sample_size = sample_size;
	}
	~NegativeBinomial() {}
};

