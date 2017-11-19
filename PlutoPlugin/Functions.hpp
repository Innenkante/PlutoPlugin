#pragma once

namespace PlutoPlugin
{
	__declspec(dllexport) class Functions
	{
	public:
		__declspec(dllexport) static void SayAll(const std::string& message);
	};
}
