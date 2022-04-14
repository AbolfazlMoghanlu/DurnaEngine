#pragma once

#include "Runtime/Math/Math.h"

namespace Durna
{
	template<typename T>
	class Rotator
	{
	public:

		T Pitch;
		T Yaw;
		T Roll;

		Rotator() : Pitch(0), Yaw(0), Roll(0) {};
		Rotator<T>(T F) : Pitch(F), Yaw(F), Roll(F) {};
		Rotator<T>(T InPitch, T InYaw, T InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {};

		/** (0, 0, 0) */
		static const Rotator<T> ZeroRotator;

		Rotator<T> operator+(Rotator<T> R)
		{
			return Rotator<T>(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll);
		}

		Rotator<T> operator*(Rotator<T> R)
		{
			return Rotator<T>(Pitch * R.Pitch, Yaw * R.Yaw, Roll * R.Roll);
		}

		const Rotator<T> operator*(float F) const
		{
			return Rotator<T>(Pitch * F, Yaw * F, Roll * F);
		}

		static Rotator<T> CombineRotators(Rotator<T> R1, Rotator<T> R2)
		{
			return Clamp(R1 + R2);
		}

		static Rotator<T> Clamp(Rotator<T>& R)
		{
			return Rotator<T>(ClampAxis(R.Pitch), ClampAxis(R.Yaw), ClampAxis(R.Roll));
		}

		static T ClampAxis(T Angle)
		{
			Angle = Math::Mod(Angle, T(360.0));

			if (Angle < T(0.0))
			{
				Angle += T(360.0);
			}

			return Angle;
		}

		static T NormalizeAxis(T Angle)
		{
			Angle = ClampAxis(Angle);

			if (Angle > T(180.0))
			{
				Angle -= T(360.0);
			}

			return Angle;
		}
	};

	template<typename T>
	const Rotator<T> Rotator<T>::ZeroRotator = Rotator(0, 0, 0);

	typedef Rotator<float> Rotatorf;
	typedef Rotator<double> Rotatord;
}