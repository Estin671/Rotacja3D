#include <iostream>
#include <math.h>
#include <array>
#include <vector>
#include "raylib.h"
#include "object.h"

int height = 1000;
int width = 1000;
double CameraFOV = 30.0;
double f = double(height)/(2.0*tan(CameraFOV/2.0));
int LineThickness = 5;
//std::array<double, 3> Center = {1.5, 1.5, 2.5};
double CameraOffsetX = 0;
double CameraOffsetY = 0;
double CameraOffsetZ = 0;


double DegToRad(double angle) {
	return angle * (M_PI/180.0);
}

int main() {
	
	bool SelectionMode = false;
	std::vector<Object> Objects;
	
	/*
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
	
	Objects.push_back(cube);
	*/
	
	InitWindow(width, height, "world");
	SetTargetFPS(60);
	while(!WindowShouldClose()) {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	if(IsKeyPressed(KEY_V)) {
		if(SelectionMode) {
		SelectionMode = false;	
		}
		else {
		SelectionMode = true;	
		}
	}
	
	if(SelectionMode) {
	DrawText("Tryb przesuwania obiektu aktywowany", 20, 20, 20, GREEN);	
	}
	
	if(IsKeyDown(KEY_D) && !SelectionMode) {
		CameraOffsetX -= 0.05;
	}
		
	else if(IsKeyDown(KEY_A) && !SelectionMode) {
		CameraOffsetX += 0.05;
	}
		
	if(IsKeyDown(KEY_W) && !SelectionMode) {
		CameraOffsetZ -= 0.05;
	}
		
	else if(IsKeyDown(KEY_S) && !SelectionMode) {
		CameraOffsetZ += 0.05;
	}
		
	if(IsKeyDown(KEY_LEFT_SHIFT) && !SelectionMode) {
		CameraOffsetY += 0.05;
	}
	else if(IsKeyDown(KEY_SPACE) && !SelectionMode) {
		CameraOffsetY -= 0.05;
	}
	
	if(IsKeyDown(KEY_D) && SelectionMode) {
		for(int i = 0; i < 8; i++) {
		Objects.back().points[i][0] += 0.05;
		}
	}
		
	else if(IsKeyDown(KEY_A) && SelectionMode) {
		for(int i = 0; i < 8; i++) {
		Objects.back().points[i][0] -= 0.05;
		}
	}
		
	if(IsKeyDown(KEY_W) && SelectionMode) {
		for(int i = 0; i < 8; i++) {
		Objects.back().points[i][2] -= 0.05;
		}
	}
		
	else if(IsKeyDown(KEY_S) && SelectionMode) {
		for(int i = 0; i < 8; i++) {
		Objects.back().points[i][2] += 0.05;
		}
	}
		
	if(IsKeyDown(KEY_LEFT_SHIFT) && SelectionMode) {
		for(int i = 0; i < 8; i++) {
		Objects.back().points[i][1] += 0.05;
		}
	}
	else if(IsKeyDown(KEY_SPACE) && SelectionMode) {
		for(int i = 0; i < 8; i++) {
		Objects.back().points[i][1] -= 0.05;
		}
	}
	
	if(IsKeyDown(KEY_U)) {
	for( Object& j : Objects ) {
	j.alpha += DegToRad(2.0);
	j.beta += DegToRad(2.0);
	j.gammaang += DegToRad(2.0);
	std::cout << j.alpha << std::endl;
	}
	}
	
	if(IsKeyPressed(KEY_G)) {
		Object i;
		i.points = 
		{
		{2, 1, 2},
		{1, 1, 2},
		{2, 2, 2},
		{1, 2, 2},
		{1, 1, 3},
		{2, 1, 3},
		{2, 2, 3},
		{1, 2, 3}	
		};
		i.SetCenter();
		Objects.push_back(i);
	}
	 
	for( Object i : Objects ) {
	i.SetCenter();
	i.CalculateRotationMatrix();
	i.RotatePoints();
	i.ConvertPoints(CameraOffsetX, CameraOffsetY, CameraOffsetZ, f, width, height);
	/*
	for(std::array<double, 3>& i : cube.RotatedPoints ) {
	std::cout << i[0] << ", " << i[1] << ", " << i[2] << std::endl; 	
	}
	*/
	i.DrawObjectLines(LineThickness);
	}
	EndDrawing();	
		for( Object i : Objects ) {
		i.ConvertedPoints.clear();
		}
	}
	CloseWindow();
	
	return 0;
}