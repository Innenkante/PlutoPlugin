#pragma once

namespace PlutoPlugin
{
	class Plugin;
	static std::vector < std::shared_ptr < Plugin > > plugins;

	__declspec(dllexport) class Plugin
	{
	public:
		Plugin()
		{
		}

		static std::shared_ptr < Plugin > Alloc()
		{
			auto pluginHandle = std::make_shared < Plugin > ();
			plugins.push_back(pluginHandle);

			return pluginHandle;
		}

		void GetCancer()
		{
			MessageBoxA(NULL, "get cancer\n", NULL, NULL);
		}

	protected:

	};
}
