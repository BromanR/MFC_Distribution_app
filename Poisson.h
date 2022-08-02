#pragma once
#include "Sample.h"

/// <summary>
/// The Poisson class inherits from the Sample class 
/// and stores the Poisson distribution parameters (model)
/// </summary>

class Poisson :
    public Sample
{
protected:
    /// <summary>
    /// parameter lambda
    /// </summary>
    double lambda = 0;
public:
    Poisson(double lambda, int sample_size) :lambda(lambda) {
        this->sample_size = sample_size;
    }

    ~Poisson() {}
};

