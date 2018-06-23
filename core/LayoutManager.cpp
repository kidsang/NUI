#include "LayoutManager.h"
#include "widget/Widget.h"

namespace nui
{

	LayoutManager::LayoutQueue::LayoutQueue()
		: m_head(nullptr)
		, m_pocket(nullptr)
		, m_pocket_size(0)
	{
	}

	LayoutManager::LayoutQueue::~LayoutQueue()
	{
		while (m_head)
		{
			LayoutRequest* next = m_head->next;
			delete m_head;
			m_head = next;
		}

		while (m_pocket)
		{
			LayoutRequest* next = m_pocket->next;
			delete m_pocket;
			m_pocket = next;
		}
	}

	LayoutRequest* LayoutManager::LayoutQueue::CreateRequest(Widget* widget)
	{
		if (m_pocket)
		{
			LayoutRequest* request = m_pocket;
			m_pocket = m_pocket->next;
			request->next = request->prev = nullptr;
			request->widget = widget;
			m_pocket_size -= 1;
			return request;
		}
		return new LayoutRequest(widget);
	}

	void LayoutManager::LayoutQueue::ReleaseRequest(LayoutRequest* request)
	{
		if (m_pocket_size < POCKET_CAPACITY)
		{
			m_pocket_size += 1;
			request->widget = nullptr;
			request->prev = nullptr;
			request->next = m_pocket;
			m_pocket = request;
		}
		else
		{
			delete request;
		}
	}

	nui::Widget* LayoutManager::LayoutQueue::GetTopMost()
	{
		Widget* found = nullptr;
		uint32_t tree_level = 0xffffffff;
		for (LayoutRequest* request = m_head; request != nullptr; request = request->next)
		{
			if (request->widget->m_tree_level < tree_level)
			{
				found = request->widget;
				tree_level = found->m_tree_level;
			}
		}
		return found;
	}

	void LayoutManager::UpdateLayout()
	{
		if (m_in_update_layout)
			return;
		m_in_update_layout = true;

		while (m_measure_queue.NotEmpty() || m_arrange_queue.NotEmpty())
		{
			// loop for measure
			while (true)
			{
				Widget* widget = m_measure_queue.GetTopMost();
				if (!widget)
					break;
				widget->Measure(widget->m_previous_available_size);
				RemoveFromeMeasureQueue(widget);
			}

			// loop for arrange
			while (m_measure_queue.IsEmpty())
			{
				Widget* widget = m_arrange_queue.GetTopMost();
				if (!widget)
					break;
				widget->Arrange(widget->m_previous_final_rect);
				RemoveFromeArrangeQueue(widget);
			}
		}
	}

	void LayoutManager::AddToMeasureQueue(Widget* widget)
	{
		if (widget->GetMeasureRequest())
			return;
		LayoutRequest* request = m_measure_queue.CreateRequest(widget);
		widget->SetMeasureRequest(request);
	}

	void LayoutManager::RemoveFromeMeasureQueue(Widget* widget)
	{
		LayoutRequest* request = widget->GetMeasureRequest();
		if (!request)
			return;
		m_measure_queue.ReleaseRequest(request);
		widget->SetMeasureRequest(nullptr);
	}

	void LayoutManager::AddToArrangeQueue(Widget* widget)
	{
		if (widget->GetArrangeRequest())
			return;
		LayoutRequest* request = m_arrange_queue.CreateRequest(widget);
		widget->SetArrangeRequest(request);
	}

	void LayoutManager::RemoveFromeArrangeQueue(Widget* widget)
	{
		LayoutRequest* request = widget->GetArrangeRequest();
		if (!request)
			return;
		m_arrange_queue.ReleaseRequest(request);
		widget->SetArrangeRequest(nullptr);
	}

	void LayoutManager::Initialize()
	{
		if (s_instance)
			return;
		s_instance = new LayoutManager();
	}

	LayoutManager::LayoutManager()
		: m_in_update_layout(false)
	{

	}

	LayoutManager* LayoutManager::s_instance = nullptr;

}
