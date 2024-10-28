#pragma once

namespace asset {
	std::shared_ptr<olc::Renderable> sprForward = std::make_shared<olc::Renderable>();
	const char* forward = "./asset/arrow.png";
	std::shared_ptr<olc::Renderable> sprLoop = std::make_shared<olc::Renderable>();
	const char* loop = "./asset/loop.png";
	std::shared_ptr<olc::Renderable> sprLoop_start = std::make_shared<olc::Renderable>();
	const char* loop_start = "./asset/loop_start.png";
	std::shared_ptr<olc::Renderable> sprLoop_end = std::make_shared<olc::Renderable>();
	const char* loop_end = "./asset/loop_end.png";
	std::shared_ptr<olc::Renderable> sprLoop_side = std::make_shared<olc::Renderable>();
	const char* loop_side = "./asset/loop_side.png";
	std::shared_ptr<olc::Renderable> sprLeft = std::make_shared<olc::Renderable>();
	const char* left = "./asset/left.png";
	std::shared_ptr<olc::Renderable> sprRight = std::make_shared<olc::Renderable>();
	const char* right = "./asset/right.png";
	std::shared_ptr<olc::Renderable> sprStart = std::make_shared<olc::Renderable>();
	const char* btn_start = "./asset/start.png";
	std::shared_ptr<olc::Renderable> sprReset = std::make_shared<olc::Renderable>();
	const char* btn_reset = "./asset/reset.png";

	std::shared_ptr<olc::Renderable> sprSlime = std::make_shared<olc::Renderable>();
	const char* slime = "./asset/slime.png";
	std::shared_ptr<olc::Renderable> sprStar = std::make_shared<olc::Renderable>();
	const char* star = "./asset/target.png";
	std::shared_ptr<olc::Renderable> sprCoin = std::make_shared<olc::Renderable>();
	const char* coin = "./asset/coin/Coin1.png";

	std::shared_ptr<olc::Renderable> sprAir = std::make_shared<olc::Renderable>();
	const char* air = "./asset/air.png";
	std::shared_ptr<olc::Renderable> sprGround = std::make_shared<olc::Renderable>();
	const char* ground = "./asset/land.png";
	std::shared_ptr<olc::Renderable> sprSea = std::make_shared<olc::Renderable>();
	const char* sea = "./asset/ocean.jpg";
	std::shared_ptr<olc::Renderable> sprBar = std::make_shared<olc::Renderable>();
	const char* bar = "./asset/bar.png";

	std::shared_ptr<olc::Renderable> sprMenu = std::make_shared<olc::Renderable>();
	const char* menu = "./asset/menu.jpg";
	std::shared_ptr<olc::Renderable> sprWin = std::make_shared<olc::Renderable>();
	const char* win = "./asset/win.jpg";
	std::shared_ptr<olc::Renderable> sprNext = std::make_shared<olc::Renderable>();
	const char* next = "./asset/next.jpg";

	std::shared_ptr<shi::SprAnima> aniCoin = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerUp = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerDown = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerLeft = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerRight = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerIdle = std::make_shared<shi::SprAnima>();

	void loadAllAssets() {
		sprSlime->Load(slime);
		sprForward->Load(forward);
		sprLoop->Load(loop);
		sprLoop_start->Load(loop_start);
		sprLoop_end->Load(loop_end);
		sprLoop_side->Load(loop_side);
		sprLeft->Load(left);
		sprRight->Load(right);
		sprAir->Load(air);
		sprGround->Load(ground);
		sprStar->Load(star);
		sprStart->Load(btn_start);
		sprReset->Load(btn_reset);
		sprCoin->Load(coin);
		sprSea->Load(sea);
		sprBar->Load(bar);
		sprMenu->Load(menu);
		sprWin->Load(win);
		sprNext->Load(next);

		aniCoin->addFrame("./asset/coin/Coin_1.png", 0.1);
		aniCoin->addFrame("./asset/coin/Coin_2.png", 0.1);
		aniCoin->addFrame("./asset/coin/Coin_3.png", 0.1);
		aniCoin->addFrame("./asset/coin/Coin_4.png", 0.1);
		aniPlayerUp->addFrame("./asset/player/up/01.png", 0.125);
		aniPlayerUp->addFrame("./asset/player/up/02.png", 0.125);
		aniPlayerUp->addFrame("./asset/player/up/03.png", 0.125);
		aniPlayerUp->addFrame("./asset/player/up/04.png", 0.125);
		aniPlayerDown->addFrame("./asset/player/down/01.png", 0.125);
		aniPlayerDown->addFrame("./asset/player/down/02.png", 0.125);
		aniPlayerDown->addFrame("./asset/player/down/03.png", 0.125);
		aniPlayerDown->addFrame("./asset/player/down/04.png", 0.125);
		aniPlayerLeft->addFrame("./asset/player/left/02.png", 0.125);
		aniPlayerLeft->addFrame("./asset/player/left/03.png", 0.125);
		aniPlayerLeft->addFrame("./asset/player/left/04.png", 0.125);
		aniPlayerLeft->addFrame("./asset/player/left/03.png", 0.125);
		aniPlayerRight->addFrame("./asset/player/right/02.png", 0.125);
		aniPlayerRight->addFrame("./asset/player/right/03.png", 0.125);
		aniPlayerRight->addFrame("./asset/player/right/04.png", 0.125);
		aniPlayerRight->addFrame("./asset/player/right/03.png", 0.125);
		aniPlayerIdle->addFrame("./asset/player/idle/01.png", 0.25);
		aniPlayerIdle->addFrame("./asset/player/idle/02.png", 0.25);
		aniPlayerIdle->addFrame("./asset/player/idle/03.png", 0.25);
		aniPlayerIdle->addFrame("./asset/player/idle/04.png", 0.25);
	}
}