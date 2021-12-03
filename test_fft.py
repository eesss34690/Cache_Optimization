#!/usr/bin/env python3

import numpy as np
import random
import time
import _fft

from pytest import approx

class TestFFT:
        
    def write_file(self, naive, tile, mkl):
        with open('performance.txt', 'w') as f:
            f.write('naive time: '+ str(naive) + " seconds\n")
            f.write('tile: '+ str(tile) + " seconds\n")
            f.write('mkl: '+ str(mkl) + " seconds\n")
            f.write('tile speeds up compared to naive: '+ str(naive / tile) + " times\n")
            f.write('MKL speeds up compared to naive: '+ str(naive / mkl) + " times\n")

    def test_validate(self):
        size_ = [1024, 2048, 4096, 8192, 16384, 32768, 65536]
        for i in size_:
            _m1 = np.random.rand(i)
            _m2 = np.random.rand(i)
            comp = _fft.initialize(_m1, _m2)

            print("DIT-FFT " + i + " elemets: ")
            start = time.perf_counter()
            dit = _fft.DIT_FFT_reordered(comp, i)
            dit_time = time.perf_counter() - start
            _fft.printing(dit)
            print("Time... " + dit_time)

            print("DIF-FFT " + i + " elemets: ")
            start = time.perf_counter()
            dif = _fft.DIF_FFT_reordered(comp, i)
            dif_time = time.perf_counter() - start
            _fft.printing(dif)
            print("Time... " + dif_time)
            
            print("DFT " + i + " elemets: ")
            start = time.perf_counter()
            dft = _fft.DFT(comp, i)
            dft_time = time.perf_counter() - start
            _fft.printing(dft)
            print("Time... " + dft_time)
            """
            for i in range(p):
                for j in range(r):
                    assert np_m[i, j] == approx(ret_naive[i, j])
                    assert np_m[i, j] == approx(ret_tile[i, j])
                    assert np_m[i, j] == approx(ret_mkl[i, j])            
            """

