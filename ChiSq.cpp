#include "pch.h"
#include "ChiSq.h"
#include "PROBDIST.h"

ChiSq::ChiSq(const Sample& distr, const Theor& theor):
	theor_size(theor.getTheorSize()), sample_size(distr.getSampleSize())
{
	calcEmpFreq(distr);
	calcTheorFreq(theor);
}


void ChiSq::calcEmpFreq(const Sample& distr) {
	emp_freq = new int[theor_size + 1]{};
	for (int i = 0; i < sample_size; ++i) {
		++emp_freq[distr[i]];
	}
}


void ChiSq::calcTheorFreq(const Theor& theor) {
	theor_freq = new double[theor_size + 1];
	for (int i = 0; i < theor_size+1; ++i) {
		theor_freq[i] = theor[i] * sample_size;
	}
}




void ChiSq::calcStat() {
	int* merged_emp_freq = new int[theor_size + 1]{};
	double* merged_theor_freq = new double[theor_size + 1]{};
	int j = 0;
	for (int i = 0; i < theor_size + 1; ++i, ++j) {
		for (merged_emp_freq[j] = 0, merged_theor_freq[j] = 0; i < theor_size + 1 && merged_theor_freq[j] < 5; ++i) {
			merged_emp_freq[j] += emp_freq[i];
			merged_theor_freq[j] += theor_freq[i];
		}
		if (merged_theor_freq[j] < 5) {
			merged_emp_freq[j - 1] += merged_emp_freq[j];
			merged_theor_freq[j - 1] += merged_theor_freq[j];
			--j;
		}
		--i;
	}
	df = j;

	stat = 0;
	for (int i = 0; i < df; ++i) {
		stat += pow(merged_emp_freq[i] - merged_theor_freq[i], 2) / merged_theor_freq[i];
	}
	delete[] merged_emp_freq;
	delete[] merged_theor_freq;
}

void ChiSq::calcPvalue() {
	if (stat < 0) {
		calcStat();
	}
	p_value = 1 - pChi(stat, df - 1);
}
