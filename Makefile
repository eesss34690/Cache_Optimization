CXX = g++

FPIC = `python3 -m pybind11 --includes`
INCLUDE = `python3-config --includes`
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -ldl -lpthread -lm $(INCLUDE)

SOFILE = _fft${shell python3-config --extension-suffix}

.PHONY: all
all: ${SOFILE}

${SOFILE}: fft.cpp
	${CXX} ${FPIC} $< -o $@ ${CXXFLAGS}

test: ${SOFILE}
	python -m pytest test_fft.py

clean:
	rm -rf *.so __pycache__ .pytest_cache performance.txt
