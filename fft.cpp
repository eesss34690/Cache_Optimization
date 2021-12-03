# include "complex.h"	// definition of struct complex, Calculation of WN[]
# include "dft.h"		// DFT
# include "dit_fft.h"	// DIT-FFT
# include "dif_fft.h"	// DIF-FFT

PYBIND11_MODULE(_fft, m) {
  m.def("DFT", &DFT);
  m.def("DIT_FFT_reordered", &DIT_FFT_reordered);
  m.def("DIF_FFT_reordered", &DIF_FFT_reordered);
}

/*
int main(int argc, char ** argv) 
{
	// Get argv
		int N_max = atoi(argv[1]); // length of input sequence
			// input 7 to run 2^{10,11,12,13,14,15,16}
			// input 6 to run 2^{10,11,12,13,14,15}
		int validate_or_evaluate = atoi(argv[2]); // 1 for validate, 0 for ignore
		int dft_dit_dif = atoi(argv[3]); // 1:DFT, 2:DIT, 3:DIF, 4:To compute everything for validation

	// Initialize
	// Setup input sequence
		complex* input_seq = new complex[N_max];
		input_seq[0] = complex(1,0);
		input_seq[1] = complex(1,0);

	// For validation of the result
		if (validate_or_evaluate == 1) {
			validate_result(input_seq, N_max, dft_dit_dif);
			return 0;
		}

	// For compare the performance(run time) of DFT/DIT/DIF
		else if (validate_or_evaluate == 0) {
			evaluate_performance(input_seq, N_max, dft_dit_dif);
			return 0;
		}

	// end
	    return 0;

}
*/