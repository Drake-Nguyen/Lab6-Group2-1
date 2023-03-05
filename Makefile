.PHONY: help test clean

CXX ?= g++
CXXFLAGS = -std=c++17 -O1 -g

SHELL = bash -eo pipefail

help:
	@echo "Usage:   make [target]"
	@echo "Targets: help, test, clean"

test: *.cpp *.hpp tests/*.cpp
	$(CXX) $(CXXFLAGS) -o tests/tests.out *.cpp tests/tests.cpp
	tests/tests.out |& tee tests/test_results.txt

clean:
	find . -name "*.out" -type f -delete
