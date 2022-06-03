#pragma once
 
namespace Durna
{
	template<typename T>
	struct Vector2
	{
		static_assert(std::is_floating_point_v<T>, "T must be floating point.");

		T X;
		T Y;

		/** (0, 0, 0) */
		static const Vector2<T> ZeroVector;

		/** (1, 1, 1) */
		static const Vector2<T> OneVector;

		Vector2() : X(0), Y(0) {};
		Vector2(T InF) : X(InF), Y(InF) {};
		Vector2(T InX, T InY) : X(InX), Y(InY) {};

		Vector2<T> operator-(const Vector2<T>& R);
	};

	template<typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2<T>& R)
	{
		return Vector2<T>(X - R.X, Y - R.Y);
	}

	template<typename T>
	const Vector2<T> Vector2<T>::ZeroVector = Vector2<T>(0, 0);

	template<typename T>
	const Vector2<T> Vector2<T>::OneVector = Vector2<T>(1, 1);

	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
}
