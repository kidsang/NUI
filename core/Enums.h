#pragma once
#ifndef Enums_h__
#define Enums_h__

#include <cstdint>

namespace nui
{
	// �ɼ���
	enum class Visibility : uint8_t
	{
		Visible, // �ɼ�
		Hidden, // ���ɼ���ռλ��
		Collapsed, // ���ɼ��Ҳ�ռλ��
	};

	// ˮƽ����
	enum class HorizontalAlignment : uint8_t
	{
		Left, // �����
		Right, // �Ҷ���
		Center, // ����
		Stretch, // ����
	};

	// ��ֱ����
	enum class VerticalAlignment : uint8_t
	{
		Left, // �϶���
		Right, // �¶���
		Center, // ����
		Stretch, // ����
	};
}

#endif // Enums_h__
