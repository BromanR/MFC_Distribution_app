#pragma once
#include "Theor.h"

/// <summary>
/// The TheorPoisson class inherits from the Theor class 
/// and calculates theoretical probabilities for Poisson distribution
/// </summary>

class TheorPoisson :
    public Theor
{
public:
    TheorPoisson(double lambda);
};

