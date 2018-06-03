#pragma once
#ifndef Widget_h__
#define Widget_h__

#include <string>
#include <vector>
#include <bitset>
#include "core/Enums.h"
#include "core/Thickness.h"

namespace nui
{
	class Widget
	{
#pragma region public functions
	public:
		Widget();
		virtual ~Widget();

		inline Visibility GetVisibility() const
		{
			return m_visibility;
		}

		inline void SetVisibility(Visibility value)
		{
			if (m_visibility == value)
				return;
			m_visibility = value;
		}

		inline float GetWidth() const
		{
			return m_width;
		}

		inline void SetWidth(float value)
		{
			if (m_width == value)
				return;
			m_width = value;
			SetWidthSeted(true);
		}

		inline bool IsAutoWidth() const
		{
			return !CheckWidthSeted();
		}

		inline void SetAutoWidth()
		{
			SetWidthSeted(false);
		}

		inline float GetHeight() const
		{
			return m_width;
		}

		inline void SetHeight(float value)
		{
			m_width = value;
			SetHeightSeted(true);
		}

		inline bool IsAutoHeight() const
		{
			return !CheckHeightSeted();
		}

		inline void SetAutoHeight()
		{
			SetHeightSeted(false);
		}
#pragma endregion public functions

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

		inline bool CheckWidthSeted() const
		{
			return CheckInternalFlag(InternalFlags::WIDTH_SETED);
		}

		inline void SetWidthSeted(bool value)
		{
			SetInternalFlag(InternalFlags::WIDTH_SETED, value);
		}

		inline bool CheckHeightSeted() const
		{
			return CheckInternalFlag(InternalFlags::WIDTH_SETED);
		}

		inline void SetHeightSeted(bool value)
		{
			SetInternalFlag(InternalFlags::WIDTH_SETED, value);
		}
#pragma endregion private funtions

#pragma region private fields
	private:
		Visibility m_visibility;
		float m_width;
		float m_height;
		float m_min_width;
		float m_min_height;
		float m_max_width;
		float m_max_height;
		float m_actual_width;
		float m_actual_height;
		Thickness m_margin;
		Thickness m_padding;
		HorizontalAlignment m_horizontal_alignment;
		VerticalAlignment m_vertical_alignment;

		std::string m_name;
		Widget* m_parent;
		std::vector<Widget*> m_children;

		enum class InternalFlags
		{
			WIDTH_SETED,
			HEIGHT_SETED,
			MIN_WIDTH_SETED,
			MIN_HEIGHT_SETED,
			MAX_WIDTH_SETED,
			MAX_HEIGHT_SETED,

			COUNT,
		};
		std::bitset<(size_t)InternalFlags::COUNT> m_internal_flags;
#pragma endregion private fields
	};
}

#endif // Widget_h__
