#include "neural_network.h"

#include <iostream>

int main()
{
	setlocale(LC_ALL, "rus");
	neural_network nn;
	nn.setSize();
	nn.initializeWeights();
	nn.ChooseFunc();
	nn.learn();
	nn.start();
}
