#pragma once
#ifndef NUI_Rect_h__
#define NUI_Rect_h__

#include "MathUtils.h"
#include "Size.h"

namespace nui
{
	struct Rect
	{
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

		Size Size() const
		{
			return nui::Size(width, height);
		}

		bool operator == (const Rect& other) const
		{
			return MathUtils::AreClose(x, other.x)
				&& MathUtils::AreClose(y, other.y)
				&& MathUtils::AreClose(width, other.width)
				&& MathUtils::AreClose(height, other.height);
		}

		bool operator != (const Rect& other) const
		{
			return !(*this == other);
		}
	};
}

#endif // NUI_Rect_h__
