#include "EventBus.h"

namespace PKMD::Backend::Events
{
	void EventBus::Reset()
	{
		for (auto& it : m_eventsMap)
		{
			it.second.clear();
		}
		m_eventsMap.clear();

#ifdef PKMD_DEBUG
		PKMD_INFO_ASSERT(m_eventsMap.size() <= 0, "Event map not cleared fully");
#endif
	}

}
