#include "LayoutManager.h"

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

	LayoutRequest* LayoutManager::LayoutQueue::Add(Widget* widget)
	{
		LayoutRequest* request = CreateRequest();
		widget->request = request
	}

	void LayoutManager::LayoutQueue::Remove(LayoutRequest* request)
	{

	}

	LayoutRequest* LayoutManager::LayoutQueue::CreateRequest()
	{
		if (m_pocket)
		{
			LayoutRequest* request = m_pocket;
			m_pocket = m_pocket->next;
			request->next = request->prev = nullptr;
			m_pocket_size -= 1;
			return request;
		}
		return new LayoutRequest();
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

	void LayoutManager::UpdateLayout()
	{
		if (m_in_update_layout)
			return;
		m_in_update_layout = true;

		while (m_measure_queue.NotEmpty() || m_arrange_queue.NotEmpty())
		{

		}
	}

	void LayoutManager::AddToMeasureQueue(Widget* widget)
	{
		if (widget->GetMeasureRequest())
			return;
		LayoutRequest* request = m_measure_queue.Add(widget);
		widget->SetMeasureRequest(request);
	}

	void LayoutManager::RemoveFromeMeasureQueue(Widget* widget)
	{
		LayoutRequest* request = widget->GetMeasureRequest();
		if (!request)
			return;
		m_measure_queue.Remove(request);
		widget->SetMeasureRequest(nullptr);
	}

	void LayoutManager::AddToArrangeQueue(Widget* widget)
	{
		if (widget->GetArrangeRequest())
			return;
		LayoutRequest* request = m_arrange_queue.Add(widget);
		widget->SetArrangeRequest(request);
	}

	void LayoutManager::RemoveFromeArrangeQueue(Widget* widget)
	{
		LayoutRequest* request = widget->GetArrangeRequest();
		if (!request)
			return;
		m_arrange_queue.Remove(request);
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
