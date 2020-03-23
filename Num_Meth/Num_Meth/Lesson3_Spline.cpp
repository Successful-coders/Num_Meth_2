#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "Point.h"
#include "Spline.h"
#include "Cubic_Interpolation_Spline_1D.h"
#include "Smoothing_Spline_1D.h"
#include "DifGenerate.h"

int main()
{
	try
	{
		Generate gen;
		gen.Generate_regularGrid(0.5, 2, 4);
		gen.Generate_irregularGrid(0.5,  2, 2, 4);
		gen.Func_sinx();
		////регулярная равномерная сетка
		//std::vector<Com_Methods::Point> Mesh = { Com_Methods::Point(0.0, 0.0, 0.0),
		//										 Com_Methods::Point(1.0, 0.0, 0.0), 
		//										 Com_Methods::Point(2.0, 0.0, 0.0) };
		////значения табличной функции f(x) = x
		//std::vector<double> Func = { 0.0, 1.0, 2.0 };

		//точка для теста
		Com_Methods::Point Test_Point(2.23, 0.0, 0.0);
		//для хранения результата
		std::vector<double> Res(3);

		//кубический интерполяционный сплайн
		Com_Methods::Cubic_Interpolation_Spline_1D Sp1;
		//построение сплайна
		Sp1.Update_Spline(gen.regularGrid, gen.func_regularGrid);
		//значение сплайна в точке
		Sp1.Get_Value(Test_Point, &Res[0]);
		std::cout << "\nCubic Interpolation Spline:\n";
		std::cout << std::left << std::setw(20) << "x" 
							   << std::setw(20) << "P(x)" 
							   << std::setw(20) << "P'(x)"
							   << std::setw(20) << "P''(x)" << "\n";
		std::cout << std::left << std::setw(20) << Test_Point.x() 
							   << std::setw(20) << Res[0] 
							   << std::setw(20) << Res[1] 
							   << std::setw(20) << Res[2] << "\n";

		//сглаживающий сплайн
		Com_Methods::Smoothing_Spline_1D Sp2 (0.0);
		//построение сплайна
		Sp2.Update_Spline(gen.regularGrid, gen.func_regularGrid);
		//значение сплайна в точке
		Sp2.Get_Value(Test_Point, &Res[0]);
		std::cout << "\nSmoothing Spline:\n";
		std::cout << std::left << std::setw(20) << "x" 
							   << std::setw(20) << "P(x)" 
							   << std::setw(20) << "P'(x)" << "\n";
		std::cout << std::left << std::setw(20) << Test_Point.x() 
							   << std::setw(20) << Res[0] 
							   << std::setw(20) << Res[1] << "\n";

	}
	catch (std::exception &Ex)
	{
		std::cout << "Error: " << Ex.what() << std::endl;
	}
}