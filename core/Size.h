#pragma once
#ifndef NUI_Size_h__
#define NUI_Size_h__

#include "MathUtils.h"

namespace nui
{
	struct Size
	{
		float width;
		float height;

		Size()
			: width(0), height(0)
		{}

		Size(float width, float height)
			: width(width), height(height)
		{}

		Size& operator = (const Size& other)
		{
			this->width = other.width;
			this->height = other.height;
			return *this;
		}

		bool operator == (const Size& other) const
		{
			return MathUtils::AreClose(width, other.width) && MathUtils::AreClose(height, other.height);
		}

		bool operator != (const Size& other) const
		{
			return !(*this == other);
		}
	};
}

#endif // NUI_Size_h__
