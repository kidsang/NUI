#pragma once
#ifndef NUI_Visual_h__
#define NUI_Visual_h__

#include <vector>

namespace nui
{
	class Visual
	{
	public:
		/// <summary>	将一个子节点添加至末尾 </summary>
		/// <param name="child">	子节点 </param>
		virtual void AddChild(Visual* child) = 0;

		/// <summary>	删除一个指定的子节点 </summary>
		/// <param name="child">	子节点 </param>
		virtual void RemoveChild(Visual* child) = 0;

		/// <summary>	在指定位置添加一个子节点 </summary>
		/// <param name="child">	子节点 </param>
		/// <param name="index">	添加位置 </param>
		virtual void AddChildAt(Visual* child, uint32_t index) = 0;

		/// <summary>	删除指定位置的子节点 </summary>
		/// <param name="index">	删除位置 </param>
		virtual void RemoveChildAt(uint32_t index) = 0;

		/// <summary>	获取子节点数量 </summary>
		virtual uint32_t GetChildCount() = 0;
	};
}

#endif // NUI_Visual_h__
