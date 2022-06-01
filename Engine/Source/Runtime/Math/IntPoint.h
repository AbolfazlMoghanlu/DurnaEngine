#pragma once

namespace Durna
{
	struct IntPoint
	{
	public:
		int X;
		int Y;

		IntPoint(int InX, int InY);
		IntPoint(int InValue);
		IntPoint();

		void operator=(const IntPoint& R);
		const bool operator!=(const IntPoint& R) const;

	public:
		static const IntPoint Zero;
		static const IntPoint One;
	};
}

