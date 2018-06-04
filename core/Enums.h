#pragma once
#ifndef NUI_Enums_h__
#define NUI_Enums_h__

#include <cstdint>

namespace nui
{
	// 可见性
	enum class Visibility : uint8_t
	{
		Visible, // 可见
		Hidden, // 不可见但占位置
		Collapsed, // 不可见且不占位置
	};

	// 水平对齐
	enum class HorizontalAlignment : uint8_t
	{
		Left, // 左对齐
		Right, // 右对齐
		Center, // 居中
		Stretch, // 拉伸
	};

	// 垂直对齐
	enum class VerticalAlignment : uint8_t
	{
		Left, // 上对齐
		Right, // 下对齐
		Center, // 居中
		Stretch, // 拉伸
	};
}

#endif // NUI_Enums_h__
