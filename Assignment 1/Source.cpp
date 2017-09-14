#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <vector>
#include<algorithm>
#include<cmath>
#include "Vect.h"
#include "Ray.h"
#include "CameraCoordSys.h"
#include "Color.h"
#include "Illumination.h"
#include "json/json.h"
#include "json/json-forwards.h"
#include <fstream>
#include "Material.h"
#include "WorldObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "Poly.h"
#include <list>

using namespace std;

int levelOfTracing = 1;

// Set up Camera
CameraCoordSys vcs(Vect(250, 250, 200), Vect(0, 1, 0), Vect(0, 0, -1));
Vect eye = vcs.VCS2WCS(Vect(0, 0, -300));

//Anti-aliasing factor
int antiAliasingFactor = 16;

//Spheres
Sphere s1 = Sphere(Vect(350, 250, -200), 100, Color(0.7, 0, 0), Material(0.01, 0.005, 0.1, 1.0 , 0.1 , 0.0));
Sphere s2 = Sphere(Vect(400, 400, 0), 80, Color(1, 1, 0), Material(0.01, 0.015, 0.1, 1.0, 0.1, 0.0));

//Planes
Plane p1 = Plane(Vect(0, 0, 0), Vect(0, 1, 0), Color(0.54, 0.27, 0.07), Material(0.01, 0.01, 0.1, 1,0,0));
Plane p2 = Plane(Vect(0, 800, 0), Vect(0,-1,0), Color(0.54, 0.27, 0.07), Material(0.01, 0.01, 0.1, 1,0,0));
Plane p3 = Plane(Vect(0, 0, -700), Vect(0, 0, 1), Color(0.54, 0.27, 0.07), Material(0.01, 0.01, 0.1, 1,0,0));
Plane p4 = Plane(Vect(-400, 0, 0), Vect(1, 0, 0), Color(0.54, 0.27, 0.07), Material(0.01, 0.01, 0.1, 1,0,0));
Plane p5 = Plane(Vect(900, 0, 0), Vect(-1, 0, 0), Color(0.54, 0.27, 0.07), Material(0.01, 0.01, 0.1, 1,0,0));

//Polygons0
list<Vect> ll1,ll2;

Poly pg1,pg2 ;

//lightSources
Illumination l1 = Illumination(Vect(10, 200, 900), 30);
Illumination l2 = Illumination(Vect(600, 500, 300), 70);

list<Sphere> listOfSpheres;

list<Plane> listOfPlanes;

list<Poly> listOfPolygons;



list<Illumination> listOfLight;



double AmbInt = 5;
int windowHeight=500, windowWidth=500;

//int modWindowHeight = antiAliasingFactor*windowHeight;
//int modWindowWidth = antiAliasingFactor*windowWidth;





