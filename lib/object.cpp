#include "object.h"
#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include "raylib.h"

void Object::CalculateRotationMatrix() {
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

void Object::RotatePoints() {
	RotatedPoints.resize(points.size());
	std::vector<std::array<double, 3>> test(points.size());
	for(int p = 0; p < points.size(); p++) {
		for(int i = 0; i < 3; i++) {
			RotatedPoints[p][i] = 0;
			test[p][i] = 0;
			for(int j = 0; j < 3; j++) {
				test[p][i] += RotationMatrix[i][j] * (points[p][j] - ObjectCenter[j]);
			}
			RotatedPoints[p][i] = test[p][i] + ObjectCenter[i];
		}
	}
}

void Object::ConvertPoints(double CameraOffsetX, double CameraOffsetY, double CameraOffsetZ, double f, int width, int height) {
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
			break;
			case 1:
			p2 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
			break;
			case 2:
			p3 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
			break;
			case 3:
			p4 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
			break;
			case 4:
			p5 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
			break;
			case 5:
			p6 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
			break;
			case 6:
			p7 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
			break;
			case 7:
			p8 = {NewPosX, NewPosY, i[2] + CameraOffsetZ};
			break;
		}
		turn++;
	}
}

void Object::DrawObjectLines(int LineThickness) {
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

void Object::SetCenter() {
	double MinX = points.front()[0];
	double MaxX = points.front()[0];
	double MinY = points.front()[1];
	double MaxY = points.front()[1];
	double MinZ = points.front()[2];
	double MaxZ = points.front()[2];
	for( std::array<double, 3>& i : points ) {
		if(i[0] < MinX) {
		MinX = i[0];	
		}
		if(i[0] > MaxX) {
		MaxX = i[0];	
		}
		if(i[1] < MinY) {
		MinY = i[1];	
		}
		if(i[1] > MaxY) {
		MaxY = i[1];	
		}
		if(i[2] < MinZ) {
		MinZ = i[2];
		}
		if(i[2] > MaxZ) {
		MaxZ = i[2];	
		}
				
		if(i == points.back()) {
		ObjectCenter = {MinX+((MaxX-MinX)/2), MinY+((MaxY-MinY)/2), MinZ+((MaxZ-MinZ)/2)};
		}
	}
}