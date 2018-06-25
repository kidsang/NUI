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

		/// <summary>	��Panel::AddChild()���� </summary>
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

		/// <summary>	�������ز������� </summary>
		/// <param name="available_size">	���ڵ��size </param>
		/// <returns>	����size </returns>
		virtual Size DoMeasure(Size available_size);

		virtual void DoArrange(Rect final_rect);

		virtual void OnChildSizeChanged(Widget* child);

		/// <summary>	���س�ȥmargin���available_size </summary>
		static Size CalcSelfAvailableSize(const Widget& widget, Size available_size)
		{
			return Size(std::max(0.f, available_size.width - widget.m_margin.left - widget.m_margin.right)
				, std::max(0.f, available_size.height - widget.m_margin.top - widget.m_margin.bottom));
		}

		/// <summary>	��ʼ����Ⱦ�ڵ� </summary>
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
		 * ��LayoutManager�����ж��Ƿ��ڶ�����
		 */
		inline LayoutRequest* GetMeasureRequest() const
		{
			return m_measure_request;
		}

		/**
		 * ��LayoutManager�����ж��Ƿ��ڶ�����
		 */
		inline void SetMeasureRequest(LayoutRequest* value)
		{
			m_measure_request = value;
		}

		/**
		 * ��LayoutManager�����ж��Ƿ��ڶ�����
		 */
		inline LayoutRequest* GetArrangeRequest() const
		{
			return m_arrange_request;
		}

		/**
		 * ��LayoutManager�����ж��Ƿ��ڶ�����
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

		// �������ϵĸ��ڵ�
		Widget* m_parent;
		// �������ϵĲ㼶��ԽСԽ��������
		uint32_t m_tree_level;
		// ��Ⱦ���ڵ�
		IVisual* m_visual_root;

		// �����ж�Widget�Ƿ�λ�ڲ��ֶ�����
		LayoutRequest* m_measure_request;
		LayoutRequest* m_arrange_request;


		enum class InternalFlags
		{
			PercentageWidth, // �Ƿ�Ϊ�ٷֱȿ��
			PercentageHeight, // �Ƿ�Ϊ�ٷֱȸ߶�
			MeasureDirty,
			ArrangeDirty,
			//MeasureInProgress,
			//ArrangeInProgress,
			MeasureDuringArrange, // �ɸ��ڵ���Arrange�����д�����Measure

			// �Ƿ�Ϊ���ָ��ڵ�
			IsLayoutRoot,

			// �Ƿ�����ڲ��ָ��ڵ���
			// �����ڲ��ָ��ڵ�֮���Widget����Ҫ������
			IsAttachedToLayoutRoot,



			COUNT,
		};
		std::bitset<(size_t)InternalFlags::COUNT> m_internal_flags;
#pragma endregion private fields

		friend class LayoutManager;
	};
}

#endif // NUI_Widget_h__
