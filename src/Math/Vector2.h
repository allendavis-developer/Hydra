#pragma once

namespace Hydra {
	template<typename T>
	struct Vector2
	{
		T X, Y;

		Vector2()
			: X(0), Y(0)
		{

		}

		Vector2(T x, T y)
			: X(x), Y(y)
		{

		}
	};
}