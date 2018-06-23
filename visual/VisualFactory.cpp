#include "VisualFactory.h"
#include "CocosVisualFactory.h"

namespace nui
{

	void VisualFactory::Initialize()
	{
		if (s_instance)
			return;
		s_instance = new CocosVisualFactory();
	}

	VisualFactory* VisualFactory::s_instance;

}

