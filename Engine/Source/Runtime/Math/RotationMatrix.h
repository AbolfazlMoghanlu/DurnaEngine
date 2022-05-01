#pragma once

#include "Runtime/Math/Matrix.h"
#include "Runtime/Math/Rotator.h"
#include "Runtime/Math/Math.h"

namespace Durna
{
	template<typename T>
	class RotationMatrix : public Matrix<T>
	{
	public:
		RotationMatrix(const Rotator<T>& InRotator);

	private:
	

	};

	template<typename T>
	RotationMatrix<T>::RotationMatrix(const Rotator<T>& InRotator)
	{
		Vector3<T> Angles = Vector3<T>(InRotator.Pitch, InRotator.Yaw, InRotator.Roll);
		Angles *= (T)PI_ON_180_DEGREES;

		const T SP = Math::Sin(Angles.X);
		const T SY = Math::Sin(Angles.Y);
		const T SR = Math::Sin(Angles.Z);
		const T CP = Math::Cos(Angles.X);
		const T CY = Math::Cos(Angles.Y);
		const T CR = Math::Cos(Angles.Z);

		M[0][0] = CP * CY;
		M[0][1] = CP * SY;
		M[0][2] = SP;
		M[0][3] = 0.0f;

		M[1][0] = SR * SP * CY - CR * SY;
		M[1][1] = SR * SP * SY + CR * CY;
		M[1][2] = -SR * CP;
		M[1][3] = 0.0f;

		M[2][0] = -(CR * SP * CY + SR * SY);
		M[2][1] = CY * SR - CR * SP * SY;
		M[2][2] = CR * CP;
		M[2][3] = 0.0f;

		M[3][0] = 0;
		M[3][1] = 0;
		M[3][2] = 0;
		M[3][3] = 1.f;
	}

}

