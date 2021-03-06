#pragma once
#ifndef NUI_Panel_h__
#define NUI_Panel_h__

#include <vector>
#include "Widget.h"
#include "core/Color.h"

namespace nui
{
	struct IColorVisual;
	struct IGradientVisual;
	struct ISpriteVisual;

	class Panel : public Widget
	{
	public:

		/// <summary>	������ʽ </summary>
		enum class BackgroundType
		{
			/// <summary>	�ޱ�����Ĭ��ֵ </summary>
			None,

			/// <summary>	��ɫ���� </summary>
			Solid,

			/// <summary>	���䱳�� </summary>
			Gradient,

			/// <summary>	ͼƬ���� </summary>
			Image,
		};

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

		void SetBackgroundType(BackgroundType type);

		inline BackgroundType GetBackgroundType() const
		{
			return m_background_type;
		}

		void SetBackgroundColor(const Color& color);

		Color GetBackgroundColor() const;

		void SetBackgroundGradient(const Color& start_color, const Color& end_color);

		Color GetBackgroundGradientStartColor() const;

		Color GetBackgroundGradientEndColor() const;

		void SetBackgroundImage(const std::string& file_name, TextureResType tex_res_type = TextureResType::Normal);


#pragma endregion public funtions

#pragma region protected funtions
	protected:
		virtual Size DoMeasure(Size available_size) override;
		virtual void DoArrange(Rect final_rect) override;

		/// <summary>	���س�ȥmargin���available_size </summary>
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

		BackgroundType m_background_type;
		IColorVisual* m_background_color_visual;
		IGradientVisual* m_background_gradient_visual;
		ISpriteVisual* m_background_sprite_visual;

#pragma endregion private fields
	};
}

#endif // NUI_Panel_h__
