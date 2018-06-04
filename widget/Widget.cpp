#include "Widget.h"

namespace nui
{
	Widget::Widget()
		: m_visibility(Visibility::Visible)
		, m_width(0)
		, m_height(0)
		//, m_min_width(0)
		//, m_min_height(0)
		//, m_max_width(0)
		//, m_max_height(0)
		, m_actual_width(0)
		, m_actual_height(0)
		, m_horizontal_alignment(HorizontalAlignment::Stretch)
		, m_vertical_alignment(VerticalAlignment::Stretch)
		, m_parent(nullptr)
	{
	}

	Widget::~Widget()
	{

	}
}

