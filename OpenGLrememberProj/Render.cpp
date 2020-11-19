#include "Render.h"
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <math.h>
#include "Vec3.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>

#define _USE_MATH_DEFINES


double f(double p0, double p1, double p2, double p3, double t)// формула кривой Ѕезье
{
	return (p0 * (1 - t) * (1 - t) * (1 - t)) + (3 * t * (1 - t) * (1 - t) * p1) + (3 * t * t * (1 - t) * p2) + t * t * t * p3; //посчитанна€ формула
}

double f2(double p1, double p4, double R1, double R4, double t) // формула кривой Ёрмита
{

	return (p1 * (2 * t * t * t - 3 * t * t + 1) + p4 * (-2 * t * t * t + 3 * t * t) + R1 * (t * t * t - 2 * t * t + t) + R4 * (t * t * t - t * t));
}

double t_max = 0;
void Bezye1()
{
	//	t_max += delta_time / 5; //t_max становитс€ = 1 за 5 секунд
		//if (t_max > 1) t_max = 0; //после обнул€етс€
	double P1[] = { 0,0,0 }; //Ќаши точки
	double P2[] = { -4,6,7 };
	double P3[] = { 10,10,7 };
	double P4[] = { 8,1,0 };
	double P[4];
	glBegin(GL_LINE_STRIP); //построим отрезки P1P2 и P2P3
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.001; t += 0.01)
	{
		P[0] = f(P1[0], P2[0], P3[0], P4[0], t);
		P[1] = f(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = f(P1[2], P2[2], P3[2], P4[2], t);
		P[3] = f(P1[3], P2[3], P3[3], P4[3], t);
		glVertex3dv(P); //–исуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(P);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
}

Vector3 Bezye11(double* P1, double* P2, double P3[3], double P4[3], double t)
{
	//	t_max += delta_time / 5; //t_max становитс€ = 1 за 5 секунд
		//if (t_max > 1) t_max = 0; //после обнул€етс€

	double P[4];

	P[0] = f(P1[0], P2[0], P3[0], P4[0], t);
	P[1] = f(P1[1], P2[1], P3[1], P4[1], t);
	P[2] = f(P1[2], P2[2], P3[2], P4[2], t);
	P[3] = f(P1[3], P2[3], P3[3], P4[3], t);

	Vector3 D;
	D.setCoords(P[0], P[1], P[2]);
	return D;
}
void Bezye2()
{

	//t_max += delta_time / 5; //t_max становитс€ = 1 за 5 секунд
	//if (t_max > 1) t_max = 0; //после обнул€етс€
	double P1[] = { 1,2,3 }; //Ќаши точки
	double P2[] = { 3,2,1 };
	double P3[] = { 12,10,2 };
	double P4[] = { 10,1,0 };
	double P[4];
	glBegin(GL_LINE_STRIP); //построим отрезки P1P2 и P2P3
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01)
	{
		P[0] = f(P1[0], P2[0], P3[0], P4[0], t);
		P[1] = f(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = f(P1[2], P2[2], P3[2], P4[2], t);
		P[3] = f(P1[3], P2[3], P3[3], P4[3], t);
		glVertex3dv(P); //–исуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(P);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
}
void Ermita1()
{
	double P1[] = { 0, 0, 0 }; //Ќаши точки
	double P2[] = { 2,0, 4 };
	double P3[] = { 4,0,4 };
	double P4[] = { 8, 0 ,0 };


	double R1[] = { 0, 0, 0 };
	double R4[] = { 0, 0, 0 };

	R1[0] = P2[0] - P1[0]; //нахождение векторов
	R1[1] = P2[1] - P1[1];
	R1[2] = P2[2] - P1[2];

	R4[0] = P4[0] - P3[0];
	R4[1] = P4[1] - P3[1];
	R4[2] = P4[2] - P3[2];

	glLineWidth(1); //ширина линии

	glBegin(GL_LINE_STRIP);
	glVertex3dv(P2); //отрисовка векторов
	glVertex3dv(P1);
	glEnd();

	glLineWidth(3); //ширина линии

	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01) //отрисовка кривой Ёрмита
	{
		double P[4];
		P[0] = f2(P1[0], P4[0], R1[0], R4[0], t);
		P[1] = f2(P1[1], P4[1], R1[1], R4[1], t);
		P[2] = f2(P1[2], P4[2], R1[2], R4[2], t);
		P[3] = f2(P1[3], P4[3], R1[3], R4[3], t);
		glVertex3dv(P); //–исуем точку P
	}
	glEnd();

	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();

}
void Ermita2()
{
	double P1[] = { 0, 6, 2 }; //Ќаши точки
	double P2[] = { 2,12, 9 };
	double P3[] = { 5,6,9 };
	double P4[] = { 9, 6 ,2 };


	double R1[] = { 0, 0, 0 };
	double R4[] = { 0, 0, 0 };

	R1[0] = P2[0] - P1[0]; //нахождение векторов
	R1[1] = P2[1] - P1[1];
	R1[2] = P2[2] - P1[2];

	R4[0] = P4[0] - P3[0];
	R4[1] = P4[1] - P3[1];
	R4[2] = P4[2] - P3[2];

	glLineWidth(1); //ширина линии

	glBegin(GL_LINE_STRIP);
	glVertex3dv(P2); //отрисовка векторов
	glVertex3dv(P1);
	glEnd();

	glLineWidth(3); //ширина линии

	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01) //отрисовка кривой Ёрмита
	{
		double P[4];
		P[0] = f2(P1[0], P4[0], R1[0], R4[0], t);
		P[1] = f2(P1[1], P4[1], R1[1], R4[1], t);
		P[2] = f2(P1[2], P4[2], R1[2], R4[2], t);
		P[3] = f2(P1[3], P4[3], R1[3], R4[3], t);
		glVertex3dv(P); //–исуем точку P
	}
	glEnd();

	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();

}

