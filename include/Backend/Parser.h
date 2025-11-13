#pragma once
#include "json/json.h"
#include <Backend/Types.h>


#include <Backend/RTTI/RTTI.h>
#include <Backend/ServiceMgr.h>

namespace PKMD::Backend
{
	/// @brief Factory style service for different types of parsers - can call required parsers on load time
	
	/// @brief  Every parser will be of this type, can static cast after
	class IParserFactoryBase : public IFactoryBase
	{
		RTTI_DECLARATIONS(IParserFactoryBase, RTTI);
	public:
		virtual std::string GetProductName() = 0;
		virtual RTTI::IdType GetBaseTypeId() const = 0;
	};
	
	
	struct IP


	class ParserService
	{
		struct IParserProvider : public IParserFactoryBase
		{
			RTTI_DECLARATIONS(IParserFactoryBase, IParserProvider);

		public:
			virtual IParserFactoryBase* GetParserOfType(std::string& type);
			virtual IParserFactoryBase* CreateParserOfType(std::string& type);

		};





		// Get interface ID
		PKMD_SERVICE_INTERFACE
	};
};