void setPixel(int x, int y, Color c) {
	if (c.getR() > 1.0)	c.setR(1.0);
	if (c.getG() > 1.0)	c.setG(1.0);
	if (c.getB() > 1.0)	c.setB(1.0);
	glColor3f((GLfloat)c.getR(), (GLfloat)c.getG(), (GLfloat)c.getB());
	//cout << '('<<x <<','<< y<<')'<<endl;
	//glPointSize(4.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

Color findColor(Ray r, int noOfLevels) {
	if (noOfLevels == 0)
		return Color(0,0,0);

	Sphere closestSphere;
	Plane closestPlane;
	Poly closestPolygon;

	double minTSphere = 100000;
	double minTPlane = 100000;
	double minTPolygon = 100000;

	double intens = 0;
	for (Sphere s : listOfSpheres) {
		double t = s.getT(r);
		if (t > 0 && t < minTSphere) {
			closestSphere = s;
			minTSphere = t;
		}
	}
	for (Plane p : listOfPlanes) {
		double t = p.getT(r);

		if (t > 0 && t < minTPlane) {
			closestPlane = p;
			minTPlane = t;
		}
	}
	for (Poly p : listOfPolygons) {
		double t = p.getT(r);
		if (t > 0 && t < minTPolygon) {
			closestPolygon = p;
			minTPolygon = t;
		}
	}
	if (minTSphere < 100010 && minTSphere>99990 && minTPlane < 100010 && minTPlane>99990 && minTPolygon < 100010 && minTPolygon>99990) { return Color(0,0,0); }
	if (minTSphere < minTPlane && minTSphere < minTPolygon) {
		Vect v = closestSphere.getIntersect(r);
		for (Illumination l : listOfLight) {
			intens += l.getIntensityAtIntersectSphere(closestSphere, v, eye);
		}
		double ambient = closestSphere.getMaterial().getAmbCoff()* AmbInt;
		double intensity = ambient + intens;
		if (closestSphere.getMaterial().getCoeffForReflect() > 0.00001) {
			Vect s = v;
			Vect dir = r.getDir().minus((closestSphere.getNormal(v)).scalarMult(2 * (-1)*((r.getDir()).dot(closestSphere.getNormal(v))))).unitVector();
			Ray reflectedRay = Ray(s, dir, 1);
			Color rgb = findColor(reflectedRay, noOfLevels - 1);
			if (rgb.equals(Color(0, 0, 0))) { intensity += 0;}
			else {
				intensity += (rgb.getIntensityFromOriginalColor())*(closestSphere.getMaterial().getCoeffForReflect());
			}
		}
		if (closestSphere.getMaterial().getCoeffForTransmit() > 0.00001) {
			Vect s = v;
			Vect dir = closestSphere.getTransmitRayDirection(r, v);
			Ray transmitRay = Ray(s, dir, 1);
			Color rgb = findColor(transmitRay, noOfLevels - 1);
			if (rgb.equals(Color(0, 0, 0))) { intensity += 0; }
			else {
				intensity += (rgb.getIntensityFromOriginalColor())*(closestSphere.getMaterial().getCoeffForTransmit())*(closestSphere.getMaterial().getCoeffForTransmit());
			}
		}
		Color col = closestSphere.getColor().scalarmult(intensity);
		return col;
	}
	else if (minTPlane < minTSphere && minTPlane < minTPolygon) {
		Vect v = closestPlane.getIntersect(r);
		for (Illumination l : listOfLight) {
			intens += l.getIntensityAtIntersectPlane(closestPlane, v, eye);
		}
		double ambient = closestPlane.getMaterial().getAmbCoff()* AmbInt;
		double intensity = ambient + intens;
		if (closestPlane.getMaterial().getCoeffForReflect() > 0.00001) {
			Vect s = v;
			Vect dir = r.getDir().minus((closestPlane.getNormal(v)).scalarMult(2 * (-1)*((r.getDir()).dot(closestPlane.getNormal(v))))).unitVector();
			Ray reflectedRay = Ray(s, dir, 1);
			Color rgb = findColor(reflectedRay, noOfLevels - 1);
			if (rgb.equals(Color(0, 0, 0))) intensity += 0;
			else {
				intensity += (rgb.getIntensityFromOriginalColor())*(closestPlane.getMaterial().getCoeffForReflect());
			}
		}		
		if (closestPlane.getMaterial().getCoeffForTransmit() > 0.00001) {
			Vect s = v;
			Vect dir = closestPlane.getTransmitRayDirection(r, v);
			Ray transmitRay = Ray(s, dir, 1);
			Color rgb = findColor(transmitRay, noOfLevels - 1);
			if (rgb.equals(Color(0, 0, 0))) { intensity += 0; }
			else {
				intensity += (rgb.getIntensityFromOriginalColor())*(closestPlane.getMaterial().getCoeffForTransmit());
			}
		}
		Color col = closestPlane.getColor().scalarmult(intensity);
		return col;
	}
	else if (minTPolygon < minTSphere && minTPolygon < minTPlane) {
		Vect v = closestPolygon.getIntersect(r);
		for (Illumination l : listOfLight) {
			intens += l.getIntensityAtIntersectPolygon(closestPolygon, v, eye);
		}
		double ambient = closestPolygon.getMaterial().getAmbCoff()* AmbInt;
		double intensity = ambient + intens;
		if (closestPolygon.getMaterial().getCoeffForReflect() > 0.00001) {
			Vect s = v;
			Vect dir = r.getDir().minus((closestPolygon.getNormal(v)).scalarMult(2 * (-1)*((r.getDir()).dot(closestPolygon.getNormal(v))))).unitVector();
			Ray reflectedRay = Ray(s, dir, 1);
			Color rgb = findColor(reflectedRay, noOfLevels - 1);
			if (rgb.equals(Color(0, 0, 0))) intensity += 0;
			else {
				intensity += (rgb.getIntensityFromOriginalColor())*(closestPolygon.getMaterial().getCoeffForReflect());
			}
		}
		if (closestPolygon.getMaterial().getCoeffForTransmit() > 0.00001) {
			Vect s = v;
			Vect dir = closestPolygon.getTransmitRayDirection(r, v);
			Ray transmitRay = Ray(s, dir, 1);
			Color rgb = findColor(transmitRay, noOfLevels - 1);
			if (rgb.equals(Color(0, 0, 0))) { intensity += 0; }
			else {
				intensity += (rgb.getIntensityFromOriginalColor())*(closestPolygon.getMaterial().getCoeffForTransmit());
			}
		}
		Color col = closestPolygon.getColor().scalarmult(intensity);
		return col;
	}
}



void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);//clear black	
	glColor3f(1.0, 0.0, 0.0);


	ll1.push_back(Vect(350, 120, -50));
	ll1.push_back(Vect(350, 120, 50));
	ll1.push_back(Vect(300, 120, 100));
	ll1.push_back(Vect(250, 120, 50));
	ll1.push_back(Vect(250, 120, -50));
	pg1 = Poly(ll1, Color(0, 1, 0), Material(0.01, 0.01, 0.1, 1,0,0));

	ll2.push_back(Vect(50, 150, -50));
	ll2.push_back(Vect(50, 250, -50));
	ll2.push_back(Vect(100, 300, -50));
	ll2.push_back(Vect(150, 250, -50));
	ll2.push_back(Vect(150, 150, -50));
	pg2 = Poly(ll2, Color(0, 0.4, 0), Material(0.01, 0.01, 0.1, 1, 0, 0));

	listOfSpheres.push_back(s2);
	listOfSpheres.push_back(s1);
	
	listOfPlanes.push_back(p1);
	listOfPlanes.push_back(p2);
	//listOfPlanes.push_back(p3);
	listOfPlanes.push_back(p4);
	listOfPlanes.push_back(p5);

	listOfPolygons.push_back(pg1);
	listOfPolygons.push_back(pg2);

	listOfLight.push_back(l1);
	listOfLight.push_back(l2);


	for (int i = 0; i < windowWidth; i++) {
		for (int j = 0; j < windowHeight; j++) {

			Vect pointOnScreen = Vect(i - windowWidth / 2, j - windowHeight / 2, 0);
			Vect pointOnScreenWCS = vcs.VCS2WCS(pointOnScreen);
			Vect dir = pointOnScreenWCS.minus(eye).unitVector();
			Ray r = Ray(eye, dir, 1);
			Color finalColor = findColor(r, levelOfTracing);
			if (finalColor.equals(Color(0, 0, 0))) continue;
			setPixel(i, j, finalColor);
			
		}
	}

	glutSwapBuffers();
}

void reshape(int w, int h)
{

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowWidth, windowHeight); 
	glutCreateWindow("OpenGL First Window");
	glewInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}






