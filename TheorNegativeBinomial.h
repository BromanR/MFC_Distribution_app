#pragma once
#include "Theor.h"

/// <summary>
/// The TheorNegativeBinomial class inherits from the Theor class 
/// and calculates theoretical probabilities for Negative Binomial distribution
/// </summary>

class TheorNegativeBinomial :
    public Theor
{
public:
    TheorNegativeBinomial(int r, double p);
};

