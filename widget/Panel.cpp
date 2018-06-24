#include "Panel.h"

namespace nui
{

	Panel::Panel()
		: m_background_type(BackgroundType::None)
	{

	}

	Panel::~Panel()
	{

	}

	void Panel::AddChild(Widget* child)
	{
		NUI_ASSERT(child != nullptr);
		NUI_ASSERT(child->GetParent() == nullptr);

		m_children.push_back(child);
		child->SetParent(this);

		if (IsAutoWidth() || IsAutoHeight())
			InvalidateMeasure();
	}

	void Panel::RemoveChild(Widget* child)
	{
		NUI_ASSERT(child != nullptr);
		NUI_ASSERT(child->GetParent() == this);

		child->SetParent(nullptr);
		auto iter = std::find(m_children.begin(), m_children.end(), child);
		this->m_children.erase(iter);
	}

	void Panel::SetBackgroundType(BackgroundType type)
	{
		if (m_background_type == type)
			return;
		m_background_type = type;

		switch (type)
		{
		case BackgroundType::None:
			break;
		case BackgroundType::Solid:
			break;
		case BackgroundType::Gradient:
			break;
		case BackgroundType::Image:
			break;
		default:
			break;
		}

	}

	void Panel::SetBackgroundColor(const Color& color)
	{

	}

	Color Panel::GetBackgroundColor() const
	{

	}

	void Panel::SetBackgroundGradient(const Color& start_color, const Color& end_color)
	{

	}

	Color Panel::GetBackgroundGradientStartColor() const
	{

	}

	Color Panel::GetBackgroundGradientEndColor() const
	{

	}

	void Panel::SetBackgroundImage(const std::string& file_name, TextureResType tex_res_type /*= TextureResType::Normal*/)
	{

	}

	Size Panel::DoMeasure(Size available_size)
	{
		Size self_size = Widget::DoMeasure(available_size);
		Size children_available_size = CalcChildrenAvailableSize(*this, self_size);

		for (Widget* child : m_children)
		{
			child->Measure(children_available_size);
		}

		return self_size;
	}

	void Panel::DoArrange(Rect final_rect)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}

