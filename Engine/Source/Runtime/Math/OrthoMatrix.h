#pragma once

#include "Runtime/Math/Matrix.h"

namespace Durna
{
	template <typename T>
	class OrthoMatrix : public Matrix<T>
	{
	public:
		OrthoMatrix(T Width, T Height, T ZScale, T ZOffset);

		/** glOrtho function
		 * See https://docs.microsoft.com/en-us/windows/win32/opengl/glortho
		 */
		OrthoMatrix(T Top, T Bottom, T Right, T Left, T FarPlane, T NearPlane);
	};

	template <typename T>
	OrthoMatrix<T>::OrthoMatrix(T Top, T Bottom, T Right, T Left, T FarPlane, T NearPlane)
	{
		T tx = -(Right + Left) / (Right - Left);
		T ty = -(Top + Bottom) / (Top - Bottom);
		T tz = -(FarPlane + NearPlane) / (FarPlane - NearPlane);

		M[0][0] = 2 / (Right - Left);
		M[0][1] = 0;
		M[0][2] = 0;
		M[0][3] = tx;

		M[1][0] = 0;
		M[1][1] = 2 / (Top - Bottom);
		M[1][2] = 0;
		M[1][3] = ty;

		M[2][0] = 0;
		M[2][1] = 0;
		M[2][2] = -2 / (FarPlane - NearPlane);
		M[2][3] = tz;

		M[3][0] = 0;
		M[3][1] = 0;
		M[3][2] = 0;
		M[3][3] = 1;
	}

	template <typename T>
	OrthoMatrix<T>::OrthoMatrix(T Width, T Height, T ZScale, T ZOffset)
		: Matrix<T>(
			Plane<T>((Width != 0.0f) ? (1.0f / Width) : 1.0f, 0.0f, 0.0f, 0.0f),
			Plane<T>(0.0f, (Height != 0.0f) ? (1.0f / Height) : 1.f, 0.0f, 0.0f),
			Plane<T>(0.0f, 0.0f, ZScale, 0.0f),
			Plane<T>(0.0f, 0.0f, ZOffset* ZScale, 1.0f)
			)
	{ }
}