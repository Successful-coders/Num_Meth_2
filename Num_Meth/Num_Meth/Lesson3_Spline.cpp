﻿#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "Point.h"
#include "Spline.h"
#include "Cubic_Interpolation_Spline_1D.h"
#include "Smoothing_Spline_1D.h"
#include "DifGenerate.h"

enum FUNCTION_TYPE { x, x2, x3, x4, sinx, xsin1000x};

void CreateSplineTable(double a, double b, double h, FUNCTION_TYPE functionType, std::vector<Com_Methods::Point> &splinePoints, std::vector<std::vector<double>> &splineValues, bool isPrintTable)//isPrintTable - отображать или нет таблицу
{
	Generate gen;
	gen.Generate_regularGrid(h, a, b);

	switch (functionType)
	{
		case x: gen.Func_x();
			break;
		case x2: gen.Func_x2();
			break;
		case x3: gen.Func_x3();
			break;
		case x4: gen.Func_x4();
			break;
		case sinx: gen.Func_sinx();
			break;
		case xsin1000x: gen.Func_xsin1000x();
			break;
	}
	

	std::vector<Com_Methods::Point> testPoints;
	//точки для тестовой таблицы
	for (double i = a + (h / 2); i < b; i += h)
	{
		Com_Methods::Point point(i, 0.0, 0.0);
		testPoints.push_back(point);
	}

	//для хранения результата
	std::vector<std::vector<double>> testValues(testPoints.size());
	for (int i = 0; i < testPoints.size(); i++)
	{
		testValues[i].resize(3);
	}

	//кубический интерполяционный сплайн
	Com_Methods::Cubic_Interpolation_Spline_1D Sp1;
	//построение сплайна
	Sp1.Update_Spline(gen.regularGrid, gen.func_regularGrid);

	//значение сплайна в точках
	for (int i = 0; i < testPoints.size(); i++)
	{
		Sp1.Get_Value(testPoints[i], &(testValues[i][0]));
	}

	std::cout << "\n\nCubic Interpolation Spline:\n";
	if (isPrintTable)
	{
		for (int i = 0; i < testPoints.size(); i++)
		{
			std::cout << std::left << std::setw(20) << "x"
				<< std::setw(20) << "P(x)"
				<< std::setw(20) << "P'(x)"
				<< std::setw(20) << "P''(x)" << "\n";
			std::cout << std::left << std::setw(20) << testPoints[i].x()
				<< std::setw(20) << testValues[i][0]
				<< std::setw(20) << testValues[i][1]
				<< std::setw(20) << testValues[i][2] << "\n";
		}
		//сглаживающий сплайн
		Com_Methods::Smoothing_Spline_1D Sp2(0.0);
		//построение сплайна
		Sp2.Update_Spline(gen.regularGrid, gen.func_regularGrid);
		//значение сплайна в точках
		for (int i = 0; i < testPoints.size(); i++)
		{
			Sp2.Get_Value(testPoints[i], &(testValues[i][0]));
		}

		std::cout << "\n\nSmoothing Spline:\n";
		for (int i = 0; i < testPoints.size(); i++)
		{
			std::cout << std::left << std::setw(20) << "x"
				<< std::setw(20) << "P(x)"
				<< std::setw(20) << "P'(x)" << "\n";
			std::cout << std::left << std::setw(20) << testPoints[i].x()
				<< std::setw(20) << testValues[i][0]
				<< std::setw(20) << testValues[i][1] << "\n";
		}
	}

	splinePoints = testPoints;
	splineValues = testValues;


}

