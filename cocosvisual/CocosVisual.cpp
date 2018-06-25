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

	void CocosVisual::AddRef()
	{
		Ref::AddRef();
	}

	void CocosVisual::DecRef()
	{
		Ref::DecRef();
	}

	void CocosVisual::AddChild(IVisual* child)
	{
		int z_order = (int)m_ccnode->getChildrenCount();
		m_ccnode->addChild(((CocosVisual*)child)->m_ccnode, z_order);
	}

	void CocosVisual::RemoveChild(IVisual* child)
	{
		cocos2d::Node* child_ccnode = ((CocosVisual*)child)->m_ccnode;
		m_ccnode->removeChild(child_ccnode);

		int z_order = child_ccnode->getLocalZOrder();
		for (cocos2d::Node* _child_ccnode : m_ccnode->getChildren())
		{
			int _z_order = _child_ccnode->getLocalZOrder();
			if (_z_order > z_order)
			{ 
				_child_ccnode->setLocalZOrder(_z_order - 1);
			}
		}
	}

	void CocosVisual::AddChildAt(IVisual* child, uint32_t index)
	{
		uint32_t child_count = (uint32_t)m_ccnode->getChildrenCount();
		if (index > child_count)
			index = child_count;

		int z_order = (int)index;
		if (index != child_count)
		{
			for (cocos2d::Node* _child_ccnode : m_ccnode->getChildren())
			{
				int _z_order = _child_ccnode->getLocalZOrder();
				if (_z_order <= z_order)
				{
					_child_ccnode->setLocalZOrder(_z_order + 1);
				}
			}
		}

		m_ccnode->addChild(((CocosVisual*)child)->m_ccnode, z_order);
	}

	void CocosVisual::RemoveChildAt(uint32_t index)
	{
		int z_order = (int)index;

		for (cocos2d::Node* _child_ccnode : m_ccnode->getChildren())
		{
			if (_child_ccnode->getLocalZOrder() == z_order)
			{
				m_ccnode->removeChild(_child_ccnode);
				break;
			}
		}

		for (cocos2d::Node* _child_ccnode : m_ccnode->getChildren())
		{
			int _z_order = _child_ccnode->getLocalZOrder();
			if (_z_order > z_order)
			{ 
				_child_ccnode->setLocalZOrder(_z_order - 1);
			}
		}
	}

	uint32_t CocosVisual::GetChildCount()
	{
		return (uint32_t)m_ccnode->getChildrenCount();
	}

}

