#pragma once
#ifndef NUI_Widget_h__
#define NUI_Widget_h__

#include <string>
#include <vector>
#include <bitset>
#include <list>
#include <algorithm>
#include "core/Assert.h"
#include "core/Enums.h"
#include "core/Size.h"
#include "core/Rect.h"
#include "core/Thickness.h"
#include "core/Ref.h"
#include "core/LayoutManager.h"
#include "visual/IVisual.h"

namespace nui
{
	class Widget : public Ref
	{
		enum class InternalFlags;

	protected:
		Widget();
		virtual ~Widget();

#pragma region public get/setters
	public:

		//inline Visibility GetVisibility() const
		//{
		//	return m_visibility;
		//}

		//void SetVisibility(Visibility value);

		//inline Size GetSize() const
		//{
		//	return m_size;
		//}

		void SetSize(float width, float height);

		void SetSize(const Size& size);

		void SetAutoSize();

		void SetPercentageSize(float percent_width, float percent_height);

		void SetPercentageSize(const Size& percent_size);

		inline float GetWidth() const
		{
			return m_size.width;
		}

		void SetWidth(float value);

		void SetAutoWidth();

		void SetPercentageWidth(float value);

		inline float GetHeight() const
		{
			return m_size.height;
		}

		void SetHeight(float value);

		void SetAutoHeight();

		void SetPercentageHeight(float value);

		inline bool IsAutoWidth() const
		{
			return m_size.width < 0;
		}

		inline bool IsAutoHeight() const
		{
			return m_size.height < 0;
		}

		inline bool IsPercentageWidth() const
		{
			return CheckInternalFlag(InternalFlags::PercentageWidth);
		}

		inline bool IsPercentageHeight() const
		{
			return CheckInternalFlag(InternalFlags::PercentageHeight);
		}

		inline Thickness GetMargin() const
		{
			return m_margin;
		}

		inline HorizontalAlignment GetHorizontalAlignment() const
		{
			return m_horizontal_alignment;
		}

		inline VerticalAlignment GetVerticalAlignment() const
		{
			return m_vertical_alignment;
		}

		inline Widget* GetParent() const
		{
			return m_parent;
		}

		inline IVisual* GetVisualRoot() const
		{
			return m_visual_root;
		}


#pragma endregion public get/setters

#pragma region public functions
	public:
		void Measure(Size available_size);
		void Arrange(Rect final_rect);

		void InvalidateMeasure();
		void InvalidateArrange();

		/// <summary>	由Panel::AddChild()调用 </summary>
		void SetParent(Widget* parent);
#pragma endregion public functions

#pragma region protected get/setters
	protected:
		inline const Size& GetSizeRef() const
		{
			return m_size;
		}

		inline bool IsMeasureDirty() const
		{
			return CheckInternalFlag(InternalFlags::MeasureDirty);
		}

		void SetMeasureDirty(bool value)
		{
			SetInternalFlag(InternalFlags::MeasureDirty, value);
		}

		inline bool IsArrangeDirty() const
		{
			return CheckInternalFlag(InternalFlags::ArrangeDirty);
		}

		void SetArrangeDirty(bool value)
		{
			SetInternalFlag(InternalFlags::ArrangeDirty, value);
		}

		//inline bool IsMeasureInProgress() const
		//{
		//	return CheckInternalFlag(InternalFlags::MeasureInProgress);
		//}

		//inline void SetMeasureInProgress(bool value)
		//{
		//	return SetInternalFlag(InternalFlags::MeasureInProgress, value);
		//}

		//inline bool IsArrangeInProgress() const
		//{
		//	return CheckInternalFlag(InternalFlags::ArrangeInProgress);
		//}

		//inline void SetArrangeInProgress(bool value)
		//{
		//	return SetInternalFlag(InternalFlags::ArrangeInProgress, value);
		//}

		inline bool IsMeasureDuringArrange() const
		{
			return CheckInternalFlag(InternalFlags::MeasureDuringArrange);
		}

		inline void SetMeasureDuringArrange(bool value)
		{
			return SetInternalFlag(InternalFlags::MeasureDuringArrange, value);
		}
#pragma endregion protected get/setters

#pragma region protected funtions
	protected:

		/// <summary>	子类重载测量方法 </summary>
		/// <param name="available_size">	父节点的size </param>
		/// <returns>	自身size </returns>
		virtual Size DoMeasure(Size available_size);

		virtual void DoArrange(Rect final_rect);

		virtual void OnChildSizeChanged(Widget* child);

		/// <summary>	返回除去margin后的available_size </summary>
		static Size CalcSelfAvailableSize(const Widget& widget, Size available_size)
		{
			return Size(std::max(0.f, available_size.width - widget.m_margin.left - widget.m_margin.right)
				, std::max(0.f, available_size.height - widget.m_margin.top - widget.m_margin.bottom));
		}

		/// <summary>	初始化渲染节点 </summary>
		virtual void InitVisualRoot();

#pragma endregion protected funtions

#pragma region private funtions
	private:
		inline bool CheckInternalFlag(InternalFlags flag) const
		{
			return m_internal_flags.test((size_t)flag);
		}

		inline void SetInternalFlag(InternalFlags flag, bool value)
		{
			m_internal_flags.set((size_t)flag, value);
		}

		/**
		 * 给LayoutManager用来判断是否在队列中
		 */
		inline LayoutRequest* GetMeasureRequest() const
		{
			return m_measure_request;
		}

		/**
		 * 给LayoutManager用来判断是否在队列中
		 */
		inline void SetMeasureRequest(LayoutRequest* value)
		{
			m_measure_request = value;
		}

		/**
		 * 给LayoutManager用来判断是否在队列中
		 */
		inline LayoutRequest* GetArrangeRequest() const
		{
			return m_arrange_request;
		}

		/**
		 * 给LayoutManager用来判断是否在队列中
		 */
		inline void SetArrangeRequest(LayoutRequest* value)
		{
			m_arrange_request = value;
		}

#pragma endregion private funtions

#pragma region private fields
	private:
		Visibility m_visibility;
		Size m_size;
		Size m_actual_size;
		Thickness m_margin;
		HorizontalAlignment m_horizontal_alignment;
		VerticalAlignment m_vertical_alignment;

		Size m_previous_available_size;
		Rect m_previous_final_rect;


		//std::string m_name;

		// 布局树上的父节点
		Widget* m_parent;
		// 布局树上的层级，越小越靠近根部
		uint32_t m_tree_level;
		// 渲染树节点
		IVisual* m_visual_root;

		// 用于判断Widget是否位于布局队列中
		LayoutRequest* m_measure_request;
		LayoutRequest* m_arrange_request;


		enum class InternalFlags
		{
			PercentageWidth, // 是否为百分比宽度
			PercentageHeight, // 是否为百分比高度
			MeasureDirty,
			ArrangeDirty,
			//MeasureInProgress,
			//ArrangeInProgress,
			MeasureDuringArrange, // 由父节点在Arrange过程中触发的Measure

			// 是否为布局根节点
			IsLayoutRoot,

			// 是否挂载在布局根节点下
			// 游离于布局根节点之外的Widget不需要被布局
			IsAttachedToLayoutRoot,



			COUNT,
		};
		std::bitset<(size_t)InternalFlags::COUNT> m_internal_flags;
#pragma endregion private fields

		friend class LayoutManager;
	};
}

#endif // NUI_Widget_h__
