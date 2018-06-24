#pragma once
#ifndef NUI_Color_h__
#define NUI_Color_h__

#include <cstdint>

namespace nui
{

	struct Color
	{
		static const Color White;
		static const Color Black;
		static const Color Transparent;

		union
		{
			uint32_t rgba;
			struct {
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;
			};
		};

		Color()
			: rgba(0)
		{}

		explicit Color(uint32_t rgba)
			: rgba(rgba)
		{}

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
			: r(r), g(g), b(b), a(a)
		{}

		bool operator == (const Color& other) const
		{
			return rgba == other.rgba;
		}

		bool operator != (const Color& other) const
		{
			return !(*this == other);
		}
	};

}

#endif // NUI_Color_h__