#pragma once

namespace asset {
	std::shared_ptr<olc::Sprite> sprForward;
	const char* forward = "./asset/arrow.png";
	std::shared_ptr<olc::Sprite> sprLoop;
	const char* loop = "./asset/loop.png";
	std::shared_ptr<olc::Sprite> sprLoop_start;
	const char* loop_start = "./asset/loop_start.png";
	std::shared_ptr<olc::Sprite> sprLoop_end;
	const char* loop_end = "./asset/loop_end.png";
	std::shared_ptr<olc::Sprite> sprLoop_side;
	const char* loop_side = "./asset/loop_side.png";
	std::shared_ptr<olc::Sprite> sprLeft;
	const char* left = "./asset/left.png";
	std::shared_ptr<olc::Sprite> sprRight;
	const char* right = "./asset/right.png";
	std::shared_ptr<olc::Sprite> sprStart;
	const char* btn_start = "./asset/start.png";
	std::shared_ptr<olc::Sprite> sprReset;
	const char* btn_reset = "./asset/reset.png";

	std::shared_ptr<olc::Sprite> sprSlime;
	const char* slime = "./asset/slime.png";
	std::shared_ptr<olc::Sprite> sprStar;
	const char* star = "./asset/target.png";
	std::shared_ptr<olc::Sprite> sprCoin;
	const char* coin = "./asset/coin/Coin1.png";

	std::shared_ptr<olc::Sprite> sprAir;
	const char* air = "./asset/air.png";
	std::shared_ptr<olc::Sprite> sprGround;
	const char* ground = "./asset/land.png";
	std::shared_ptr<olc::Sprite> sprSea;
	const char* sea = "./asset/ocean.jpg";
	std::shared_ptr<olc::Sprite> sprBar;
	const char* bar = "./asset/bar.png";

	std::shared_ptr<olc::Sprite> sprMenu;
	const char* menu = "./asset/menu.jpg";
	std::shared_ptr<olc::Sprite> sprWin;
	const char* win = "./asset/win.jpg";
	std::shared_ptr<olc::Sprite> sprNext;
	const char* next = "./asset/next.jpg";

	std::shared_ptr<shi::SprAnima> aniCoin = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerUp = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerDown = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerLeft = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerRight = std::make_shared<shi::SprAnima>();
	std::shared_ptr<shi::SprAnima> aniPlayerIdle = std::make_shared<shi::SprAnima>();

	void loadAllAssets() {
		sprSlime = std::make_shared<olc::Sprite>(slime);
		sprForward = std::make_shared<olc::Sprite>(forward);
		sprLoop = std::make_shared<olc::Sprite>(loop);
		sprLoop_start = std::make_shared<olc::Sprite>(loop_start);
		sprLoop_end = std::make_shared<olc::Sprite>(loop_end);
		sprLoop_side = std::make_shared<olc::Sprite>(loop_side);
		sprLeft = std::make_shared<olc::Sprite>(left);
		sprRight = std::make_shared<olc::Sprite>(right);
		sprAir = std::make_shared<olc::Sprite>(air);
		sprGround = std::make_shared<olc::Sprite>(ground);
		sprStar = std::make_shared<olc::Sprite>(star);
		sprStart = std::make_shared<olc::Sprite>(btn_start);
		sprReset = std::make_shared<olc::Sprite>(btn_reset);
		sprCoin = std::make_shared<olc::Sprite>(coin);
		sprSea = std::make_shared<olc::Sprite>(sea);
		sprBar = std::make_shared<olc::Sprite>(bar);
		sprMenu = std::make_shared<olc::Sprite>(menu);
		sprWin = std::make_shared<olc::Sprite>(win);
		sprNext = std::make_shared<olc::Sprite>(next);

		aniCoin->addFrame(std::make_shared<olc::Sprite>("./asset/coin/Coin_1.png"), 0.1);
		aniCoin->addFrame(std::make_shared<olc::Sprite>("./asset/coin/Coin_2.png"), 0.1);
		aniCoin->addFrame(std::make_shared<olc::Sprite>("./asset/coin/Coin_3.png"), 0.1);
		aniCoin->addFrame(std::make_shared<olc::Sprite>("./asset/coin/Coin_4.png"), 0.1);
		aniPlayerUp->addFrame(std::make_shared<olc::Sprite>("./asset/player/up/01.png"), 0.125);
		aniPlayerUp->addFrame(std::make_shared<olc::Sprite>("./asset/player/up/02.png"), 0.125);
		aniPlayerUp->addFrame(std::make_shared<olc::Sprite>("./asset/player/up/03.png"), 0.125);
		aniPlayerUp->addFrame(std::make_shared<olc::Sprite>("./asset/player/up/04.png"), 0.125);
		aniPlayerDown->addFrame(std::make_shared<olc::Sprite>("./asset/player/down/01.png"), 0.125);
		aniPlayerDown->addFrame(std::make_shared<olc::Sprite>("./asset/player/down/02.png"), 0.125);
		aniPlayerDown->addFrame(std::make_shared<olc::Sprite>("./asset/player/down/03.png"), 0.125);
		aniPlayerDown->addFrame(std::make_shared<olc::Sprite>("./asset/player/down/04.png"), 0.125);
		aniPlayerLeft->addFrame(std::make_shared<olc::Sprite>("./asset/player/left/02.png"), 0.125);
		aniPlayerLeft->addFrame(std::make_shared<olc::Sprite>("./asset/player/left/03.png"), 0.125);
		aniPlayerLeft->addFrame(std::make_shared<olc::Sprite>("./asset/player/left/04.png"), 0.125);
		aniPlayerLeft->addFrame(std::make_shared<olc::Sprite>("./asset/player/left/03.png"), 0.125);
		aniPlayerRight->addFrame(std::make_shared<olc::Sprite>("./asset/player/right/02.png"), 0.125);
		aniPlayerRight->addFrame(std::make_shared<olc::Sprite>("./asset/player/right/03.png"), 0.125);
		aniPlayerRight->addFrame(std::make_shared<olc::Sprite>("./asset/player/right/04.png"), 0.125);
		aniPlayerRight->addFrame(std::make_shared<olc::Sprite>("./asset/player/right/03.png"), 0.125);
		aniPlayerIdle->addFrame(std::make_shared<olc::Sprite>("./asset/player/idle/01.png"), 0.25);
		aniPlayerIdle->addFrame(std::make_shared<olc::Sprite>("./asset/player/idle/02.png"), 0.25);
		aniPlayerIdle->addFrame(std::make_shared<olc::Sprite>("./asset/player/idle/03.png"), 0.25);
		aniPlayerIdle->addFrame(std::make_shared<olc::Sprite>("./asset/player/idle/04.png"), 0.25);
	}
}