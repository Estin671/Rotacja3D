#include <iostream>
#include <math.h>
#include <array>
#include <vector>
#include "raylib.h"

int height = 1000;
int width = 1000;
double CameraFOV = 30.0;
double f = double(height)/(2.0*tan(CameraFOV/2.0));
int LineThickness = 5;
std::array<double, 3> Center = {1.5, 1.5, 2.5};
double CameraOffsetX = 0;
double CameraOffsetY = 0;
double CameraOffsetZ = 0;

class Object {
	public:
		std::vector<std::array<double, 3>> points;
		std::vector<std::array<double, 3>> RotatedPoints;
		std::vector<std::array<double, 2>> ConvertedPoints;
		double alpha = 0;
		double beta = 0;
		double gammaang = 0;
		double RotationMatrix[3][3];
		std::array<double, 3> p1;
		std::array<double, 3> p2;
		std::array<double, 3> p3;
		std::array<double, 3> p4;
		std::array<double, 3> p5;
		std::array<double, 3> p6;
		std::array<double, 3> p7;
		std::array<double, 3> p8;
	
		void CalculateRotationMatrix() {
		RotationMatrix[0][0] = cos(beta)*cos(gammaang);
		RotationMatrix[0][1] = (sin(alpha)*sin(beta)*cos(gammaang)) - (cos(alpha)*sin(gammaang));
		RotationMatrix[0][2] = (cos(alpha)*sin(beta)*cos(gammaang)) + (sin(alpha)*sin(gammaang));

		RotationMatrix[1][0] = cos(beta)*sin(gammaang);
		RotationMatrix[1][1] = (sin(alpha)*sin(beta)*sin(gammaang)) + (cos(alpha)*cos(gammaang));
		RotationMatrix[1][2] = (cos(alpha)*sin(beta)*sin(gammaang)) - (sin(alpha)*cos(gammaang));

		RotationMatrix[2][0] = -sin(beta);
		RotationMatrix[2][1] = sin(alpha)*cos(beta);
		RotationMatrix[2][2] = cos(alpha)*cos(beta);
		}
	
		void RotatePoints() {
			RotatedPoints.resize(points.size());
			std::vector<std::array<double, 3>> test(points.size());
			for(int p = 0; p < points.size(); p++) {
				for(int i = 0; i < 3; i++) {
					RotatedPoints[p][i] = 0;
					test[p][i] = 0;
					for(int j = 0; j < 3; j++) {
						test[p][i] += RotationMatrix[i][j] * (points[p][j] - Center[j]);
					}
					RotatedPoints[p][i] = test[p][i] + Center[i];
				}
			}
		}
		
		void ConvertPoints() {
			int turn = 0;
			for( std::array<double, 3>& i : RotatedPoints ) {
				double NewPosX = width/2 + ((i[0] - CameraOffsetX)*f)/(i[2] + CameraOffsetZ);
				double NewPosY = height/2 - ((i[1] - CameraOffsetY)*f)/(i[2] + CameraOffsetZ);
				ConvertedPoints.push_back({NewPosX, NewPosY});
				if(i[2] + CameraOffsetZ > 0) {
				DrawCircle(NewPosX, NewPosY, 20 / (i[2] + CameraOffsetZ), BLACK);
				}
				
				switch(turn) {
					case 0:
					p1 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
					case 1:
					p2 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
					case 2:
					p3 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
					case 3:
					p4 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
					case 4:
					p5 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
					case 5:
					p6 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
					case 6:
					p7 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
					case 7:
					p8 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
				}
				turn++;
			}
		}
		
		void DrawObjectLines() {
			if(p1[2] > 0 && p2[2] > 0) {
			DrawLineEx({p1[0], p1[1]}, {p2[0], p2[1]}, LineThickness, BLACK);
			}
			if(p2[2] > 0 && p4[2] > 0) {
			DrawLineEx({p2[0], p2[1]}, {p4[0], p4[1]}, LineThickness, BLACK);
			}
			if(p4[2] > 0 && p3[2] > 0) {
			DrawLineEx({p4[0], p4[1]}, {p3[0], p3[1]}, LineThickness, BLACK);
			}
			if(p3[2] > 0 && p1[2] > 0) {
			DrawLineEx({p3[0], p3[1]}, {p1[0], p1[1]}, LineThickness, BLACK);
			}
		
			// podstawa dalsza
			if(p6[2] > 0 && p5[2] > 0) {
			DrawLineEx({p6[0], p6[1]}, {p5[0], p5[1]}, LineThickness, BLACK);
			}
			if(p5[2] > 0 && p8[2] > 0) {
			DrawLineEx({p5[0], p5[1]}, {p8[0], p8[1]}, LineThickness, BLACK);
			}
			if(p8[2] > 0 && p7[2] > 0) {
			DrawLineEx({p8[0], p8[1]}, {p7[0], p7[1]}, LineThickness, BLACK);
			}
			if(p7[2] > 0 && p6[2] > 0) {
			DrawLineEx({p7[0], p7[1]}, {p6[0], p6[1]}, LineThickness, BLACK);
			}
		
			// ściany boczne
			if(p1[2] > 0 && p6[2] > 0) {
			DrawLineEx({p1[0], p1[1]}, {p6[0], p6[1]}, LineThickness, BLACK);
			}
			if(p2[2] > 0 && p5[2] > 0) {
			DrawLineEx({p2[0], p2[1]}, {p5[0], p5[1]}, LineThickness, BLACK);
			}
			if(p3[2] > 0 && p7[2] > 0) {
			DrawLineEx({p3[0], p3[1]}, {p7[0], p7[1]}, LineThickness, BLACK);
			}
			if(p4[2] > 0 && p8[2] > 0) {
			DrawLineEx({p4[0], p4[1]}, {p8[0], p8[1]}, LineThickness, BLACK);
			}
		}
};

double DegToRad(double angle) {
	return angle * (M_PI/180.0);
}

int main() {
	
	Object cube;
	cube.points = {
	{2, 1, 2},
	{1, 1, 2},
	{2, 2, 2},
	{1, 2, 2},
	{1, 1, 3},
	{2, 1, 3},
	{2, 2, 3},
	{1, 2, 3}	
	};
	
	InitWindow(width, height, "world");
	SetTargetFPS(60);
	while(!WindowShouldClose()) {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	if(IsKeyDown(KEY_D)) {
		CameraOffsetX += 0.05;
	}
		
	else if(IsKeyDown(KEY_A)) {
		CameraOffsetX -= 0.05;
	}
		
	if(IsKeyDown(KEY_W)) {
		CameraOffsetZ -= 0.05;
	}
		
	else if(IsKeyDown(KEY_S)) {
		CameraOffsetZ += 0.05;
	}
		
	if(IsKeyDown(KEY_LEFT_SHIFT)) {
		CameraOffsetY += 0.05;
	}
	else if(IsKeyDown(KEY_SPACE)) {
		CameraOffsetY -= 0.05;
	}
	
	if(IsKeyDown(KEY_U)) {
	cube.alpha += DegToRad(2.0);
	cube.beta += DegToRad(2.0);
	cube.gammaang += DegToRad(2.0);
	}
	cube.CalculateRotationMatrix();
	cube.RotatePoints();
	cube.ConvertPoints();
	/*
	for(std::array<double, 3>& i : cube.RotatedPoints ) {
	std::cout << i[0] << ", " << i[1] << ", " << i[2] << std::endl; 	
	}
	*/
	cube.DrawObjectLines();
	EndDrawing();	
	cube.ConvertedPoints.clear();
	}
	CloseWindow();
	
	return 0;
}