#pragma once

#include "Runtime/Math/Matrix.h"

namespace Durna
{
	template<typename T>
	class TranslationMatrix : public Matrix<T>
	{
	public:
		TranslationMatrix(const Vector3<T>& Delta);

	};

	template<typename T>
	TranslationMatrix<T>::TranslationMatrix(const Vector3<T>& Delta)
		: Matrix<T>(
			Plane<T>(1,			0,			 0,			0),
			Plane<T>(0,			1,			 0,			0),
			Plane<T>(0,			0,			 1,			0),
			Plane<T>(Delta.X,	Delta.Y,	 Delta.Z,	1)
			)
	{

	}

}

