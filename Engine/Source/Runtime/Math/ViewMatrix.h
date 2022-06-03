#pragma once

#include "Runtime/Math/Matrix.h"

namespace Durna
{
	template<typename T>
	class ViewMatrix : public Matrix<T>
	{
	public:
		ViewMatrix(const Vector3f& Location, const Vector3f& ForwardVector,
			const Vector3f& RightVector, const Vector3f& UpVector);
	};

	template<typename T>
	ViewMatrix<T>::ViewMatrix(const Vector3f& Location, const Vector3f& ForwardVector,
		const Vector3f& RightVector, const Vector3f& UpVector)
	{
		for (int32 RowIndex = 0; RowIndex < 3; RowIndex++)
		{
			M[RowIndex][0] = RowIndex == 0 ? RightVector.X : RowIndex == 1 ? RightVector.Y : RightVector.Z;
			M[RowIndex][1] = RowIndex == 0 ? UpVector.X : RowIndex == 1 ? UpVector.Y : UpVector.Z;
			M[RowIndex][2] = RowIndex == 0 ? ForwardVector.X : RowIndex == 1 ? ForwardVector.Y : ForwardVector.Z;
			M[RowIndex][3] = 0.0f;
		}

		M[3][0] = Vector3f::DotProduct(Location * -1, RightVector);
		M[3][1] = Vector3f::DotProduct(Location * -1, UpVector);
		M[3][2] = Vector3f::DotProduct(Location * -1, ForwardVector);
		M[3][3] = 1.0f;
	}
}