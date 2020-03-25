#include "DifGenerate.h"

void Generate::Generate_regularGrid(const double& h,const double& begin, const double& end)
{
	
	for (double i = begin; i < end; i= i+h)
	{
		regularGrid.push_back(Com_Methods::Point(i, 0, 0));
	}
	regularGrid.push_back(Com_Methods::Point(end, 0, 0));
	
}

void Generate::Generate_irregularGrid(const double& h, const double& r, const double& begin, const double& end)
{
	double difH = h;
	irregularGrid.push_back(Com_Methods::Point(begin,0,0));
	for (double i = begin + difH; i <= end; i+=difH )
	{
		irregularGrid.push_back(Com_Methods::Point(i, 0, 0));
		difH *= r;
	}
	irregularGrid.push_back(Com_Methods::Point(end, 0, 0));
}

void Generate::Func_x()
{
	for (int i = 0; i < regularGrid.size(); i++)
	{
		func_regularGrid.push_back(regularGrid[i].x());
	}
	
	for (int i = 0; i < irregularGrid.size(); i++)
	{
		func_irregularGrid.push_back(irregularGrid[i].x());
	}
}

void Generate::Func_x2()
{
	for (int i = 0; i < regularGrid.size(); i++)
	{
		func_regularGrid.push_back(pow(regularGrid[i].x(),2));
	}

	for (int i = 0; i < irregularGrid.size(); i++)
	{
		func_irregularGrid.push_back(pow(irregularGrid[i].x(),2));
	}
}

void Generate::Func_x3()
{
	for (int i = 0; i < regularGrid.size(); i++)
	{
		func_regularGrid.push_back(pow(regularGrid[i].x(), 3));
	}

	for (int i = 0; i < irregularGrid.size(); i++)
	{
		func_irregularGrid.push_back(pow(irregularGrid[i].x(), 3));
	}
}

void Generate::Func_x4()
{
	for (int i = 0; i < regularGrid.size(); i++)
	{
		func_regularGrid.push_back(pow(regularGrid[i].x(), 4));
	}

	for (int i = 0; i < irregularGrid.size(); i++)
	{
		func_irregularGrid.push_back(pow(irregularGrid[i].x(), 4));
	}
}

void Generate::Func_sinx()
{
	for (int i = 0; i < regularGrid.size(); i++)
	{
		func_regularGrid.push_back(sin(regularGrid[i].x()));
	}

	for (int i = 0; i < irregularGrid.size(); i++)
	{
		func_irregularGrid.push_back(sin(irregularGrid[i].x()));
	}
}

void Generate::Func_xsin1000x()
{
	for (int i = 0; i < regularGrid.size(); i++)
	{
		func_regularGrid.push_back(regularGrid[i].x()*sin(1000*regularGrid[i].x()));
	}

	for (int i = 0; i < irregularGrid.size(); i++)
	{
		func_irregularGrid.push_back(irregularGrid[i].x() * sin(1000 * irregularGrid[i].x()));
	}
}