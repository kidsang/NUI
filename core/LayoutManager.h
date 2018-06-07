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

		explicit LayoutRequest(Widget* widget) : widget(widget), prev(nullptr), next(nullptr) {}
	};

	class LayoutManager
	{
		class LayoutQueue
		{
			const int POCKET_CAPACITY = 100;

		public:
			LayoutQueue();
			~LayoutQueue();
			inline bool IsEmpty() { return m_head == nullptr; }
			inline bool NotEmpty() { return m_head != nullptr; }
			LayoutRequest* CreateRequest(Widget* widget);
			void ReleaseRequest(LayoutRequest* request);
			Widget* GetTopMost();

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
		bool m_in_update_layout; // 是否正处于布局中
		LayoutQueue m_measure_queue;
		LayoutQueue m_arrange_queue;

#pragma region constructor
	public:
		static void Initialize();
		static LayoutManager* Instance() { return s_instance; }
	private:
		LayoutManager();
	private:
		static LayoutManager* s_instance;
#pragma endregion constructor

		friend class Widget;
	};
}

#endif // NUI_LayoutManager_h__
