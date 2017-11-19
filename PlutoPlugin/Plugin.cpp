#include "stdafx.hpp"

namespace PlutoPlugin
{
	void LoadPlugins()
	{
		// iterate through all files in the plugins directory
		auto plugins = std::filesystem::path("plugins");
		for (auto &file : std::filesystem::directory_iterator(plugins))
		{
			// Check if file extension is .dll
			if (file.path().extension() == ".dll")
			{
				// Load plugin
				auto plugin = LoadLibraryW(file.path().c_str());
			}
		}
	}
}
