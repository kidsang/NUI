#include "Widget.h"

namespace nui
{
	Widget::Widget()
		: m_visibility(Visibility::Visible)
		, m_horizontal_alignment(HorizontalAlignment::Stretch)
		, m_vertical_alignment(VerticalAlignment::Stretch)
		, m_parent(nullptr)
		, m_tree_level(0)
		, m_measure_request(nullptr)
		, m_arrange_request(nullptr)
	{
	}

	Widget::~Widget()
	{

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

	void Widget::Measure(Size available_size)
	{
		if (!IsMeasureDirty() && m_previous_available_size == available_size)
			return;

		Size prev_size = m_actual_size;
		Size actual_size = DoMeasure(available_size);
		//if (m_actual_size == actual_size)

		InvalidateArrange();
	}

}

