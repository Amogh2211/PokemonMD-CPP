#pragma once
#include <fstream>
#include <stdio.h>

#include <Backend/Types.h>

#define CHECK_OPEN_FILE(fileStream)                 \
PKMD_ERROR(fileStream.is_open());                   \
std::cout << "Loaded file: " << filePath << "\n";   \

namespace PKMD::Backend::Utils
{
	
}