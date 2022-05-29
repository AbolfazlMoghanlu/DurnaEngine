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


	public:
		static const IntPoint Zero;
		static const IntPoint One;
	};
}

