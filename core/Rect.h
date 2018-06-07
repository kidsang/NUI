#pragma once
#ifndef NUI_Rect_h__
#define NUI_Rect_h__

#include <cmath>

namespace nui
{
	struct Rect
	{
		const float Eps = 1e-7; // 对于一个界面库来说，这个精度足够了

		float x;
		float y;
		float width;
		float height;


		Rect()
			: x(0), y(0), width(0), height(0)
		{}

		Rect(float x, float y, float width, float height)
			: x(x), y(y), width(width), height(height)
		{}

		float Left() const
		{
			return x;
		}

		float Top() const
		{
			return y;
		}

		float Right() const
		{
			return x + width;
		}

		float Bottom() const
		{
			return y + height;
		}

		bool operator == (const Rect& other) const
		{
			return fabs(x - other.x) < Eps && fabs(y - other.y) < Eps
				&& fabs(width - other.width) < Eps && fabs(height - other.height) < Eps;
		}

		bool operator != (const Rect& other) const
		{
			return !(*this == other);
		}
	};
}

#endif // NUI_Rect_h__
