#include "nui.h"

#include "core/LayoutManager.h"
#include "visual/VisualFactory.h"

namespace nui
{
	void NUIInitialize()
	{
		LayoutManager::Initialize();
		VisualFactory::Initialize();
	}
}

