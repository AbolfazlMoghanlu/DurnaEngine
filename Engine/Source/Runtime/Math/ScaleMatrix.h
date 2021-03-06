#pragma once

#include "Runtime/Math/Matrix.h"

namespace Durna
{
	template <typename T>
	class ScaleMatrix : public Matrix<T>
	{
	public:
		ScaleMatrix(const Vector3<T>& InScale);
	};

	template <typename T>
	ScaleMatrix<T>::ScaleMatrix(const Vector3<T>& InScale)
	{
		M[0][0] = InScale.X;
		M[0][1] = 0;
		M[0][2] = 0;
		M[0][3] = 0;

		M[1][0] = 0;
		M[1][1] = InScale.Y;
		M[1][2] = 0;
		M[1][3] = 0;

		M[2][0] = 0;
		M[2][1] = 0;
		M[2][2] = InScale.Z;
		M[2][3] = 0;

		M[3][0] = 0;
		M[3][1] = 0;
		M[3][2] = 0;
		M[3][3] = 1;
	}

}


