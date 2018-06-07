#pragma once
#ifndef NUI_Widget_h__
#define NUI_Widget_h__

#include <string>
#include <vector>
#include <bitset>
#include <list>
#include "core/Assert.h"
#include "core/Enums.h"
#include "core/Size.h"
#include "core/Thickness.h"
#include "core/LayoutManager.h"

namespace nui
{
	class Widget
	{
		Widget();
		virtual ~Widget();

		enum class InternalFlags;

#pragma region public get/setters
	public:

		inline Visibility GetVisibility() const
		{
			return m_visibility;
		}

		inline float GetWidth() const
		{
			return m_size.width;
		}

		inline float GetHeight() const
		{
			return m_size.height;
		}

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

		void SetVisibility(Visibility value);

		void SetWidth(float value);

		void SetAutoWidth();

		void SetPercentageWidth(float value);

		void SetHeight(float value);

		void SetAutoHeight();

		void SetPercentageHeight(float value);
#pragma endregion public get/setters

#pragma region public functions
	public:
		void Measure(Size available_size);
		void InvalidateMeasure();
		void InvalidateArrange();

#pragma endregion public functions

#pragma region protected get/setters
	protected:
		inline bool IsMeasureDirty() const
		{
			return CheckInternalFlag(InternalFlags::MeasureDirty);
		}

		inline bool IsArrangeDirty() const
		{
			return CheckInternalFlag(InternalFlags::ArrangeDirty);
		}

		inline bool IsMeasureInProgress() const
		{
			return CheckInternalFlag(InternalFlags::MeasureInProgress);
		}

		inline bool IsArrangeInProgress() const
		{
			return CheckInternalFlag(InternalFlags::ArrangeInProgress);
		}
#pragma endregion protected get/setters

#pragma region protected funtions
	protected:
		Size DoMeasure(Size available_size);
#pragma endregion protected funtions

#pragma region private funtions
	private:
		enum class InternalFlags;
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
		Size m_previous_available_size;
		Thickness m_margin;
		HorizontalAlignment m_horizontal_alignment;
		VerticalAlignment m_vertical_alignment;

		//std::string m_name;
		Widget* m_parent;

		// 用于判断Widget是否位于布局队列中
		LayoutRequest* m_measure_request;
		LayoutRequest* m_arrange_request;


		enum class InternalFlags
		{
			PercentageWidth, // 是否为百分比宽度
			PercentageHeight, // 是否为百分比高度
			MeasureDirty,
			ArrangeDirty,
			MeasureInProgress,
			ArrangeInProgress,



			COUNT,
		};
		std::bitset<(size_t)InternalFlags::COUNT> m_internal_flags;
#pragma endregion private fields

		friend class LayoutManager;
	};
}

#endif // NUI_Widget_h__
