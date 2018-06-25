#include "Ref.h"
#include "Assert.h"

namespace nui
{

	void Ref::AddRef()
	{
		NUI_ASSERT(m_ref_count > 0);
		m_ref_count += 1;
	}

	void Ref::DecRef()
	{
		NUI_ASSERT(m_ref_count > 0);
		m_ref_count -= 1;
		if (m_ref_count == 0)
		{
			delete this;
		}
	}

}
