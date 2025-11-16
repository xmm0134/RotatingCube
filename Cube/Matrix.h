#pragma once


struct Matrix2x2
{
	Matrix2x2(float x, float y,
		float x1, float y1);

	Matrix2x2();

	union
	{
		float Elements[2][2];

		struct
		{
			float x, y;
			float x1, y1;
		}s;
	};
	Matrix2x2 operator*(Matrix2x2& other)
	{
		Matrix2x2 m;
		m.Elements[0][0] = Elements[0][0] * other.Elements[0][0] + Elements[0][1] * other.Elements[1][0];
		m.Elements[0][1] = Elements[0][0] * other.Elements[0][1] + Elements[0][1] * other.Elements[1][1];

		m.Elements[1][0] = Elements[1][0] * other.Elements[0][0] + Elements[1][1] * other.Elements[1][0];
		m.Elements[1][1] = Elements[1][0] * other.Elements[0][1] + Elements[1][1] * other.Elements[1][1];

		return m;
	}
};

struct Vector3
{
	Vector3(float x,
			float y,
			float z
	);

	Vector3();

	float x, y, z;

	void Normalize();

	const Vector3& operator+(const Vector3& other)
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	const Vector3& operator-(const Vector3& other)
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	const Vector3& operator*(const Vector3& other)
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	const Vector3& operator/(const Vector3& other)
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}
	
};

struct Matrix4x4
{
	Matrix4x4(float x,  float y,  float z,  float w,
			  float x1, float y1, float z1, float w1,
			  float x2, float y2, float z2, float w2,
			  float x3, float y3, float z3, float w3);

	Matrix4x4();


	float Elements[4][4];
	Matrix4x4 operator*(const Matrix4x4& other) const
	{
		Matrix4x4 NewMatrix;

		NewMatrix.Elements[0][0] = Elements[0][0] * other.Elements[0][0] + Elements[0][1] * other.Elements[1][0] + Elements[0][2] * other.Elements[2][0] + Elements[0][3] * other.Elements[3][0];
		NewMatrix.Elements[0][1] = Elements[0][0] * other.Elements[0][1] + Elements[0][1] * other.Elements[1][1] + Elements[0][2] * other.Elements[2][1] + Elements[0][3] * other.Elements[3][1];
		NewMatrix.Elements[0][2] = Elements[0][0] * other.Elements[0][2] + Elements[0][1] * other.Elements[1][2] + Elements[0][2] * other.Elements[2][2] + Elements[0][3] * other.Elements[3][2];
		NewMatrix.Elements[0][3] = Elements[0][0] * other.Elements[0][3] + Elements[0][1] * other.Elements[1][3] + Elements[0][2] * other.Elements[2][3] + Elements[0][3] * other.Elements[3][3];

		NewMatrix.Elements[1][0] = Elements[1][0] * other.Elements[0][0] + Elements[1][1] * other.Elements[1][0] + Elements[1][2] * other.Elements[2][0] + Elements[1][3] * other.Elements[3][0];
		NewMatrix.Elements[1][1] = Elements[1][0] * other.Elements[0][1] + Elements[1][1] * other.Elements[1][1] + Elements[1][2] * other.Elements[2][1] + Elements[1][3] * other.Elements[3][1];
		NewMatrix.Elements[1][2] = Elements[1][0] * other.Elements[0][2] + Elements[1][1] * other.Elements[1][2] + Elements[1][2] * other.Elements[2][2] + Elements[1][3] * other.Elements[3][2];
		NewMatrix.Elements[1][3] = Elements[1][0] * other.Elements[0][3] + Elements[1][1] * other.Elements[1][3] + Elements[1][2] * other.Elements[2][3] + Elements[1][3] * other.Elements[3][3];

		NewMatrix.Elements[2][0] = Elements[2][0] * other.Elements[0][0] + Elements[2][1] * other.Elements[1][0] + Elements[2][2] * other.Elements[2][0] + Elements[2][3] * other.Elements[3][0];
		NewMatrix.Elements[2][1] = Elements[2][0] * other.Elements[0][1] + Elements[2][1] * other.Elements[1][1] + Elements[2][2] * other.Elements[2][1] + Elements[2][3] * other.Elements[3][1];
		NewMatrix.Elements[2][2] = Elements[2][0] * other.Elements[0][2] + Elements[2][1] * other.Elements[1][2] + Elements[2][2] * other.Elements[2][2] + Elements[2][3] * other.Elements[3][2];
		NewMatrix.Elements[2][3] = Elements[2][0] * other.Elements[0][3] + Elements[2][1] * other.Elements[1][3] + Elements[2][2] * other.Elements[2][3] + Elements[2][3] * other.Elements[3][3];

		NewMatrix.Elements[3][0] = Elements[3][0] * other.Elements[0][0] + Elements[3][1] * other.Elements[1][0] + Elements[3][2] * other.Elements[2][0] + Elements[3][3] * other.Elements[3][0];
		NewMatrix.Elements[3][1] = Elements[3][0] * other.Elements[0][1] + Elements[3][1] * other.Elements[1][1] + Elements[3][2] * other.Elements[2][1] + Elements[3][3] * other.Elements[3][1];
		NewMatrix.Elements[3][2] = Elements[3][0] * other.Elements[0][2] + Elements[3][1] * other.Elements[1][2] + Elements[3][2] * other.Elements[2][2] + Elements[3][3] * other.Elements[3][2];
		NewMatrix.Elements[3][3] = Elements[3][0] * other.Elements[0][3] + Elements[3][1] * other.Elements[1][3] + Elements[3][2] * other.Elements[2][3] + Elements[3][3] * other.Elements[3][3];

		return NewMatrix;
	}

	void Transpose();
};

struct Vector4
{
	float x, y, z, w;

	Vector4(float x, float y, float z, float w);
	Vector4();

	const Vector4& operator+(const Vector4& other)
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}
	const Vector4& operator-(const Vector4& other)
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}
	const Vector4& operator*(const Vector4& other)
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}
	const Vector4& operator/(const Vector4& other)
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}

	Vector4 operator*(const Matrix4x4& other) 
	{
		Vector4 NewVector;
		NewVector.x = this->x * other.Elements[0][0] + this->y * other.Elements[1][0] + this->z * other.Elements[2][0] + this->w * other.Elements[3][0];
		NewVector.y = this->x * other.Elements[0][1] + this->y * other.Elements[1][1] + this->z * other.Elements[2][1] + this->w * other.Elements[3][1];
		NewVector.z = this->x * other.Elements[0][2] + this->y * other.Elements[1][2] + this->z * other.Elements[2][2] + this->w * other.Elements[3][2];
		NewVector.w = this->x * other.Elements[0][3] + this->y * other.Elements[1][3] + this->z * other.Elements[2][3] + this->w * other.Elements[3][3];

		return NewVector;
	}
	
};