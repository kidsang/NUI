#pragma once
#ifndef NUI_LayoutManager_h__
#define NUI_LayoutManager_h__

#include <list>
#include "widget/Widget.h"

namespace nui
{
	struct LayoutRequest
	{
		Widget* widget;
		LayoutRequest* prev;
		LayoutRequest* next;

		LayoutRequest() : widget(nullptr), prev(nullptr), next(nullptr) {}
	};

	class LayoutManager
	{
		class LayoutQueue
		{
			const int POCKET_CAPACITY = 100;

		public:
			LayoutQueue();
			~LayoutQueue();
			LayoutRequest* Add(Widget* widget);
			void Remove(LayoutRequest* request);
			inline bool IsEmpty() { return m_head == nullptr; }
			inline bool NotEmpty() { return m_head != nullptr; }

		private:
			LayoutRequest* CreateRequest();
			void ReleaseRequest(LayoutRequest* request);

		private:
			LayoutRequest* m_head;
			LayoutRequest* m_pocket;
			int m_pocket_size;
		};

	public:
		void UpdateLayout();

	private:
		//Widget* GetTopMost
		void AddToMeasureQueue(Widget* widget);
		void RemoveFromeMeasureQueue(Widget* widget);
		void AddToArrangeQueue(Widget* widget);
		void RemoveFromeArrangeQueue(Widget* widget);

	private:
		bool m_in_update_layout; // �Ƿ������ڲ�����
		LayoutQueue m_measure_queue;
		LayoutQueue m_arrange_queue;
		//std::list<Widget*> m_measure_queue;
		//std::list<Widget*> m_arrange_queue;

#pragma region constructor
	public:
		static void Initialize();
		static LayoutManager* Instance() { return s_instance; }
	private:
		LayoutManager();
	private:
		static LayoutManager* s_instance;
#pragma endregion constructor
	};
}

#endif // NUI_LayoutManager_h__