#pragma once
#ifndef NUI_Visual_h__
#define NUI_Visual_h__

#include <vector>

namespace nui
{
	class Visual
	{
	public:
		virtual void AddChild(Visual* child) = 0;
		virtual void RemoveChild(Visual* child) = 0;
	};
}

#endif // NUI_Visual_h__
