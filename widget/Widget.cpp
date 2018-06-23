#include "Widget.h"
#include "visual/CocosVisualFactory.h"

namespace nui
{
	Widget::Widget()
		: m_visibility(Visibility::Visible)
		, m_horizontal_alignment(HorizontalAlignment::Stretch)
		, m_vertical_alignment(VerticalAlignment::Stretch)
		, m_parent(nullptr)
		, m_visual(nullptr)
		, m_tree_level(0)
		, m_measure_request(nullptr)
		, m_arrange_request(nullptr)
	{
	}

	Widget::~Widget()
	{
		if (m_visual)
		{
			delete m_visual;
			m_visual = nullptr;
		}
	}

	void Widget::SetSize(float width, float height)
	{
		if (MathUtils::AreClose(width, m_size.width) && MathUtils::AreClose(height, m_size.height))
			return;

		m_size.width = width;
		m_size.height = height;
		SetInternalFlag(InternalFlags::PercentageWidth, false);
		SetInternalFlag(InternalFlags::PercentageHeight,false);
		InvalidateMeasure();
	}

	void Widget::SetSize(const Size& size)
	{
		SetSize(size.width, size.height);
	}

	void Widget::SetAutoSize()
	{
		if (IsAutoWidth() && IsAutoHeight())
			return;

		m_size.width = -1;
		m_size.height = -1;
		SetInternalFlag(InternalFlags::PercentageWidth, false);
		SetInternalFlag(InternalFlags::PercentageHeight,false);
		InvalidateMeasure();
	}

	void Widget::SetPercentageSize(float percent_width, float percent_height)
	{
		if (IsPercentageWidth() && MathUtils::AreClose(percent_width, m_size.width)
			&& IsPercentageHeight() && MathUtils::AreClose(percent_height, m_size.height))
			return;

		m_size.width = percent_width;
		m_size.height = percent_height;
		SetInternalFlag(InternalFlags::PercentageWidth, true);
		SetInternalFlag(InternalFlags::PercentageHeight, true);
		InvalidateMeasure();
	}

	void Widget::SetPercentageSize(const Size& percent_size)
	{
		SetPercentageSize(percent_size.width, percent_size.height);
	}

	void Widget::SetWidth(float value)
	{
		if (MathUtils::AreClose(value, m_size.width))
			return;

		m_size.width = value;
		SetInternalFlag(InternalFlags::PercentageWidth, false);
		InvalidateMeasure();
	}

	void Widget::SetAutoWidth()
	{
		if (IsAutoWidth())
			return;

		m_size.width = -1;
		SetInternalFlag(InternalFlags::PercentageWidth, false);
		InvalidateMeasure();
	}

	void Widget::SetPercentageWidth(float value)
	{
		if (IsPercentageWidth() && MathUtils::AreClose(value, m_size.width))
			return;

		m_size.width = value;
		SetInternalFlag(InternalFlags::PercentageWidth, true);
		InvalidateMeasure();
	}

	void Widget::SetHeight(float value)
	{
		if (MathUtils::AreClose(value, m_size.height))
			return;

		m_size.height = value;
		SetInternalFlag(InternalFlags::PercentageHeight,false);
		InvalidateMeasure();
	}

	void Widget::SetAutoHeight()
	{
		if (IsAutoHeight())
			return;

		m_size.height = -1;
		SetInternalFlag(InternalFlags::PercentageHeight,false);
		InvalidateMeasure();
	}

	void Widget::SetPercentageHeight(float value)
	{
		if (IsPercentageHeight() && MathUtils::AreClose(value, m_size.height))
			return;

		m_size.height = value;
		SetInternalFlag(InternalFlags::PercentageHeight, true);
		InvalidateMeasure();
	}

	void Widget::Measure(Size available_size)
	{
		if (!IsMeasureDirty() && m_previous_available_size == available_size)
			return;

		InvalidateArrange();

		Size prev_size = m_actual_size;
		m_actual_size = DoMeasure(available_size);
		SetMeasureDirty(false);

		if (!IsMeasureDuringArrange() && m_actual_size != prev_size)
		{
			if (m_parent)
			{
				m_parent->OnChildSizeChanged(this);
			}
		}
	}

	void Widget::Arrange(Rect final_rect)
	{
		if (IsMeasureDirty())
		{
			SetMeasureDuringArrange(true);
			Measure(final_rect.Size());
			SetMeasureDuringArrange(false);
		}

		if (!IsArrangeDirty() && m_previous_final_rect == final_rect)
			return;

		DoArrange(final_rect);
		SetArrangeDirty(false);
	}

	void Widget::InvalidateMeasure()
	{
		if (IsMeasureDirty())
			return;
		SetMeasureDirty(true);
		LayoutManager::Instance()->AddToMeasureQueue(this);
	}

	void Widget::InvalidateArrange()
	{
		if (IsArrangeDirty())
			return;
		SetArrangeDirty(true);
		LayoutManager::Instance()->AddToArrangeQueue(this);
	}

	void Widget::SetParent(Widget* parent)
	{
		if (m_parent == parent)
			return;

		if (m_parent)
			m_parent->m_visual->RemoveChild(m_visual);

		if (parent)
			parent->m_visual->AddChild(m_visual);

		m_parent = parent;

		if (m_parent && (IsPercentageWidth() || IsPercentageHeight()))
		{
			InvalidateMeasure();
		}
	}

	Size Widget::DoMeasure(Size available_size)
	{
		Size self_available_size = CalcSelfAvailableSize(*this, available_size);
		Size desired_size = m_size;

		if (IsPercentageWidth())
		{
			desired_size.width *= self_available_size.width;
		}

		if (IsPercentageHeight())
		{
			desired_size.height *= self_available_size.height;
		}

		return desired_size;
	}

	void Widget::DoArrange(Rect final_rect)
	{

	}

	void Widget::OnChildSizeChanged(Widget* child)
	{
		InvalidateMeasure();
	}

	void Widget::InitVisual()
	{
		NUI_ASSERT(!m_visual);
		m_visual = CocosVisualFactory::Instance()->CreateEmpty();
	}

}

