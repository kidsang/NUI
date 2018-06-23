#pragma once
#ifndef NUI_MathUtils_h__
#define NUI_MathUtils_h__

#include <cmath>

namespace nui
{
	struct MathUtils
	{
		static constexpr float Eps = 1e-7f; // 对于一个界面库来说，这个精度足够了

		static inline bool AreClose(float a, float b)
		{
			return fabs(a - b) < Eps;
		}
	};

}

#endif // NUI_MathUtils_h__
