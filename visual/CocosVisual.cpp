#include "CocosVisual.h"

namespace nui
{

	CocosVisual::CocosVisual()
	{
		m_ccnode = cocos2d::Node::create();
		m_ccnode->retain();
	}

	CocosVisual::CocosVisual(cocos2d::Node* ccnode)
		: m_ccnode(ccnode)
	{
		if (ccnode)
			ccnode->retain();
	}

	CocosVisual::~CocosVisual()
	{
		if (m_ccnode)
		{
			m_ccnode->release();
			m_ccnode = nullptr;
		}
	}

	void CocosVisual::AddChild(Visual* child)
	{
		m_ccnode->addChild(((CocosVisual*)child)->m_ccnode);
	}

	void CocosVisual::RemoveChild(Visual* child)
	{
		m_ccnode->removeChild(((CocosVisual*)child)->m_ccnode);
	}

}

