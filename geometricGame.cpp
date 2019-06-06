#include "UI.hpp"
#include<iostream>
#include<math.h>
bool isRayCrossCircleAndFindCrossPoint(double x1, double y1, double x2, double y2,
	double radius, double x0, double y0, double& crossX, double& crossY)
{
	double A = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
	double B = (x2 - x1)*(x1 - x0) + (y2 - y1)*(y1 - y0);
	double C = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0) - (radius*radius);
	double discriminant = B*B - A*C;
	if (discriminant < 0)
	{
		return false;
	}
	else if (discriminant == 0)
	{
		double lamda12 = -B / A;
		crossX = x1 + ((lamda12))*(x2 - x1);
		crossY = y1 + ((lamda12))*(y2 - y1);
		if (lamda12 >= 0)
		{
			return true;
		}
		//?
		return false;
	}
	 else // (discriminant > 0)
	{
		double lamda1 = (-B - sqrt(discriminant)) / A;
		double lamda2 = (-B + sqrt(discriminant)) / A;
		if (lamda1 < 0 && lamda2 < 0)
			return false;
		else if ((lamda1 < 0 && lamda2>0))
		{
			crossX = x1 + ((lamda2))*(x2 - x1);
			crossY = y1 + ((lamda2))*(y2 - y1);
			return true;
		}
		else if (lamda2 < 0 && lamda1>0)
		{
			crossX = x1 + ((lamda1))*(x2 - x1);
			crossY = y1 + ((lamda1))*(y2 - y1);
			return true;
		}
		else// (lamda1 > 0 && lamda2 > 0)
		{
			crossX = x1 + ((lamda1))*(x2 - x1);
			crossY = y1 + ((lamda1))*(y2 - y1);
			return true;
		}
	}
}
double CalcDet(double c1, double c2, double c3, double c4)
{
	return ((c1*c4) - (c2*c3));
}
bool iSRayCrossMirrorAndFindCrossPoint(double x1, double y1, double x2, double y2,
	double a1, double b1, double a2, double b2, double & crossPx, double & crossPy,
	double &crossPpX, double &crossPpY, double& crossPpGx, double &crossPpGy)
{
	double det = CalcDet(x2 - x1, a1 - a2, y2 - y1, b1 - b2);
	if (det == 0)
	{
		return false;
	}
	else //(det != 0)
	{
		double det1 = CalcDet(a1 - x1, a1 - a2, b1 - y1, b1 - b2);
		double lamda = det1 / det;
		if (lamda < 0)
		{
			return false;
		}
		else //(lamda >= 0)
		{
			double det2 = CalcDet(x2 - x1, a1 - x1, y2 - y1, b1 - y1);
			double mu = det2 / det;
			if (mu < 0 || mu > 1)
			{
				return false;
			}
			else//mu >= 0 && mu <= 1
			{
				crossPx = x1 + lamda*(x2 - x1);
				crossPy = y1 + lamda*(y2 - y1);
				double det = CalcDet(b1 - b2, a1 - a2, a2 - a1, b1 - b2);//!=0 always
				double det1 = CalcDet(x1 - crossPx, a1 - a2, y1 - crossPy, b1 - b2);
				crossPpX = crossPx + (det1 / det)*(b1 - b2);
				crossPpY = crossPy + (det1 / det)*(a2 - a1);
				crossPpGx = (2 * crossPpX) - x1;
				crossPpGy = (2 * crossPpY) - y1;
				return true;
			}
		}
	}
}
int main()
{
    double input[1000];
    
	GetInput(input);
	double x0 = input[2];
	double y0 = input[3];
	double radius = input[4];
	double fromX = input[5];
	double fromY = input[6];
	double toX = input[7];
	double toY = input[8];
	double crossX=0;
	double crossY=0;
	double crossPxMirr = 0;
	double crossPyMirr = 0;
	double crossPpX = 0;
	double crossPpY = 0;
	double crossPpGx = 0;
	double crossPpGy = 0;
	if (fromX == toX && fromY == toY)
	{
		std::cout << "ERROR\n";
		return 1;
	}
	for (int i = 1; i <=int(input[9]); i++)
	{
		bool rayCrossMirror = false;
		for (int i = 0; i <= 36 && !(rayCrossMirror); i += 4)
		{
			if (iSRayCrossMirrorAndFindCrossPoint(fromX, fromY, toX, toY,
				input[11 + i], input[11 + i + 1], input[11 + i + 2], input[11 + i + 3], crossPxMirr, crossPyMirr, crossPpX, crossPpY, crossPpGx, crossPpGy))
			{
				SetRaySegment(toX, toY, crossPxMirr, crossPyMirr);
				SetRaySegment(crossPxMirr, crossPyMirr, crossPpGx, crossPpGy);
				rayCrossMirror = true;
				
			}
		}
		if (!rayCrossMirror)
		{
			if (isRayCrossCircleAndFindCrossPoint(fromX, fromY, toX, toY, radius, x0, y0, crossX, crossY)) {
				SetRaySegment(fromX, fromY, crossX, crossY);
				std::cout << "Win\n";
				return 0;
			}
			else
			{
				if (iSRayCrossMirrorAndFindCrossPoint(fromX, fromY, toX, toY, 0, 0, input[0], 0,
					crossPxMirr, crossPyMirr, crossPpX, crossPpY, crossPpGx, crossPpGy)
					|| iSRayCrossMirrorAndFindCrossPoint(fromX, fromY, toX, toY, 0, 0, 0, input[1],
						crossPxMirr, crossPyMirr, crossPpX, crossPpY, crossPpGx, crossPpGy)
					|| iSRayCrossMirrorAndFindCrossPoint(fromX, fromY, toX, toY, 0, input[1], input[0], input[1],
						crossPxMirr, crossPyMirr, crossPpX, crossPpY, crossPpGx, crossPpGy)
					|| iSRayCrossMirrorAndFindCrossPoint(fromX, fromY, toX, toY, input[0], 0, input[0], input[1],
						crossPxMirr, crossPyMirr, crossPpX, crossPpY, crossPpGx, crossPpGy))
				{
					SetRaySegment(toX, toY, crossPxMirr, crossPyMirr);
					SetRaySegment(crossPxMirr, crossPyMirr, crossPpGx, crossPpGy);
					
				}
			}
			fromX = crossPxMirr;
			fromY = crossPyMirr;
			toX = crossPpGx;
			toY = crossPpGy;
		}
		
	}
    return 0;
}