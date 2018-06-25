#pragma once
#ifndef NUI_Visual_h__
#define NUI_Visual_h__

namespace nui
{
	struct IVisual
	{
		/// <summary>	�������ü��� </summary>
		virtual void AddRef() = 0;

		/// <summary>	�������ü��� </summary>
		virtual void DecRef() = 0;

		/// <summary>	��һ���ӽڵ������ĩβ </summary>
		/// <param name="child">	�ӽڵ� </param>
		virtual void AddChild(IVisual* child) = 0;

		/// <summary>	ɾ��һ��ָ�����ӽڵ� </summary>
		/// <param name="child">	�ӽڵ� </param>
		virtual void RemoveChild(IVisual* child) = 0;

		/// <summary>	��ָ��λ�����һ���ӽڵ� </summary>
		/// <param name="child">	�ӽڵ� </param>
		/// <param name="index">	���λ�� </param>
		virtual void AddChildAt(IVisual* child, uint32_t index) = 0;

		/// <summary>	ɾ��ָ��λ�õ��ӽڵ� </summary>
		/// <param name="index">	ɾ��λ�� </param>
		virtual void RemoveChildAt(uint32_t index) = 0;

		/// <summary>	��ȡ�ӽڵ����� </summary>
		virtual uint32_t GetChildCount() = 0;
	};
}

#endif // NUI_Visual_h__
