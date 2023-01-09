#pragma once
#include <vector>
#include <string> 
#include "olcPixelGameEngine.h"
#include "shiiTool.h"
#include "Asset.h"
#include "MapData.h"

olc::vi2d tileSize = { 30,30 };

class State{
public:
	virtual State* run(float fElapsedTime, olc::PixelGameEngine* engine) = 0;
};

class SplashState :public State {
private:
	bool state_ini = true;
	float displayedTime = 0.0;
	float slimeAlpha = 0.0;
	shi::SimpleSprite sprSlime;
	shi::SimpleSprite sprMenu;
public:
	State* run(float fElapsedTime, olc::PixelGameEngine* engine)override;
};

class GameState :public State {
private:
	//初始化物件宣告
	std::unique_ptr<shi::SimpleSprite> onDrag;
	shi::SimpleSprite sprForward;
	shi::SimpleSprite sprLoop;
	shi::SimpleSprite sprLeft;
	shi::SimpleSprite sprRight;
	shi::SimpleSprite map[10][10];
	shi::SimpleSprite sprStart;
	shi::SimpleSprite sprReset;
	shi::SimpleSprite sprStar;
	std::shared_ptr<shiMap::MapData> mapData;
	std::vector<std::unique_ptr<shi::SimpleSprite>> sprSideLineList;
	std::map<int, std::unique_ptr<shi::SimpleSprite>> sprCoinList;
	std::vector<olc::vi2d> coinPosList;
	shi::SimpleSprite sprSea;
	shi::SimpleSprite sprBar;
	shi::SimpleSprite sprWin;
	shi::SimpleSprite sprNext;


private:
	//指令相關宣告
	enum cmdType {
		none,
		forward,
		turn_left,
		turn_right,
		loop_start,
		loop_end
	};
	class Cmd {
	public:
		Cmd(cmdType type):type(type){};
		cmdType type;
		int loopCount = 4;
	};
	cmdType onDragCmd = none;
	std::vector<Cmd> cmdList;
	shi::SimpleSprite cmdSprt[14];
	int mouseHoverIndex = -1;

private:
	//主角相關宣告
	enum direction {
		up,down,left,right
	};
	olc::vi2d getDir2d(direction dir) {
		switch (dir){
		case up: return { 0,-1 };
		case down: return { 0,1 };
		case left: return { -1,0 };
		case right: return { 1,0 };
		}
	}
	direction playerDir = right;
	shi::SimpleSprite player;
	olc::vi2d playerPos = { 3,3 };
	olc::vi2d lastPos = { 3,3 };

private:
	//遊戲狀態相關宣告
	enum actionState {
		state_ini,
		editCommand,
		execCommand,
		levelCleared
	};
	actionState currentAction = state_ini;
	int programCount = 0;
	std::vector<int> loopCountList;
	std::vector<int> loopRteurnList;
	float animationTime = 0;
	int mapIndex = 1;//設定初始地圖
	int totalCoinGet = 0;
	int currentCoinGet = 0;

public:
	State* run(float fElapsedTime, olc::PixelGameEngine* engine) override;
};

//-----------------------以上為宣告-----------------------------
//-----------------------以下為實作-----------------------------

State* SplashState::run(float fElapsedTime, olc::PixelGameEngine* engine) {
	//開啟遊戲時顯示史萊姆商標
	engine->Clear(olc::BLACK);
	if (state_ini) {
		state_ini = false;
		sprSlime.ini(asset::slime);
		sprSlime.pos = (olc::vi2d(400, 300) - sprSlime.getSize()) / 2;
		sprMenu.ini(asset::menu);
		sprMenu.setSize({ 400,300 });
	}
	else displayedTime += fElapsedTime;
	if (displayedTime > 3) {
		sprMenu.draw(engine);
		if(engine->GetMouse(0).bPressed) return new GameState();
	}
	else if (displayedTime > 2) {
		sprMenu.tint = olc::PixelF(1.0, 1.0, 1.0, displayedTime-2);
		sprMenu.draw(engine);
		slimeAlpha = 3- displayedTime;
		sprSlime.tint = olc::PixelF(1.0, 1.0, 1.0, slimeAlpha);
		sprSlime.draw(engine);
	}
	else if (displayedTime > 1) {
		sprSlime.tint = olc::PixelF(1.0, 1.0, 1.0, slimeAlpha);
		sprSlime.draw(engine);
	}
	else {
		slimeAlpha = displayedTime;
		sprSlime.tint = olc::PixelF(1.0, 1.0, 1.0, slimeAlpha);
		sprSlime.draw(engine);
	}
	return this;
}

