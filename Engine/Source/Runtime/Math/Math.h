#pragma once

#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)
#define PI 3.14159
#define PI_ON_180_DEGREES 0.0174532778 // PI / 180

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
			return Degrees * (T)PI_ON_180_DEGREES;
		}

		template<typename T>
		static T Clamp(T Value, T Min, T Max)
		{
			return (Value < Min) ? Min : (Value < Max) ? Value : Max;
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

		static float Tan(float Value)
		{
			return tanf(Value);
		}

		static bool IsNearlyEqual(float A, float B, float Telorance = 0.001f);
	};
}