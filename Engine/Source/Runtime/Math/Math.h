#pragma once

#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)
#define PI 3.14159

namespace Durna
{
	class Math
	{
	public:

		static float Mod(float A, float B);
		static float Abs(float A);
		static 	double TruncToDouble(double A);

		template<typename T>
		static T DegreesToRadians(T const& Degrees)
		{
			return Degrees * (PI / 180.f);
		}

		static float Sin(float Value)
		{
			return sinf(Value);
		}

		static double Sin(double Value)
		{
			return sin(Value);
		}

		static float Cos(float Value)
		{
			return cosf(Value);
		}

		static double Cos(double Value)
		{
			return cos(Value);
		}

		static void SinCos(float* SinRes, float* CosRes, float Value)
		{
			*SinRes = Sin(Value);
			*CosRes = Cos(Value);
		}
	};
}