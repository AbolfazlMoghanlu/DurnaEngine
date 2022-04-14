#pragma once

#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)

namespace Durna
{
	class Math
	{
	public:

		static float Mod(float A, float B);
		static float Abs(float A);
		static 	double TruncToDouble(double A);
	};
}