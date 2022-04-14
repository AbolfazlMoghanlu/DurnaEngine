#pragma once

namespace Durna
{
	template<typename T>
	struct Vector3
	{
		static_assert(std::is_floating_point_v<T>, "T must be floating point");

		T X;
		T Y;
		T Z;

		/** (0, 0, 0) */
		static const Vector3<T> ZeroVector;

		/** (1, 1, 1) */
		static const Vector3<T> OneVector;

		Vector3() : X(0), Y(0), Z(0) {};
		Vector3(T InF) : X(InF), Y(InF), Z(InF) {};
		Vector3(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ) {};
		
		const Vector3<T> operator+(Vector3<T> Vec3) const
		{
			return Vector3<T>(X + Vec3.X, Y + Vec3.Y, Z + Vec3.Z);
		}

		void operator+=(Vector3<T> Vec3)
		{
			X += Vec3.X;
			Y += Vec3.Y;
			Z += Vec3.Z;
		}

		const void operator*(Vector3<T> Vec3) const
		{
			return Vector3<T>(X * Vec3.X, Y * Vec3.Y, Z * Vec3.Z);
		}

		const Vector3 operator*(float f) const
		{
			return Vector3<T>(X * f, Y * f, Z * f);
		}
	};


	template<typename T>
	const Vector3<T> Vector3<T>::ZeroVector = Vector3<T>(0);

	template<typename T>
	const Vector3<T> Vector3<T>::OneVector = Vector3<T>(1);


	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
}


