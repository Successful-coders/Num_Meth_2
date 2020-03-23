﻿#pragma once

namespace Com_Methods
{
	//точка
	class Point
	{
	private:
		//координаты
		double X, Y, Z;
	public:
		//конструктор
		Point(double x, double y, double z);
		//доступ к полям
		double x()const;
		double y()const;
		double z()const;
	};
}

