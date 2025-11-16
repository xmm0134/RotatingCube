#include"Matrix.h"
#include<math.h>


Matrix2x2::Matrix2x2(float x, float y,
					 float x1, float y1)
{
	Elements[0][0] = x;
	Elements[0][1] = y;
	Elements[1][0] = x1;
	Elements[1][1] = y1;
}

Matrix2x2::Matrix2x2()
{

}

Matrix4x4::Matrix4x4(float x,  float y,  float z,  float w,
					 float x1, float y1, float z1, float w1, 
					 float x2, float y2, float z2, float w2, 
					 float x3, float y3, float z3, float w3)
{
	Elements[0][0] = x;
	Elements[0][1] = y;
	Elements[0][2] = z;
	Elements[0][3] = w;

	Elements[1][0] = x1;
	Elements[1][1] = y1;
	Elements[1][2] = z1;
	Elements[1][3] = w1;

	Elements[2][0] = x2;
	Elements[2][1] = y2;
	Elements[2][2] = z2;
	Elements[2][3] = w2;
					  
	Elements[3][0] = x3;
	Elements[3][1] = y3;
	Elements[3][2] = z3;
	Elements[3][3] = w3;

}

Matrix4x4::Matrix4x4() { };

void Matrix4x4::Transpose()
{

	Matrix4x4 Buffer;
	for (short int i = 0; i < 4; i++)
	{
		for (short int j = 0; j < 4; j++)
		{
			Buffer.Elements[i][j] = this->Elements[j][i];
		}
	}

	for (short int i = 0; i < 4; i++)
	{
		for (short int j = 0; j < 4; j++) 
		{
			this->Elements[i][j] = Buffer.Elements[i][j];
		}
	}

}
Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4()
{

}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3()
{

}

void Vector3::Normalize()
{
	float Magnatuide = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);

	this->x /= Magnatuide;
	this->y /= Magnatuide;
	this->z /= Magnatuide;
}
