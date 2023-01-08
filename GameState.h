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
	//��l�ƪ���ŧi
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
	//���O�����ŧi
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
	//�D�������ŧi
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
	//�C�����A�����ŧi
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
	int mapIndex = 1;//�]�w��l�a��
	int totalCoinGet = 0;
	int currentCoinGet = 0;

public:
	State* run(float fElapsedTime, olc::PixelGameEngine* engine) override;
};

//-----------------------�H�W���ŧi-----------------------------
//-----------------------�H�U����@-----------------------------

State* SplashState::run(float fElapsedTime, olc::PixelGameEngine* engine) {
	//�}�ҹC������ܥv�ܩi�Ӽ�
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
		//��l�ƶ��q�A�u����@��
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
			//�C������
		}
		else mapData = shiMap::maps[mapIndex];//���J�a��
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
		//���O�s��Ҧ��A�������a�ާ@

		//�ƹ��I������A�P�_���a�I�F�ƻ�F��
		if (engine->GetMouse(0).bPressed) {
			olc::vi2d mousePos = engine->GetMousePos();

			if (mousePos.x > 300 && mousePos.x < 350) {
				//�I��������
				if (mousePos.y < 50) { //�Ԩ��e�i��O
					onDrag = std::make_unique<shi::SimpleSprite>(asset::forward);
					onDragCmd = forward;
				}
				else if (mousePos.y < 100) { //�Ԩ��j���O
					onDrag = std::make_unique<shi::SimpleSprite>(asset::loop);
					onDragCmd = loop_start;
				}
				else if (mousePos.y < 150) { //�Ԩ������O
					onDrag = std::make_unique<shi::SimpleSprite>(asset::left);
					onDragCmd = turn_left;
				}
				else if (mousePos.y < 200) { //�Ԩ��k���O
					onDrag = std::make_unique<shi::SimpleSprite>(asset::right);
					onDragCmd = turn_right;
				}
				else if (mousePos.y < 250 && cmdList.size()>0) {
					//�I���}�l���s�A�����������O�Ҧ�
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
				//�I�����O�C��
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

		//��Ԫ��A�A���즲���F���۷ƹ�����
		if (onDrag != nullptr) {
			if (engine->GetMouse(0).bHeld) {
				onDrag.get()->pos = engine->GetMousePos() - onDrag.get()->getSize() / 2;
				onDrag.get()->tint = olc::PixelF(1.0, 1.0, 1.0, 0.5);

				//���O�����O�C�W��ɡA�w�P��m���O����m
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

			//��}�즲���F��A�P�_��b����
			if (engine->GetMouse(0).bReleased) {
				if (mouseHoverIndex >= 0) {
					if (mouseHoverIndex < cmdList.size()) {
						//�b���O�C���A���J���O
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
						//�b���O�C�~�A�s�W���O�����
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

				//�����즲���A
				onDrag.release();
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

		//���U�k��A�R���k�����O����
		if (engine->GetMouse(1).bPressed && engine->GetMouseX() > 350) {
			int index = (engine->GetMouseY() - 15) / 20;
			if (index < cmdList.size()) {
				cmdList.erase(cmdList.begin() + index);
			}
		}
		break;
	case execCommand:
		//������O�Ҧ��A���a�i�I�U���m���s�^��s��Ҧ�

		if(animationTime>0) { 
			//animationTime>0�ɤ�����O�A�p��ʧ@�ɶ�
			animationTime -= fElapsedTime;
			if (animationTime <= 0) {
				animationTime = 0;
				programCount++;
				lastPos = playerPos;
			}
		}
		else if (playerPos == mapData->getStarPos()) {
			//���a��F���I�ɡA�i�J�U�@��(�q���e��)
			currentAction = levelCleared;
		}
		else if (animationTime <= 0 && programCount< cmdList.size()) {
			//animationTime<=0�ɡA�ھ�programCount�����e���O
			switch (cmdList[programCount].type) {
			case forward: //�e�i���O�A�ھڭ����V���ʥD���A�e���l��0(�a�O)�ɤ~��e�i
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
				//�P�_�e�i��|���|�Y�����
				for (int i = 0; i < coinPosList.size(); i++) {
					if (playerPos == coinPosList[i]) {
						coinPosList.erase(coinPosList.begin() + i);
						currentCoinGet++;
					}
				}
				break;
			case turn_left: //������O
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
			case turn_right: //�k����O
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
			case loop_start: //�j���Y
				loopCountList.push_back(cmdList[programCount].loopCount-1);
				loopRteurnList.push_back(programCount);
				break;
			case loop_end: //�j���
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
			//�ھڪ��a��V���ܹϮ�
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

		//�Y���O���槹���A�i�J����
		if (programCount >= cmdList.size()) {
			loopCountList.clear();
			loopRteurnList.clear();
			animationTime = 0;
			player.animation = asset::aniPlayerIdle;
		}

		//�Y���a���U���m���s�A�h���m�C���^�����e���A
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
		//�L���e��
		if (engine->GetMouse(0).bPressed) {
			mapIndex++;
			currentAction = state_ini;
			totalCoinGet += currentCoinGet;
			currentCoinGet = 0;
			if (mapIndex == 9 || mapIndex == 8 && (totalCoinGet + currentCoinGet) < 81) return new SplashState();
		}
		break;
	}
	

	//��ܵe�����q�A������draw()���Ϲ��~�|�X�{�b�e���W
	engine->Clear({128,128,255});

	//�e�X�a�Ϥ��(�a�O�M�Ѫ�))
	sprSea.draw(engine);
	for (int x = 0; x < 10; x++) for (int y = 0; y < 10; y++) {
		if(mapData.get()->getMap()[x + 10 * y] == 0) map[x][y].draw(engine);
	}
	sprBar.draw(engine);

	//�e�X����
	for (int i = 0; i < coinPosList.size(); i++) {
		int index = coinPosList[i].x * 10 + coinPosList[i].y;
		sprCoinList[index]->pos = coinPosList[i] * 30 + olc::vi2d(5, 5);
		sprCoinList[index]->drawAnimation(engine, fElapsedTime);
		sprCoinList[index]->setSize({ 20,20 });
	}

	//�e�X�k�������O�C
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

		//�b�j��̪����O�k���A�õe�X�j�饪������
		for (int j = 0; j < inLoop; j++) {
			if(j >= sprSideLineList.size()) sprSideLineList.push_back(std::make_unique<shi::SimpleSprite>(asset::loop_side));
			sprSideLineList[j]->pos = { 350 + j * 3,cmdSprt[i].pos.y };
			sprSideLineList[j]->draw(engine);
		}
		cmdSprt[i].pos.x = 350 + inLoop * 3;
		if (cmdList[i].type == loop_start) inLoop++;
		//���椤�����O�C���ܷt
		if (i == programCount && currentAction == execCommand) cmdSprt[i].tint = olc::GREY;
		else cmdSprt[i].tint = olc::WHITE;
		//�w�p���a��U���O����m�d�ť�
		if (cmdList[i].type == none) cmdSprt[i].tint = olc::BLANK;
		cmdSprt[i].draw(engine);
	}

	//�e�X�������
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
	//�e�X���b��Ԫ�����
	if (onDrag != nullptr) onDrag.get()->draw(engine);

	//�e�X�D���A�b����ɸ�۫��O����
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