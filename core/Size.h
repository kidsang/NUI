#pragma once
#ifndef NUI_Size_h__
#define NUI_Size_h__

#include <cmath>

struct Size
{
	float width;
	float height;

	const float Eps = 1e-6;

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
};

#endif // NUI_Size_h__
