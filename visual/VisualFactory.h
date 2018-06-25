#pragma once
#ifndef NUI_VisualFactory_h__
#define NUI_VisualFactory_h__

namespace nui
{
	struct IVisual;

	class VisualFactory
	{
	public:
		static void Initialize();
		static VisualFactory* Instance() { return s_instance; }

	public:
		virtual IVisual* CreateEmpty() = 0;

		//virtual IVisual* CreateColor() = 0;

		//virtual IVisual* CreateGradient() = 0;

		//virtual IVisual* CreateSprite() = 0;

		//virtual IVisual* CreateScale9Sprite() = 0;

	protected:
		VisualFactory() {};
	private:
		static VisualFactory* s_instance;
	};
}

#endif // NUI_VisualFactory_h__
