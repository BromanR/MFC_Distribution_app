#pragma once
#include "Sample.h"

/// <summary>
/// The Geom class inherits from the Sample class 
/// and stores the Geometric distribution parameters (model)
/// </summary>


class Geom :
    public Sample
{
protected:
/// <summary>
///  Parameter of distribution which shows 
///  success probability for one Bernoulli trial
/// </summary>
	double prob;
public:
	Geom(double prob, int sample_size) :prob(prob) {
		this->sample_size = sample_size;
	}
	~Geom() {}
};

