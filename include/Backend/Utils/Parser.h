#pragma once
#include <json/json.h>
#include <Backend/ServiceMgr.h>
#include <Backend/RTTI/RTTI.h>

namespace PKMD::Backend::Utils
{

	inline void populateRoot(std::istream& input, Json::Value& root)
	{
		std::string errs;

		Json::CharReaderBuilder builder;
		builder["collectComments"] = false;

		std::string json((std::istreambuf_iterator<char>(input)),
			std::istreambuf_iterator<char>());

		std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

		bool ok = reader->parse(json.c_str(),
			json.c_str() + json.size(),
			&root,
			&errs);

		if (!ok)
		{
			std::cout << "JSON parse error: " << errs << "\n";
			PKMD_ERROR(ok);
		}

		// DEBUG: See what was parsed
		std::cout << "Loaded: " << root.toStyledString() << "\n";
		std::cout << "\n--------------------------------------------------------\n";
	}
	
	struct IJsonParser
	{
	public:
		// Deserialize JSON from a string
		virtual bool Deserialize(const std::string& jsonText) = 0;

		// Deserialize JSON from an input stream
		virtual bool Deserialize(std::istream& input) = 0;

		// Deserialize JSON from a file
		virtual bool DeserializeFromFile(const std::string& filePath) = 0;

		virtual Json::Value getRootMap() const = 0;
	};


	class FilePathsParser :  public IJsonParser
	{
	public:
		// Deserialize JSON from a string
		virtual bool Deserialize(const std::string& jsonText) override;

		// Deserialize JSON from an input stream
		virtual bool Deserialize(std::istream& input) override;

		// Deserialize JSON from a file
		virtual bool DeserializeFromFile(const std::string& filePath) override;

		virtual Json::Value getRootMap() const { return m_rootMap; };
	private:
		Json::Value m_rootMap;
	};

	
}