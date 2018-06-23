#pragma once
#ifndef NUI_CocosVisualFactory_h__
#define NUI_CocosVisualFactory_h__

#include "VisualFactory.h"

namespace nui
{
	class CocosVisualFactory : public VisualFactory
	{
	public:
		virtual Visual* CreateEmpty();

	};
}

#endif // NUI_CocosVisualFactory_h__
