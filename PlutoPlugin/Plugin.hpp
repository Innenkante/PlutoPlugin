#pragma once

namespace PlutoPlugin
{
	class Plugin;
	static std::vector < std::shared_ptr < Plugin > > plugins;

	enum class CallbackType
	{
		PlayerSay,
		PlayerConnecting,
		PlayerConnected,
		PlayerDisconnected,
		ExitLevel,
	};

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

		template <typename T> void InstallCallback(CallbackType type, T function)
		{
			this->callbacks[type] = reinterpret_cast<std::uintptr_t>(function);
		}

		std::unordered_map < CallbackType, std::uintptr_t >& GetCallbacks()
		{
			return this->callbacks;
		}

	protected:
		std::unordered_map < CallbackType, std::uintptr_t > callbacks;

	};
}
