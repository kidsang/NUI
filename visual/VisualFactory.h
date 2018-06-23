#pragma once
#ifndef NUI_VisualFactory_h__
#define NUI_VisualFactory_h__

namespace nui
{
	class Visual;

	class VisualFactory
	{
	public:
		static void Initialize();
		static VisualFactory* Instance() { return s_instance; }

	public:
		virtual Visual* CreateEmpty() = 0;

		//virtual Visual* CreateColor() = 0;

		//virtual Visual* CreateGradient() = 0;

		//virtual Visual* CreateSprite() = 0;

		//virtual Visual* CreateScale9Sprite() = 0;

	protected:
		VisualFactory() {};
	private:
		static VisualFactory* s_instance;
	};
}

#endif // NUI_VisualFactory_h__
