#pragma once
#ifndef NUI_Ref_h__
#define NUI_Ref_h__

#include <cstdint>

namespace nui
{
	class Ref
	{
	public:
		Ref()
			: m_ref_count(1)
		{}

		void AddRef();

		void DecRef();

	private:
		uint32_t m_ref_count;
	};

}

#endif // NUI_Ref_h__
