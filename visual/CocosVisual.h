#pragma once
#ifndef NUI_CocosVisual_h__
#define NUI_CocosVisual_h__

#include "cocos2d.h"
#include "Visual.h"

namespace nui
{
	class CocosVisual : public Visual
	{
	public:
		CocosVisual();
		explicit CocosVisual(cocos2d::Node* ccnode);
		~CocosVisual();

		inline cocos2d::Node* GetCCNode() const
		{
			return m_ccnode;
		}

		virtual void AddChild(Visual* child);

		virtual void RemoveChild(Visual* child);

		virtual void AddChildAt(Visual* child, uint32_t index);

		virtual void RemoveChildAt(uint32_t index);

		virtual uint32_t GetChildCount();

	private:
		cocos2d::Node* m_ccnode;
	};
}

#endif // NUI_CocosVisual_h__
