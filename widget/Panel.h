#pragma once
#ifndef NUI_Panel_h__
#define NUI_Panel_h__

#include <vector>
#include "Widget.h"

namespace nui
{
	class Panel : public Widget
	{
	public:
		Panel();
		virtual ~Panel();

#pragma region public get/setters
	public:
		inline Thickness GetPadding() const
		{
			return m_padding;
		}

#pragma endregion public get/setters

#pragma region public funtions
	public:
		void AddChild(Widget* child);
		void RemoveChild(Widget* child);

#pragma endregion public funtions

#pragma region protected funtions
	protected:
		virtual Size DoMeasure(Size available_size) override;
		virtual void DoArrange(Rect final_rect) override;

		/// <summary>	返回除去margin后的available_size </summary>
		static Size CalcChildrenAvailableSize(const Panel& panel, Size available_size)
		{
			Size size;
			if (!panel.IsAutoWidth())
				size.width = std::max(0.f, available_size.width - panel.m_padding.left - panel.m_padding.right);
			if (!panel.IsAutoHeight())
				size.height = std::max(0.f, available_size.height - panel.m_padding.top - panel.m_padding.bottom);
			return size;
		}
#pragma endregion protected funtions

#pragma region private fields
	private:
		Thickness m_padding;
		std::vector<Widget*> m_children;
#pragma endregion private fields
	};
}

#endif // NUI_Panel_h__