void FindNorm(FUNCTION_TYPE functionType, std::vector<Com_Methods::Point> splinePoints, std::vector<std::vector<double>> splineValues, double approxError[3])
{
	double max = 0;
	double maxOfDerivative1 = 0;
	double maxOfDerivative2 = 0;

	switch (functionType)
	{
	case x:
	{
		for (int i = 0; i < splinePoints.size(); i++)
		{
			double diff = abs(splineValues[i][0] - splinePoints[i].x());
			double diffOfDerivative1 = abs(splineValues[i][1] - 1);
			double diffOfDerivative2 = abs(splineValues[i][2]);

			if (diff > max)
			{
				max = diff;
			}
			if (diffOfDerivative1 > maxOfDerivative1)
			{
				maxOfDerivative1 = diffOfDerivative1;
			}
			if (diffOfDerivative2 > maxOfDerivative2)
			{
				maxOfDerivative2 = diffOfDerivative2;
			}
		}
	}
		break;
	case x2:
	{
		for (int i = 0; i < splinePoints.size(); i++)
		{
			double diff = abs(splineValues[i][0] - (splinePoints[i].x()  * splinePoints[i].x()));
			double diffOfDerivative1 = abs(splineValues[i][1] - (2 * splinePoints[i].x()));
			double diffOfDerivative2 = abs(splineValues[i][2] - 2);

			if (diff > max)
			{
				max = diff;
			}
			if (diffOfDerivative1 > maxOfDerivative1)
			{
				maxOfDerivative1 = diffOfDerivative1;
			}
			if (diffOfDerivative2 > maxOfDerivative2)
			{
				maxOfDerivative2 = diffOfDerivative2;
			}
		}
	}
		break;
	case x3:
	{
		for (int i = 0; i < splinePoints.size(); i++)
		{
			double diff = abs(splineValues[i][0] - (splinePoints[i].x() * splinePoints[i].x() * splinePoints[i].x()));
			double diffOfDerivative1 = abs(splineValues[i][1] - (3 * splinePoints[i].x() * splinePoints[i].x()));
			double diffOfDerivative2 = abs(splineValues[i][2] - (6 * splinePoints[i].x()));

			if (diff > max)
			{
				max = diff;
			}
			if (diffOfDerivative1 > maxOfDerivative1)
			{
				maxOfDerivative1 = diffOfDerivative1;
			}
			if (diffOfDerivative2 > maxOfDerivative2)
			{
				maxOfDerivative2 = diffOfDerivative2;
			}
		}
	}
		break;
	case x4:
	{
		for (int i = 0; i < splinePoints.size(); i++)
		{
			double diff = abs(splineValues[i][0] - (splinePoints[i].x() * splinePoints[i].x() * splinePoints[i].x() * splinePoints[i].x()));
			double diffOfDerivative1 = abs(splineValues[i][1] - (4 * splinePoints[i].x() * splinePoints[i].x() * splinePoints[i].x()));
			double diffOfDerivative2 = abs(splineValues[i][2] - (12 * splinePoints[i].x() * splinePoints[i].x()));

			if (diff > max)
			{
				max = diff;
			}
			if (diffOfDerivative1 > maxOfDerivative1)
			{
				maxOfDerivative1 = diffOfDerivative1;
			}
			if (diffOfDerivative2 > maxOfDerivative2)
			{
				maxOfDerivative2 = diffOfDerivative2;
			}
		}
	}
		break;
	case sinx:
	{
		for (int i = 0; i < splinePoints.size(); i++)
		{
			double diff = abs(splineValues[i][0] - sin(splinePoints[i].x()));			
			double diffOfDerivative1 = abs(splineValues[i][1] - cos(splinePoints[i].x()));
			double diffOfDerivative2 = abs(splineValues[i][2] + sin(splinePoints[i].x()));

			if (diff > max)
			{
				max = diff;
			}
			if (diffOfDerivative1 > maxOfDerivative1)
			{
				maxOfDerivative1 = diffOfDerivative1;
			}
			if (diffOfDerivative2 > maxOfDerivative2)
			{
				maxOfDerivative2 = diffOfDerivative2;
			}
		}
	}
		break;
	}


	double result[3] = { max, maxOfDerivative1, maxOfDerivative2};
	approxError[0] = max;
	approxError[1] = maxOfDerivative1;
	approxError[2] = maxOfDerivative2;
}

int main()
{
	try
	{
		std::vector<Com_Methods::Point> splinePoints;
		std::vector<std::vector<double>> splineValues;
		double approxError[3];
		double h = 0.1;
		FUNCTION_TYPE func = x;
		std::cout << "Analytical function: " << "x" << "\n";
		std::cout << "\n\h = " << h << "\n";
		CreateSplineTable(0.0, 2.0, h, func, splinePoints, splineValues, false);
		FindNorm(func, splinePoints, splineValues, approxError);

		std::cout << "Approximation error of function: " << approxError[0] << "\n"
			<< "Approximation error of derivative 1 : " << approxError[1] << "\n"
			<< "Approximation error of derivative 2 : " << approxError[2] << "\n";

		h /= 2;
		std::cout << "\n\h = " << h << "\n";
		CreateSplineTable(0, 2.0, h, func, splinePoints, splineValues, false);
		FindNorm(func, splinePoints, splineValues, approxError);

		std::cout << "Approximation error of function: " << approxError[0] << "\n"
			<< "Approximation error of derivative 1 : " << approxError[1] << "\n"
			<< "Approximation error of derivative 2 : " << approxError[2] << "\n";

		h /= 2;
		std::cout << "\n\h = " << h << "\n";
		CreateSplineTable(0, 2.0, h, func, splinePoints, splineValues, false);
		FindNorm(func, splinePoints, splineValues, approxError);

		std::cout << "Approximation error of function: " << approxError[0] << "\n"
			<< "Approximation error of derivative 1 : " << approxError[1] << "\n"
			<< "Approximation error of derivative 2 : " << approxError[2] << "\n";
	}
	catch (std::exception & Ex)
	{
		std::cout << "Error: " << Ex.what() << std::endl;
	}
}