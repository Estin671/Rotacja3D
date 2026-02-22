#pragma once
#include <vector>
#include <array>

class Object {
public:
	std::vector<std::array<double, 3>> points;
	std::vector<std::array<double, 3>> RotatedPoints;
	std::vector<std::array<double, 2>> ConvertedPoints;
	double alpha;
	double beta;
	double gammaang;
	std::array<double, 3> p1;
	std::array<double, 3> p2;
	std::array<double, 3> p3;
	std::array<double, 3> p4;
	std::array<double, 3> p5;
	std::array<double, 3> p6;
	std::array<double, 3> p7;
	std::array<double, 3> p8;
	
	void CalculateRotationMatrix();
	void RotatePoints();
	void ConvertPoints(double CameraOffsetX, double CameraOffsetY, double CameraOffsetZ, double f, int width, int height);
	void DrawObjectLines(int LineThickness);
	void SetCenter();
private:
	double RotationMatrix[3][3];
	std::array<double, 3> ObjectCenter;
};