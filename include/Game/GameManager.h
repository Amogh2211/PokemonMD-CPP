#pragma once
namespace PKMD::Game
{
	class GameManager
	{
	public:
		static GameManager* Create();
		static GameManager* GetInstance();
		static void Destroy();
		void Init();
	private:
		void InitGameManager();
	};
}