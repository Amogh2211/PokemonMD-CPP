#include <string>


#include <Backend/RTTI/RTTI.h>

namespace PKMD::Backend
{
	std::string RTTI::ToString() const
	{
		using namespace std::string_literals;
		return "RTTI"s;
	}

	bool RTTI::Equals(const RTTI* rhs) const
	{
		return this == rhs;
	}
}