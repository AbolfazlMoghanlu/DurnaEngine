#pragma once

#include "Runtime/Math/Matrix.h"

namespace Durna
{
	template <typename T>
	class OrthoMatrix : public Matrix<T>
	{
	public:
		OrthoMatrix(T Width, T Height, T ZScale, T ZOffset);
	};

	template <typename T>
	OrthoMatrix<T>::OrthoMatrix(T Width, T Height, T ZScale, T ZOffset)
		: Matrix<T>(
			Plane<T>((Width != 0.0f) ? (1.0f / Width) : 1.0f, 0.0f, 0.0f, 0.0f),
			Plane<T>(0.0f, (Height != 0.0f) ? (1.0f / Height) : 1.f, 0.0f, 0.0f),
			Plane<T>(0.0f, 0.0f, ZScale, 0.0f),
			Plane<T>(0.0f, 0.0f, ZOffset* ZScale, 1.0f)
			)
	{}


}

