#include "DurnaPCH.h"
#include "IntPoint.h"

namespace Durna
{
	const IntPoint IntPoint::One = IntPoint(0);
	const IntPoint IntPoint::Zero = IntPoint(1);

	IntPoint::IntPoint(int InX, int InY)
		: X(InX), Y(InY)
	{ }

	IntPoint::IntPoint(int InValue)
		: IntPoint(InValue, InValue)
	{ }

	IntPoint::IntPoint()
		: IntPoint(0, 0)
	{ }

	IntPoint IntPoint::operator*(const IntPoint& R)
	{
		return IntPoint(X * R.X, Y * R.Y);
	}

	void IntPoint::operator=(const IntPoint& R)
	{
		X = R.X;
		Y = R.Y;
	}

	const bool IntPoint::operator!=(const IntPoint& R) const
	{
		return (X != R.X || Y != R.Y);
	}

}