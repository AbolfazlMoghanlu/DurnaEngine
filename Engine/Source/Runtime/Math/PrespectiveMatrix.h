#pragma once

#include "Runtime/Math/Matrix.h"

namespace Durna
{
	template <typename T>
	class PrespectiveMatrix : public Matrix<T>
	{
	public:
		PrespectiveMatrix(T HalFOV, T Width, T Height, T MinZ, T MaxZ);

	private:


	};

	template <typename T>
	PrespectiveMatrix<T>::PrespectiveMatrix(T HalfFOV, T Width, T Height, T MinZ, T MaxZ)
		: Matrix<T>(
			Plane<T>(1.0f / Math::Tan(Math::DegreesToRadians(HalfFOV)), 0.0f, 0.0f, 0.0f),
			Plane<T>(0.0f, Width / Math::Tan(Math::DegreesToRadians(HalfFOV)) / Height, 0.0f, 0.0f),
			Plane<T>(0.0f, 0.0f, ((MinZ == MaxZ) ? 1.0f : MaxZ / (MaxZ - MinZ)), 1.0f),
			Plane<T>(0.0f, 0.0f, -MinZ * ((MinZ == MaxZ) ? 1.0f : MaxZ / (MaxZ - MinZ)), 0.0f)
			)
	{	}

}

