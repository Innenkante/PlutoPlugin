#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <experimental\filesystem>

namespace std
{
	namespace filesystem = experimental::filesystem;
}

#include "Functions.hpp"
#include "Plugin.hpp"

namespace PlutoPlugin
{
	__declspec(dllexport) void Startup();
}
