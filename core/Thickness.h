#pragma once
#ifndef Thickness_h__
#define Thickness_h__

struct Thickness
{
	float left;
	float top;
	float right;
	float bottom;

	Thickness()
		: left(0), top(0), right(0), bottom(0)
	{}

	Thickness(float left, float top, float right, float bottom)
		: left(left), top(top), right(right), bottom(bottom)
	{}
};

#endif // Thickness_h__
