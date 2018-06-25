#include "VisualFactory.h"
#include "cocosvisual/CocosVisualFactory.h"

namespace nui
{

	void VisualFactory::Initialize()
	{
		if (s_instance)
			return;

		// 使用cocos作为底层渲染库
		s_instance = new CocosVisualFactory();
	}

	VisualFactory* VisualFactory::s_instance;

}

