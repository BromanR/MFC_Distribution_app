#pragma once
#include "Theor.h"

/// <summary>
/// The TheorBinomial class inherits from the Theor class 
/// and calculates theoretical probabilities for Binomial distribution
/// </summary>

class TheorBinomial :
    public Theor
{
protected:

public:
	TheorBinomial(int n_trials, double p);
};

