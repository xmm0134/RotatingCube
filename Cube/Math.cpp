#include "Math.h"

extern Matrix4x4 Identity_Matrix( 1.0f, 0.0f,0.0f, 0.0f, 
								  0.0f, 1.0f, 0.0, 0.0f, 
								  0.0f, 0.0f, 1.0f, 0.0f, 
								  0.0f, 0.0f, 0.0f, 1.0f);

Matrix4x4 Math::Translate(Vector4 Translation)
{
	return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
				     0.0f, 1.0f, 0.0f, 0.0f,
				     0.0f, 0.0f, 1.0f, 0.0f,
				     Translation.x, Translation.y, Translation.z, 1.0f
	);
}

Matrix4x4 Math::RotateX(float Theta)
{
	float Radians = Theta * (PI / 180);
	if (Theta == 0)
	{
		return Identity_Matrix;
	}
	return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(Radians), -sin(Radians), 0.0f,
		0.0f, sin(Radians), cos(Radians), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Math::RotateY(float Theta)
{
	float Radians = Theta * (PI / 180);
	if (Theta == 0)
	{
		return Identity_Matrix;
	}
	return Matrix4x4(
		cos(Radians), 0.0f, -sin(Radians), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin(Radians), 0.0f, cos(Radians), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Math::RotateZ(float Theta)
{
	float Radians = Theta * (PI / 180);
	if (Theta == 0)
	{
		return Identity_Matrix;
	}
	return Matrix4x4(
		cos(Radians), sin(Radians), 0.0f, 0.0f,
		-sin(Radians), cos(Radians), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	
}

Matrix4x4 Math::Scale(float Factor)
{
	if (Factor == 0)
	{
		return Identity_Matrix;
	}
	return Matrix4x4(Factor, 0.0f,   0.0f,   0.0f,
				     0.0f,   Factor, 0.0f,   0.0f,
				     0.0f,   0.0f,   Factor, 0.0f,
				     0.0f,   0.0f,   0.0f,   1.0f
		);
}

Matrix4x4 Math::ProjectionMatrix(float AspectRatio, float FOV, float ZNear, float ZFar)
{
	float xPrime = (1 / tan(FOV / 2)) / AspectRatio;
	float yPrime = (1 / tan(FOV / 2));

	float A = ZFar / (ZFar - ZNear);
	float B = (-ZNear * ZFar) / (ZFar - ZNear);

	return Matrix4x4( xPrime, 0.0f,   0.0f, 0.0f,
					  0.0f,   yPrime, 0.0f, 0.0f,
				      0.0f,   0.0f,   A,	1.0f,
					  0.0f,   0.0f,   B,    0.0f
	);

}

Matrix4x4 Math::ViewMatrix(Vector3 CameraPos, Vector3 TargetPoint)
{
	Vector3 N = TargetPoint - CameraPos;
	N.Normalize();

	Vector3 Up(0, 1, 0);

	Vector3 U = Math::Cross(Up, N);
	U.Normalize();
	Vector3 V = Math::Cross(N, U);

	Matrix4x4 Camera(U.x, U.y, U.z, 0,
				     V.x, V.y, V.z, 0,
					 N.x, N.y, N.z, 0,
				     0.0f, 0.0f, 0.0f, 1.0f
		);

	Matrix4x4 Translation(1.0f, 0.0f, 0.0f, 0.0f,
						  0.0f, 1.0f, 0.0f, 0.0f,
					      0.0f, 0.0f, 1.0f, 0.0f,
						  -CameraPos.x, -CameraPos.y, -CameraPos.z, 1.0f
		);

	Matrix4x4 Product = Camera * Translation;

	Product.Transpose();

	return Product;
}

Vector3 Math::Cross(Vector3 A, Vector3 B)
{
	    // i    j	  k
	    // A.x  A.y  A.z
	    // B.x  B.y  B.z

	Vector3 result;
	result.x = A.y * B.z - A.z * B.y;
	result.y = A.z * B.x - A.x * B.z;
	result.z = A.x * B.y - A.y * B.x;
	return result;
}

float Math::Dot(Vector3 A, Vector3 B)
{
	return ((A.x * B.x) + (A.y * B.y) + (A.z * B.z));
}