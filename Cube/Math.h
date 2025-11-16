#pragma once
#include"Matrix.h"
#include<math.h>
#define PI 3.1415926

namespace Math
{
	extern Matrix4x4 Translate(Vector4 Translation);

	extern Matrix4x4 RotateX(float Theta);

	extern Matrix4x4 RotateY(float Theta);

	extern Matrix4x4 RotateZ(float Theta);

	extern Matrix4x4 Scale(float Factor);

	extern Matrix4x4 ProjectionMatrix(float AspectRatio, float FOV, float ZNear, float ZFar);

	extern Matrix4x4 ViewMatrix(Vector3 CameraPos, Vector3 TargetPoint);

	extern Vector3 Cross(Vector3 A, Vector3 B);

	extern float Dot(Vector3 A, Vector3 B);

};