State* GameState::run(float fElapsedTime, olc::PixelGameEngine* engine) {
	switch (currentAction) {
	case state_ini:
		//初始化階段，只執行一次
		sprForward.ini(asset::sprForward, { 300,0 });
		sprForward.setSize({ 50,50 });
		sprLoop.ini(asset::sprLoop, { 300,50 });
		sprLoop.setSize({ 50,50 });
		sprLeft.ini(asset::sprLeft, { 300,100 });
		sprLeft.setSize({ 50,50 });
		sprRight.ini(asset::sprRight, { 300,150 });
		sprRight.setSize({ 50,50 });
		sprStart.ini(asset::sprStart, { 300,210 });
		sprStart.setSize({ 50,30 });
		sprReset.ini(asset::sprReset, { 300,260 });
		sprReset.setSize({ 50,30 });
		sprSea.ini(asset::sprSea);
		sprSea.setSize({ 400,300 });
		sprBar.ini(asset::sprBar, { 350,0 });
		sprBar.setSize({ 50,300 });
		sprWin.ini(asset::sprWin, { 75,25 });
		sprWin.setSize({ 250,250 });
		sprNext.ini(asset::sprNext, { 75,25 });
		sprNext.setSize({ 250,250 });
		if (mapIndex > 8) {
			//遊戲結束
		}
		else mapData = shiMap::maps[mapIndex];//載入地圖
		playerPos = mapData->getSpawnPoint();
		lastPos = playerPos;
		coinPosList = mapData->getCoinPos();
		sprStar.ini(asset::star, mapData->getStarPos()*30);
		for (int x = 0; x < 10; x++) for (int y = 0; y < 10; y++) {
			switch (mapData.get()->getMap()[x + 10*y]) {
			case 0:
				map[x][y].ini(asset::ground, tileSize * olc::vi2d(x, y));
				break;
			case 1:
				map[x][y].ini(asset::air, tileSize * olc::vi2d(x, y));
				break;
			}
		}
		for (int i = 0; i < 14; i++) {
			cmdSprt[i].ini(asset::forward, { 350, i * 20 -5});
		}
		for (int i = 0; i < coinPosList.size(); i++) {
			sprCoinList[coinPosList[i].x * 10 + coinPosList[i].y] = std::make_unique<shi::SimpleSprite>();
			sprCoinList[coinPosList[i].x * 10 + coinPosList[i].y]->animation = asset::aniCoin;
		}
		player.ini(asset::aniPlayerIdle, playerPos * tileSize);
		player.setSize(tileSize);
		currentAction = editCommand;
		cmdList.clear();
		programCount = 0;
		playerDir = right;
		loopCountList.clear();
		loopRteurnList.clear();
		animationTime = 0;
		currentCoinGet = 0;
		break;
	case editCommand:
		//指令編輯模式，接受玩家操作

		//滑鼠點擊左鍵，判斷玩家點了甚麼東西
		if (engine->GetMouse(0).bPressed) {
			olc::vi2d mousePos = engine->GetMousePos();

			if (mousePos.x > 300 && mousePos.x < 350) {
				//點擊控制元件時
				if (mousePos.y < 50) { //拉取前進止令
					onDrag = std::make_unique<shi::SimpleSprite>(asset::forward);
					onDragCmd = forward;
				}
				else if (mousePos.y < 100) { //拉取迴圈止令
					onDrag = std::make_unique<shi::SimpleSprite>(asset::loop);
					onDragCmd = loop_start;
				}
				else if (mousePos.y < 150) { //拉取左轉止令
					onDrag = std::make_unique<shi::SimpleSprite>(asset::left);
					onDragCmd = turn_left;
				}
				else if (mousePos.y < 200) { //拉取右轉止令
					onDrag = std::make_unique<shi::SimpleSprite>(asset::right);
					onDragCmd = turn_right;
				}
				else if (mousePos.y < 250 && cmdList.size()>0) {
					//點擊開始按鈕，切換到執行指令模式
					currentAction = execCommand;
					int loopCount = 0;
					for (int i = 0; i < cmdList.size(); i++) {
						if (cmdList[i].type == loop_start) loopCount++;
						else if (cmdList[i].type == loop_end) loopCount--;
						if (loopCount < 0) currentAction = editCommand;
					}
					if (loopCount > 0) currentAction = editCommand;
				}
			}
			else if (mousePos.x > 350) {
				//點擊指令列時
				int index = (engine->GetMouseY() - 15) / 20;
				if (index < cmdList.size()) {
					switch (cmdList[index].type) {
					case forward:
						onDragCmd = cmdList[index].type;
						onDrag = std::make_unique<shi::SimpleSprite>(asset::forward);
						break;
					case turn_left:
						onDragCmd = cmdList[index].type;
						onDrag = std::make_unique<shi::SimpleSprite>(asset::left);
						break;
					case turn_right:
						onDragCmd = cmdList[index].type;
						onDrag = std::make_unique<shi::SimpleSprite>(asset::right);
						break;
					}
				}
				if (onDragCmd != none) {
					cmdList.erase(cmdList.begin()+ index);
				}
			}
		}

		//拖拉狀態，讓拖曳的東西跟著滑鼠移動
		if (onDrag != nullptr) {
			if (engine->GetMouse(0).bHeld) {
				onDrag.get()->pos = engine->GetMousePos() - onDrag.get()->getSize() / 2;
				onDrag.get()->tint = olc::PixelF(1.0, 1.0, 1.0, 0.5);

				//指令拖到指令列上方時，預判放置指令的位置
				if (engine->GetMouseX() > 350 && 
					(mouseHoverIndex>=0 || 
						cmdList.size() < 13 || 
						onDragCmd != loop_start && cmdList.size() < 14)) 
				{
					mouseHoverIndex = (engine->GetMouseY() - 15) / 20;
					if (mouseHoverIndex < cmdList.size() && cmdList[mouseHoverIndex].type != none) {
						for (auto it = cmdList.begin(); it != cmdList.end(); it++) {
							if (it->type == none) {
								cmdList.erase(it);
								break;
							}
						}
						cmdList.insert(cmdList.begin() + mouseHoverIndex, none);
					}
				}
				else if (mouseHoverIndex >= 0) {
					for (auto it = cmdList.begin(); it != cmdList.end(); it++) {
						if (it->type == none) {
							cmdList.erase(it);
							break;
						}
					}
					mouseHoverIndex = -1;
				}
			}

			//放開拖曳的東西，判斷放在哪裡
			if (engine->GetMouse(0).bReleased) {
				if (mouseHoverIndex >= 0) {
					if (mouseHoverIndex < cmdList.size()) {
						//在指令列內，插入指令
						switch (onDragCmd) {
						case forward:
							cmdList.insert(cmdList.begin() + mouseHoverIndex, forward);
							break;
						case turn_left:
							cmdList.insert(cmdList.begin() + mouseHoverIndex, turn_left);
							break;
						case turn_right:
							cmdList.insert(cmdList.begin() + mouseHoverIndex, turn_right);
							break;
						case loop_start:
							cmdList.insert(cmdList.begin() + mouseHoverIndex, loop_end);
							cmdList.insert(cmdList.begin() + mouseHoverIndex, loop_start);
							break;
						}
					}else {
						//在指令列外，新增指令到尾端
						switch (onDragCmd) {
						case forward:
							cmdList.push_back(forward);
							break;
						case turn_left:
							cmdList.push_back(turn_left);
							break;
						case turn_right:
							cmdList.push_back(turn_right);
							break;
						case loop_start:
							cmdList.push_back(loop_start);
							cmdList.push_back(loop_end);
							break;
						}
					}
				}

				//結束拖曳狀態
				onDrag = nullptr;
				onDragCmd = none; 
				for (auto it = cmdList.begin(); it != cmdList.end(); it++) {
					if (it->type == none) {
						cmdList.erase(it);
						break;
					}
				}
				mouseHoverIndex = -1;
			}
		}

		//按下右鍵，刪除右側指令物件
		if (engine->GetMouse(1).bPressed && engine->GetMouseX() > 350) {
			int index = (engine->GetMouseY() - 15) / 20;
			if (index < cmdList.size()) {
				cmdList.erase(cmdList.begin() + index);
			}
		}
		break;
	case execCommand:
		//執行指令模式，玩家可點下重置按鈕回到編輯模式

		if(animationTime>0) { 
			//animationTime>0時不行指令，計算動作時間
			animationTime -= fElapsedTime;
			if (animationTime <= 0) {
				animationTime = 0;
				programCount++;
				lastPos = playerPos;
			}
		}
		else if (playerPos == mapData->getStarPos()) {
			//玩家到達終點時，進入下一關(通關畫面)
			currentAction = levelCleared;
		}
		else if (animationTime <= 0 && programCount< cmdList.size()) {
			//animationTime<=0時，根據programCount執行當前指令
			switch (cmdList[programCount].type) {
			case forward: //前進指令，根據面對方向移動主角，前方格子為0(地板)時才能前進
				switch (playerDir) {
				case up:
					if (playerPos.y != 0 &&
						mapData.get()->getMap()[playerPos.x + 10 * (playerPos.y - 1)] == 0)
						playerPos += getDir2d(playerDir);
					break;
				case down:
					if (playerPos.y != 9 && 
						mapData.get()->getMap()[playerPos.x + 10 * (playerPos.y + 1)] == 0)
						playerPos += getDir2d(playerDir);
					break;
				case left:
					if (playerPos.x != 0 && 
						mapData.get()->getMap()[playerPos.x - 1 + 10 * (playerPos.y)] == 0)
						playerPos += getDir2d(playerDir);
					break;
				case right:
					if (playerPos.x != 9 && 
						mapData.get()->getMap()[playerPos.x + 1 + 10 * (playerPos.y)] == 0)
						playerPos += getDir2d(playerDir);
					break;
				}
				//判斷前進後會不會吃到金幣
				for (int i = 0; i < coinPosList.size(); i++) {
					if (playerPos == coinPosList[i]) {
						coinPosList.erase(coinPosList.begin() + i);
						currentCoinGet++;
					}
				}
				break;
			case turn_left: //左轉指令
				switch (playerDir) {
				case up:
					playerDir = left;
					break;
				case down:
					playerDir = right;
					break;
				case left:
					playerDir = down;
					break;
				case right:
					playerDir = up;
					break;
				}
				break;
			case turn_right: //右轉指令
				switch (playerDir) {
				case up:
					playerDir = right;
					break;
				case down:
					playerDir = left;
					break;
				case left:
					playerDir = up;
					break;
				case right:
					playerDir = down;
					break;
				}
				break;
			case loop_start: //迴圈頭
				loopCountList.push_back(cmdList[programCount].loopCount-1);
				loopRteurnList.push_back(programCount);
				break;
			case loop_end: //迴圈尾
				int loopCount = loopCountList.back();
				loopCountList.pop_back();
				if (loopCount > 0) {
					programCount = loopRteurnList.back();
					loopCountList.push_back(loopCount - 1);
				} else {
					loopRteurnList.pop_back();
				}
				break;
			}
			//根據玩家方向改變圖案
			switch (playerDir)
			{
			case up:
				player.animation = asset::aniPlayerUp;
				break;
			case down:
				player.animation = asset::aniPlayerDown;
				break;
			case left:
				player.animation = asset::aniPlayerLeft;
				break;
			case right:
				player.animation = asset::aniPlayerRight;
				break;
			}
			animationTime = 0.5f;
		}

		//若指令執行完畢，進入等待
		if (programCount >= cmdList.size()) {
			loopCountList.clear();
			loopRteurnList.clear();
			animationTime = 0;
			player.animation = asset::aniPlayerIdle;
		}

		//若玩家按下重置按鈕，則重置遊戲回到執行前狀態
		if (engine->GetMouse(0).bPressed &&
			engine->GetMouseX() > 300 && engine->GetMouseX() < 350 &&
			engine->GetMouseY() > 250 && engine->GetMouseY() < 300) {
			playerPos = mapData->getSpawnPoint();
			lastPos = playerPos;
			playerDir = right;
			player.animation = asset::aniPlayerIdle;
			currentAction = editCommand;
			programCount = 0;
			loopCountList.clear();
			loopRteurnList.clear();
			animationTime = 0;
			coinPosList = mapData->getCoinPos();
			currentCoinGet = 0;
		}
		break;
	case GameState::levelCleared:
		//過關畫面
		if (engine->GetMouse(0).bPressed) {
			mapIndex++;
			currentAction = state_ini;
			totalCoinGet += currentCoinGet;
			currentCoinGet = 0;
			if (mapIndex == 9 || mapIndex == 8 && (totalCoinGet + currentCoinGet) < 81) return new SplashState();
		}
		break;
	}
	

	//顯示畫面階段，有執行draw()的圖像才會出現在畫面上
	engine->Clear({128,128,255});

	//畫出地圖方格(地板和天空))
	sprSea.draw(engine);
	for (int x = 0; x < 10; x++) for (int y = 0; y < 10; y++) {
		if(mapData.get()->getMap()[x + 10 * y] == 0) map[x][y].draw(engine);
	}
	sprBar.draw(engine);

	//畫出金幣
	for (int i = 0; i < coinPosList.size(); i++) {
		int index = coinPosList[i].x * 10 + coinPosList[i].y;
		sprCoinList[index]->pos = coinPosList[i] * 30 + olc::vi2d(5, 5);
		sprCoinList[index]->drawAnimation(engine, fElapsedTime);
		sprCoinList[index]->setSize({ 20,20 });
	}

	//畫出右側的指令列
	int inLoop = 0;
	for (int i = 0; i < cmdList.size(); i++) {
		switch (cmdList[i].type) {
		case forward:
			cmdSprt[i].setSprite(asset::sprForward);
			break;
		case turn_left:
			cmdSprt[i].setSprite(asset::sprLeft);
			break;
		case turn_right:
			cmdSprt[i].setSprite(asset::sprRight);
			break;
		case loop_start:
			cmdSprt[i].setSprite(asset::sprLoop_start);
			break;
		case loop_end:
			inLoop--;
			cmdSprt[i].setSprite(asset::sprLoop_end);
			break;
		}

		//在迴圈裡的指令右移，並畫出迴圈左側邊邊
		for (int j = 0; j < inLoop; j++) {
			if(j >= sprSideLineList.size()) sprSideLineList.push_back(std::make_unique<shi::SimpleSprite>(asset::loop_side));
			sprSideLineList[j]->pos = { 350 + j * 3,cmdSprt[i].pos.y };
			sprSideLineList[j]->draw(engine);
		}
		cmdSprt[i].pos.x = 350 + inLoop * 3;
		if (cmdList[i].type == loop_start) inLoop++;
		//執行中的指令顏色變暗
		if (i == programCount && currentAction == execCommand) cmdSprt[i].tint = olc::GREY;
		else cmdSprt[i].tint = olc::WHITE;
		//預計玩家放下指令的位置留空白
		if (cmdList[i].type == none) cmdSprt[i].tint = olc::BLANK;
		cmdSprt[i].draw(engine);
	}

	//畫出控制項元件
	sprForward.draw(engine);
	sprLoop.draw(engine);
	sprLeft.draw(engine);
	sprRight.draw(engine);
	if (currentAction == editCommand) sprStart.tint = olc::WHITE;
	else sprStart.tint = olc::DARK_GREY;
	sprStart.draw(engine);
	if (currentAction == editCommand) sprReset.tint = olc::DARK_GREY;
	else sprReset.tint = olc::WHITE;
	sprReset.draw(engine);
	sprStar.draw(engine);
	//畫出正在拖拉的元件
	if (onDrag != nullptr) onDrag.get()->draw(engine);

	//畫出主角，在執行時跟著指令移動
	if(animationTime>0 && cmdList[programCount].type == forward)
		player.pos = playerPos * tileSize - olc::vf2d(playerPos * tileSize - lastPos * tileSize) * animationTime * 2;
	else
		player.pos = playerPos * tileSize;
	player.drawAnimation(engine, fElapsedTime);

	engine->DrawStringDecal({ 2,2 }, "Level "+ std::to_string(mapIndex)+"\nCoin: "+std::to_string(totalCoinGet+currentCoinGet), olc::BLACK);

	if (currentAction == levelCleared) {
		if(mapIndex == 8 || mapIndex == 7 && (totalCoinGet+currentCoinGet) < 81){
			sprWin.draw(engine); 
			engine->DrawStringDecal({ 145,200 }, "Total Coins: " + std::to_string(totalCoinGet + currentCoinGet), olc::BLACK);
		}
		else sprNext.draw(engine);
	}

	return this;
}
