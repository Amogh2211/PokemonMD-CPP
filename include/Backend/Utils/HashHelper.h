#pragma once
#include <Backend/Types.h>

namespace PKMD::Backend::Utils
{
	inline const size_t generateHash(const std::string& inputString) noexcept
	{
		std::hash<string> hasher;
		return hasher(inputString);	
	}
}