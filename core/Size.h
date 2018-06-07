#pragma once
#ifndef NUI_Size_h__
#define NUI_Size_h__

#include <cmath>

namespace nui
{
	struct Size
	{
		const float Eps = 1e-7; // 对于一个界面库来说，这个精度足够了

		float width;
		float height;

		Size()
			: width(0), height(0)
		{}

		Size(float width, float height)
			: width(width), height(height)
		{}

		bool operator == (const Size& other) const
		{
			return fabs(width - other.width) < Eps && fabs(height - other.height) < Eps;
		}

		bool operator != (const Size& other) const
		{
			return !(*this == other);
		}
	};
}

#endif // NUI_Size_h__