void Object()
{

	glColor3f(0, 0.34, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(1, -0.5, 0.5);
	glVertex3f(1, 0.5, 0.5);
	glVertex3f(-1, 0.5, 0.5);
	glVertex3f(-1, -0.5, 0.5);
	glEnd();

	// ‘иолетова€ сторона Ч ѕ–ј¬јя
	glBegin(GL_POLYGON);

	glVertex3f(1, -0.5, -0.5);
	glVertex3f(1, 0.5, -0.5);
	glVertex3f(1, 0.5, 0.5);
	glVertex3f(1, -0.5, 0.5);
	glEnd();

	// «елена€ сторона Ч Ћ≈¬јя
	glBegin(GL_POLYGON);

	glVertex3f(-1, -0.5, 0.5);
	glVertex3f(-1, 0.5, 0.5);
	glVertex3f(-1, 0.5, -0.5);
	glVertex3f(-1, -0.5, -0.5);
	glEnd();

	// —ин€€ сторона Ч ¬≈–’Ќяя
	glBegin(GL_POLYGON);

	glVertex3f(1, 0.5, 0.5);
	glVertex3f(1, 0.5, -0.5);
	glVertex3f(-1, 0.5, -0.5);
	glVertex3f(-1, 0.5, 0.5);
	glEnd();

	//  расна€ сторона Ч Ќ»∆Ќяя
	glBegin(GL_POLYGON);

	glVertex3f(1, -0.5, -0.5);
	glVertex3f(1, 0.5, -0.5);
	glVertex3f(-1, 0.5, -0.5);
	glVertex3f(-1, -0.5, -0.5);
	glEnd();

	//  расна€ сторона Ч Ѕќ ќ¬јя
	glBegin(GL_POLYGON);

	glVertex3f(1, -0.5, -0.5);
	glVertex3f(1, -0.5, 0.5);
	glVertex3f(-1, -0.5, 0.5);
	glVertex3f(-1, -0.5, -0.5);
	glEnd();
}

void Bese2(double delta_time)
{
	static double t_max = 0;
	static bool flagReverse = false;

	if (!flagReverse)
	{
		t_max += delta_time / 5; //t_max становитс€ = 1 за 5 секунд
		if (t_max > 1)
		{
			t_max = 1; //после обнул€етс€
			flagReverse = !flagReverse;
		}
	}
	else
	{
		t_max -= delta_time / 5; //t_max становитс€ = 1 за 5 секунд
		if (t_max < 0)
		{
			t_max = 0; //после обнул€етс€
			flagReverse = !flagReverse;
		}
	}
	double P1[] = { 0,0,0 }; //Ќаши точки
	double P2[] = { -4,6,7 };
	double P3[] = { 10,10,7 };
	double P4[] = { 8,1,0 };
	Bezye1();

	Vector3 P_old = Bezye11(P1, P2, P3, P4, !flagReverse ? t_max - delta_time : t_max + delta_time);
	Vector3 P = Bezye11(P1, P2, P3, P4, t_max);
	Vector3 VecP_P_old = (P - P_old).normolize();

	Vector3 rotateX(VecP_P_old.X(), VecP_P_old.Y(), 0);
	rotateX = rotateX.normolize();

	Vector3 VecPrX = Vector3(1, 0, 0).vectProisvedenie(rotateX);
	double CosX = Vector3(1, 0, 0).ScalarProizv(rotateX);
	double SinAngleZ = VecPrX.Z() / abs(VecPrX.Z());
	double AngleOZ = acos(CosX) * 180 / PI * SinAngleZ;

	double AngleOY = acos(VecP_P_old.Z()) * 180 / PI - 90;

	double A[] = { -0.5,-0.5,-0.5 };
	glPushMatrix();
	glTranslated(P.X(), P.Y(), P.Z());
	glRotated(AngleOZ, 0, 0, 1);
	glRotated(AngleOY, 0, 1, 0);
	//glRotated(CalculateAngleOZ(P_old, P), 0, 0, 1);
	Object();
	glPopMatrix();

	glColor3d(0, 0, 0);

}

void Render(double delta_time)
{
	Bezye1();
	Bezye2();

	Ermita1();
	Ermita2();

	//Object();

	Bese2(delta_time);

}