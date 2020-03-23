﻿#include "pch.h"
#include <iostream>
#include "Cubic_Interpolation_Spline_1D.h"

namespace Com_Methods
{
	//обновить сплайн
	void Cubic_Interpolation_Spline_1D::Update_Spline(const std::vector<Point> &Points, 
		                                              const std::vector<double> &F_Value)
	{
		//обновление списка точек сплайна
		this->Points.clear();
		for (auto & elem : Points) this->Points.push_back(elem);

		//число отрезков разбиения
		int Num_Segment = Points.size() - 1;

		//длина текущего отрезка и следующего
		double h_current, h_next;

		//изменение размеров векторов коэффициентов
		a.resize(Num_Segment);
		b.resize(Num_Segment);
		c.resize(Num_Segment + 1);
		d.resize(Num_Segment);

		//вычисление коэффициентов
		for (int i = 1; i < Num_Segment; i++)
		{
			//длина текущего и следующего отрезков
			h_current = Points[i].x() - Points[i - 1].x();
			h_next = Points[i + 1].x() - Points[i].x();

			//формируем диагональ
			b[i - 1] = 2 * (h_current + h_next);
			//формируем нижнюю диагональ
			a[i] = h_current;
			//формируем верхнюю диагональ
			d[i - 1] = h_next;
			//правая часть
			c[i - 1] = 3.0 * ((F_Value[i + 1] - F_Value[i]) / h_next - (F_Value[i] - F_Value[i - 1]) / h_current);
		}
		
		//метод прогонки: прямой ход
		for (int j = 1; j < Num_Segment - 1; j++)
		{
			b[j] -= a[j] / b[j - 1] * d[j - 1]; //диагональ
			c[j] -= a[j] / b[j - 1] * c[j - 1]; //правая часть
		}

		//метод прогонки: обратный ход
		c[Num_Segment - 2] /= b[Num_Segment - 2];
		for (int j = Num_Segment - 3; j >= 0; j--)
		{
			c[j] = (c[j] - c[j + 1] * d[j]) / b[j];
		}

		//добавляем краевые условия
		c[Num_Segment] = 0.0;
		for (int i = Num_Segment - 1; i > 0; i--) c[i] = c[i - 1];
		c[0] = 0.0;

		for (int i = 0; i < Num_Segment; i++)
		{
			h_current = Points[i + 1].x() - Points[i].x();
			a[i] = F_Value[i];
			b[i] = (F_Value[i + 1] - F_Value[i]) / h_current - (c[i + 1] + 2.0 * c[i]) * h_current / 3.0;
			d[i] = (c[i + 1] - c[i]) / h_current / 3.0;
		}
	}

	//вычислить значение сплайна в точке P
	void Cubic_Interpolation_Spline_1D::Get_Value(const Point &P, double * Res)const
	{
		//машинный ноль
		double eps = 1e-7;
		//число отрезков
		int Num_Segment = Points.size() - 1;
		//поиск отрезка, которому принадлежит точка
		for (int i = 0; i < Num_Segment; i++)
		{
			if (P.x() > Points[i].x() && P.x() < Points[i + 1].x() ||
				fabs(P.x() - Points[i].x()) < eps ||
				fabs(P.x() - Points[i + 1].x()) < eps)
			{
				double diff = (P.x() - Points[i].x());
				Res[0] = a[i] + b[i] * diff + c[i] * pow(diff, 2) + d[i] * pow(diff, 3);
				Res[1] = b[i] + 2.0 * c[i] * diff + 3.0 * d[i] * pow(diff, 2);
				Res[2] = 2.0 * c[i] + 6.0 * d[i] * diff;
				return;
			}
		}
		throw std::exception("The point wasn't found in the segments...");
	}
}

