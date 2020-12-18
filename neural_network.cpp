//Автор : Киневич Т.О. группа : 821703
#include "neural_network.h"
#include <thread>
neural_network::neural_network() {
	P = 3;
	M = 4;
	a = 0.0000056;
	Err = 0;
	N = 100000;
	FuncNumber = 0;
	setFunctions();
}

void neural_network::AddFunction(std::vector<double> func) {
	Functions.push_back(func);
}

void neural_network::learn() {
	double count = 0;
	while (count < N) {
		Matrix X, Y, Z, Err;
		double Total = 0;
		std::vector<Matrix> In = toInput(Functions[FuncNumber]);
		std::vector<Matrix> Rez = FuncRez(Functions[FuncNumber]);
		Z = getDefault();
		for (auto i = 0; i < In.size(); i++) {
			Matrix Temp, Temp1,Temp2,Temp3;
			X = In[i].Unic(Z);
			Y = X * firstWeights;
			Activate(Y);
			Z = Y * secondWeights;

			Err = Z - Rez[i];

			Temp = Y.Transposition() * ((Y - 1) * -1);
			Temp1 = Err * secondWeights.Transposition();
			Temp2 = Temp1 * Temp;
			Temp1 = Temp2.Transposition() * X;

			firstWeights = firstWeights - Temp1.Transposition() * a;

			Temp = Y.Transposition() * Err;

			secondWeights = secondWeights - Temp * a;
		}
		for (auto i = 0; i < In.size(); i++) {
			Matrix Temp, Temp1;
			X = In[i].Unic(Z);
			Y = X * firstWeights;
			Z = Y * secondWeights;
			Err = Z - Rez[i];
			Total += Err.square();
		}
		double T = count / N * 100;
		std::cout << T << " % " << std::endl;
		std::cout << Total << std::endl;
		count++;
	}
}

void neural_network::initializeWeights() {

	std::vector<std::vector<double>> Mat;
	for (auto j = 0; j < P + 1; j++) {
		std::vector<double> Weights;
		for (auto i = 0; i < M; i++) {
			Weights.emplace_back((double)(rand()) / RAND_MAX);
		}
		Mat.emplace_back(Weights);
	}
	firstWeights.setData(Mat);
	Mat.clear();
	for (auto j = 0; j < M; j++) {
		std::vector<double> Weights;
		for (auto i = 0; i < 1; i++) {
			Weights.emplace_back((double)(rand()) / RAND_MAX);
		}
		Mat.emplace_back(Weights);
	}
	secondWeights.setData(Mat);
	firstWeights.print();	
	secondWeights.print();
}

void neural_network::start() {
	Matrix X, Y, Z, Err;
/*	for (auto i = 0; i < 4; i++) {
		Functions[FuncNumber].erase(Functions[FuncNumber].begin() + 0);
	}*/
	std::vector<double> d;
	std::vector<Matrix> In;
	In = toInput(Functions[FuncNumber]);
	std::vector<Matrix> Rez;
	Rez = FuncRez(Functions[FuncNumber]);
	Z = getDefault();
	for (auto i = 0; i < In.size(); i++) {
		Matrix Temp, Temp1;
		X = In[i].Unic(Z);
		Y = X * firstWeights;
		Z = Y * secondWeights;
		Z.print();
	}
	std::cout << "Правельные ответы : " << std::endl;
	for (auto i : Rez) {
		i.print();
	}
}

void neural_network::setSize() {
	std::cout << "M : ";
	std::cin >> M;
	std::cout << std::endl;
	std::cout << "P : ";
	std::cin >> P;
	std::cout << std::endl;
}

void neural_network::ChangeFirstWieghts(Matrix x,Matrix delta) {
	firstWeights = firstWeights - x.Transposition() * a * delta;
}

void neural_network::ChangeSecondWeights(Matrix x, Matrix delta) {
	secondWeights = secondWeights - x.Transposition() * a * delta;
}

std::vector<Matrix> neural_network::toInput(std::vector<double> func) {
	std::vector<Matrix> Mat;
	for (auto i = 0; i < M; i++) {
		Matrix TempMat;
		std::vector<std::vector<double>> Temp;
		std::vector<double> fun;
		for (auto k = i; k < i + P; k++) {
			fun.push_back(func[k]);
		}
		Temp.push_back(fun);
		TempMat.setData(Temp);
		Mat.push_back(TempMat);
	}
	return Mat;
}

std::vector<Matrix> neural_network::FuncRez(std::vector<double> func) {
	std::vector<Matrix> Mat;
	for (auto i = 0; i < M; i++) {
		Matrix TempMat;
		std::vector<std::vector<double>> Temp;
		std::vector<double> fun;
		fun.push_back(func[i + P]);
		Temp.push_back(fun);
		TempMat.setData(Temp);
		Mat.push_back(TempMat);
	}
	return Mat;
}

Matrix neural_network::getDefault() {
	Matrix Mat;
	std::vector<std::vector<double>> Temp = {{0}};
	Mat.setData(Temp);
	return Mat;
}

void neural_network::Activate(Matrix& Mat) {
	std::vector<std::vector<double>> Temp;
	Temp = Mat.getData();
	for (auto i = 0; i < Temp.size(); i++)
	{
		for (auto j = 0; j < Temp[i].size(); j++) {
			Temp[i][j] = ((double)1 / ((double)1 + exp(Temp[i][j])));
		}
	}
	Mat.setData(Temp);
}

void neural_network::ChooseFunc() {
	int Temp;
	std::cout << "Выберите функцию : 1 - степеная, 2 - ряд Фибоначчи" << std::endl;
	std::cin >> Temp;
	switch (Temp)
	{
	case 1:
		FuncNumber = 0;
		break;
	case 2:
		FuncNumber = 1;
		break;
	default:
		break;
	}
}

void neural_network::setFunctions() {
	AddFunction({ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 });
	AddFunction({ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233 });
}