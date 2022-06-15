#pragma once

#include "Runtime/Math/Matrix.h"

namespace Durna
{
	template <typename T>
	class OrthoMatrix : public Matrix<T>
	{
	public:
		OrthoMatrix(T Width, T Height, T FarPlane, T NearPlane);

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
		M[1][3] = tz;

		M[2][0] = 0;
		M[2][1] = 0;
		M[2][2] = -2 / (FarPlane - NearPlane);
		M[2][3] = ty;

		M[3][0] = 0;
		M[3][1] = 0;
		M[3][2] = 0;
		M[3][3] = 1;
	}

	template <typename T>
	OrthoMatrix<T>::OrthoMatrix(T Width, T Height, T FarPlane, T NearPlane)
	{
		const T ZScale = 1.0f / (FarPlane - NearPlane);
		const T ZOffset = -NearPlane;

		M[0][0] = (Width) ? (1.0f / Width) : 1.0f; 
		M[0][1] = 0.0f; 
		M[0][2] = 0.0f; 
		M[0][3] = 0.0f; 

		M[1][0] = 0.0f; 
		M[1][1] = (Height) ? (1.0f / Height) : 1.0f;
		M[1][2] = 0.0f; 
		M[1][3] = 0.0f; 

		M[2][0] = 0.0f; 
		M[2][1] = 0.0f; 
		M[2][2] = ZScale;
		M[2][3] = 0.0f; 

		M[3][0] = 0.0f; 
		M[3][1] = 0.0f; 
		M[3][2] = ZOffset * ZScale;
		M[3][3] = 1.0f;
	}
}