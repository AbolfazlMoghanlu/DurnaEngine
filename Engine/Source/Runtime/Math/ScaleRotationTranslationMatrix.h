#pragma once

#include "Runtime/Math/Math.h"
#include "Runtime/Math/Matrix.h"
#include "Runtime/Math/Vector3.h"
#include "Runtime/Math/Rotator.h"

namespace Durna
{
	template <typename T>
	class ScaleRotationTranslationMatrix : public Matrix<T>
	{
	public:
		ScaleRotationTranslationMatrix(const Vector3<T>& Scale, const Rotator<T>& Rotation, const Vector3<T>& Translation);

	private:
	};

	template <typename T>
	ScaleRotationTranslationMatrix<T>::ScaleRotationTranslationMatrix(const Vector3<T>& Scale, const Rotator<T>& Rotation, const Vector3<T>& Translation)
	{
		Vector3<T> Angles = Vector3<T>(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
		Angles *= (T)PI_ON_180_DEGREES;

		const T SP = Math::Sin(Angles.X);
		const T SY = Math::Sin(Angles.Y);
		const T SR = Math::Sin(Angles.Z);
		const T CP = Math::Cos(Angles.X);
		const T CY = Math::Cos(Angles.Y);
		const T CR = Math::Cos(Angles.Z);

		M[0][0] = (CP * CY) * Scale.X;
		M[0][1] = (CP * SY) * Scale.X;
		M[0][2] = (SP)*Scale.X;
		M[0][3] = 0.f;

		M[1][0] = (SR * SP * CY - CR * SY) * Scale.Y;
		M[1][1] = (SR * SP * SY + CR * CY) * Scale.Y;
		M[1][2] = (-SR * CP) * Scale.Y;
		M[1][3] = 0.f;

		M[2][0] = (-(CR * SP * CY + SR * SY)) * Scale.Z;
		M[2][1] = (CY * SR - CR * SP * SY) * Scale.Z;
		M[2][2] = (CR * CP) * Scale.Z;
		M[2][3] = 0.f;

		M[3][0] = Translation.X;
		M[3][1] = Translation.Y;
		M[3][2] = Translation.Z;
		M[3][3] = 1.f;
	}

}

