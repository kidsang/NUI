#pragma once
#ifndef NUI_MathUtils_h__
#define NUI_MathUtils_h__

#include <cmath>

namespace nui
{
	struct MathUtils
	{
		static constexpr float Eps = 1e-7f; // ����һ���������˵����������㹻��

		static inline bool AreClose(float a, float b)
		{
			return fabs(a - b) < Eps;
		}
	};

}

#endif // NUI_MathUtils_h__
