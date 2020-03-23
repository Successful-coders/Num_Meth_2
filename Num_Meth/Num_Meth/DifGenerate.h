#pragma once
#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "Point.h"

//Funcrion Code:
//1: x
//2: x^2
//3: x^3
//4: x^4
//5: sin(x)
class Generate
{
public:
	//���������� � ���������� �������� ���������
	std::vector<Com_Methods::Point> regularGrid;
	std::vector<Com_Methods::Point> irregularGrid;
	// �������� ������� ��� ���������� � ���������� �������� ���������
	std::vector<double> func_regularGrid;
	std::vector<double> func_irregularGrid;

	void Generate_regularGrid(const double &h,  const double& begin, const double& end);
	void Generate_irregularGrid(const double &h, const double&r, const double&begin, const double&end);
	// ���������� �������� �������
	void Func_x();
	void Func_x2();
	void Func_x3();
	void Func_x4();
	void Func_sinx();
};