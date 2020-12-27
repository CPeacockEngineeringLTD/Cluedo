#pragma once
#include "Vec3d.h"
#include <algorithm>
class Matrix {
	friend class Vec3d;
public:
	float m[4][4] = { 0 };//add overloads
	Matrix();
	Matrix(float a, float b, float c, float d, float e, float f, float g, float h,
		float i, float j, float k, float l, float n, float o, float p, float q);
	Matrix operator * (Matrix& rhs);
	static Matrix Matrix_MakeIdentity();
	static Matrix Matrix_MakeRotationX(float fAngleRad);
	static Matrix Matrix_MakeRotationY(float fAngleRad);
	static Matrix Matrix_MakeRotationZ(float fAngleRad);
	static Matrix Matrix_MakeTranslation(float x, float y, float z);
	static Matrix Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
	static Matrix Matrix_MultiplyMatrix(Matrix& m1, Matrix& m2);
	static Matrix Matrix_PointAt(Vec3d& pos, Vec3d& target, Vec3d& up);
	static Matrix Matrix_QuickInverse(Matrix& m);
};

