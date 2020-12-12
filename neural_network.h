#pragma once
//#include "Neuron.h"
#include "Matrix.h"
#include <iostream>

class neural_network
{
private:
	std::vector<std::vector<double>> Functions;
	Matrix firstWeights;
	Matrix secondWeights;
	int P;
	int M;
	double a;
	double N;
	double Err;
	int FuncNumber;
public:
	neural_network();
	void AddFunction(std::vector<double>);
	void setSize();
	void initializeWeights();
	void learn();
	void start();
	void ChangeFirstWieghts(Matrix, Matrix);
	void ChangeSecondWeights(Matrix, Matrix);
	std::vector<Matrix> toInput(std::vector<double>);
	std::vector<Matrix> FuncRez(std::vector<double>);
	Matrix getDefault();
	void ChooseFunc();
};

