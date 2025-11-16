#include <Backend/Utils/Parser.h>
#include <Backend/Types.h>
#include <Backend/Utils/FileUtils.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <filesystem>


namespace PKMD::Backend::Utils
{
	bool FilePathsParser::Deserialize(const std::string& jsonText)
	{
		return false;
	}
	bool FilePathsParser::Deserialize(std::istream& input)
	{
		populateRoot(input, m_rootMap);
		return true;
	}
	bool FilePathsParser::DeserializeFromFile(const std::string& filePath)
	{
		std::cout << "Actual CWD: " << std::filesystem::current_path() << "\n";
		std::ifstream fileStream(filePath);
		CHECK_OPEN_FILE(fileStream);
		return Deserialize(fileStream);
	}
}
