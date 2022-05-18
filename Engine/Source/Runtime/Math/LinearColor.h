#pragma once

namespace Durna
{
	class LinearColor
	{
	public:
		float R, G, B, A;

		LinearColor() : R(0), G(0), B(0), A(255) {};
		LinearColor(float InInt) : R(InInt), G(InInt), B(InInt), A(255) {};
		LinearColor(float InR, float InG, float InB, float InA) : R(InR), G(InG), B(InB), A(InA) {};

		static LinearColor const Black;
		static LinearColor const White;

	protected:

	private:

	};
}