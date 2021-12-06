#!/usr/bin/env python3

import numpy as np
import random
import time
import cmath
from scipy.fftpack import fft
import _fft

from pytest import approx

class TestFFT:
        
    def test_validate(self):
        size_ = [1024, 2048, 4096, 8192, 16384, 32768, 65536]
        with open('performance.txt', 'w') as f: 
            f.write("Performance for FFT improvement\n")
        for i in size_:
            _m1 = np.random.rand(i)
            _m2 = np.random.rand(i)
            comp = _fft.initialize(_m1, _m2)
            py_comp = [complex(_m1[j], _m2[j]) for j in range(i)]
            with open('performance.txt', 'a') as f:
                f.write("\n\nDIT-FFT " + str(i) + " elemets: \n")
            start = time.perf_counter()
            dit = _fft.DIT_FFT_reordered(comp, i)
            dit_time = time.perf_counter() - start
            #_fft.printing(dit, i)
            with open('performance.txt', 'a') as f:
                f.write("Time... " + str(dit_time) + "\n")

                f.write("DIF-FFT " + str(i) + " elemets: \n")
            start = time.perf_counter()
            dif = _fft.DIF_FFT_reordered(comp, i)
            dif_time = time.perf_counter() - start
            #_fft.printing(dif, i)
            with open('performance.txt', 'a') as f:
                f.write("Time... " + str(dif_time) + "\n")
            
            #    f.write("DFT " + str(i) + " elemets: \n")
            #start = time.perf_counter()
            #dft = _fft.DFT(comp, i)
            #dft_time = time.perf_counter() - start
            #_fft.printing(dft, i)
            #with open('performance.txt', 'a') as f:
            #    f.write("Time... " + str(dft_time) + "\n")

            ans = fft(py_comp)
            with open('performance.txt', 'a') as f:
                f.write("\nAns:\n")
                f.write(str(ans))
            
            real = _fft.back_real(dit, i)
            img = _fft.back_img(dit, i)
            for j in range(i):
                assert ans[j].real == approx(real[j], 1e-3)
                assert ans[j].imag == approx(img[j], 1e-3)

            real = _fft.back_real(dif, i)
            img = _fft.back_img(dif, i)
            for j in range(i):
                assert ans[j].real == approx(real[j], 1e-3)
                assert ans[j].imag == approx(img[j], 1e-3)

            #real = _fft.back_real(dft, i)
            #img = _fft.back_img(dft, i)
            #for j in range(i):
            #    assert ans[j].real == approx(real[j], 1e-3)
            #    assert ans[j].imag == approx(img[j], 1e-3)
            """
            for i in range(p):
                for j in range(r):
                    assert np_m[i, j] == approx(ret_naive[i, j])
                    assert np_m[i, j] == approx(ret_tile[i, j])
                    assert np_m[i, j] == approx(ret_mkl[i, j])            
            """

