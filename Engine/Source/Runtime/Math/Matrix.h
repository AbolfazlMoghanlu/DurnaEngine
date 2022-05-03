#pragma once

#include "Runtime/Math/Vector3.h"
#include "Plane.h"

namespace Durna
{
	template<typename T>
	class Matrix
	{
	public:
		T M[4][4] = { 0 };

		Matrix(const Plane<T>& InX, const Plane<T>& InY, const Plane<T>& InZ, const Plane<T>& InW);
		Matrix(const Vector3<T>& InX, const Vector3<T>& InY, const Vector3<T>& InZ, const Vector3<T>& InW);

		Matrix();

		static const Matrix Identity;


	private:
	};

	template<typename T>
	Matrix<T>::Matrix()
	{

	}

	template<typename T>
	Matrix<T>::Matrix(const Plane<T>& InX, const Plane<T>& InY, const Plane<T>& InZ, const Plane<T>& InW)
	{
		M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
		M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
		M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
		M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
	}

	template<typename T>
	Matrix<T>::Matrix(const Vector3<T>& InX, const Vector3<T>& InY, const Vector3<T>& InZ, const Vector3<T>& InW)
	{
		M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = 0;
		M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = 0;
		M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = 0;
		M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = 1;
	}

	template<typename T>
	const Matrix<T> Matrix<T>::Identity = Matrix<T>(
		Vector3<int32>(1, 0, 0), Vector3<int32>(0, 1, 0), Vector3<int32>(0, 0, 1));

}

