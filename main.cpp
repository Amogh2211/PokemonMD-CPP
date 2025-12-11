#pragma once
#include "Game/GameManager.h"
#include <filesystem>
#include <stdio.h>


#include <Backend/Types.h>
#include <Backend/Events/EventBus.h>
#include <Backend/Input/InputManager.h>

#include <Game/UI/MenuManager.h>

// Should ideally make a logger at some point
using namespace PKMD::Game;
using namespace PKMD::Backend::Events;
using namespace PKMD::Backend::Input;


// ---------------- Player ------------------------
struct Player {
	int x = 400;
	int y = 300;
	int speed = 5;

	void MoveUp()
	{
		y -= speed;
		std::cout << "PlayerMovedUp\n";
	}
	void MoveDown() { y += speed; std::cout << "PlayerMovedDown\n"; }
	void MoveLeft() { x -= speed; std::cout << "PlayerMovedLeft\n"; }
	void MoveRight() { x += speed; std::cout << "PlayerMovedRight\n"; }

	void Render() const { DrawRectangle(x, y, 50, 50, BLUE); }
	void SubscribeToEvents()
	{
		PKMD::Backend::Events::EventBus& eventBus = *PKMD::Backend::Events::EventBus::Instance();
		// Subscribe Player movement
		eventBus.Subscribe<KeyPressedEvent>([&](const KeyPressedEvent& e) {
			switch (e.keyCode)
			{
			case KEY_UP:    MoveUp(); break;
			case KEY_DOWN:  MoveDown(); break;
			case KEY_LEFT:  MoveLeft(); break;
			case KEY_RIGHT: MoveRight(); break;
			}
			},
			EventChannels::EVENT_TYPE_INPUT
		);

	}
};





int main()
{
	PKMD::Backend::Events::EventBus& eventBus = *PKMD::Backend::Events::EventBus::Instance();
	
	InitWindow(800, 600, "EventBus Input Example");
	SetTargetFPS(60);

	
	Player player;
	player.SubscribeToEvents();

	

	while (!WindowShouldClose())
	{
		// 1. Poll inputs and emit events
		PKMD::Backend::Input::InputManager::PollInput(eventBus);

		// 2. Draw scene
		BeginDrawing();
		ClearBackground(RAYWHITE);

		player.Render();
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}