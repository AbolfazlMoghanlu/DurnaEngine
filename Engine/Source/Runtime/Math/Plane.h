#pragma once

#include "Runtime/Math/Vector3.h"

namespace Durna
{
	template<typename T>
	class Plane : public Vector3<T>
	{
	public:
		T W;

		Plane(T InX, T InY, T InZ, T InW);
	};

	template<typename T>
	Plane<T>::Plane(T InX, T InY, T InZ, T InW)
		: Vector3<T>(InX, InY, InZ)
		, W(InW)
	{}

}

