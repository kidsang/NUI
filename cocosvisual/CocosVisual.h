#pragma once
#ifndef NUI_CocosVisual_h__
#define NUI_CocosVisual_h__

#include "cocos2d.h"
#include "visual/IVisual.h"
#include "core/Ref.h"

namespace nui
{
	class CocosVisual : public IVisual, public Ref
	{
	public:
		CocosVisual();
		explicit CocosVisual(cocos2d::Node* ccnode);
		~CocosVisual();

		inline cocos2d::Node* GetCCNode() const
		{
			return m_ccnode;
		}

		virtual void AddRef();

		virtual void DecRef();

		virtual void AddChild(IVisual* child);

		virtual void RemoveChild(IVisual* child);

		virtual void AddChildAt(IVisual* child, uint32_t index);

		virtual void RemoveChildAt(uint32_t index);

		virtual uint32_t GetChildCount();

	private:
		cocos2d::Node* m_ccnode;
	};
}

#endif // NUI_CocosVisual_h__
