#pragma once


namespace PKMD::Game
{
	class EventBase;

	class GameObject
	{
	public:
		virtual ~GameObject() = default;
		virtual void Init() {}
		virtual void Destroy() {}

		// Updates
		virtual void Update(float deltaTime) {}
		virtual void FixedUpdate(float fixedDeltaTime) {}

		// rendering
		virtual void Render() {}

		// Called when an event is emitted on the bus
		virtual void OnEvent(const EventBase& event) {}

		virtual void SubcribeToEvents() = 0;
	};
}