#pragma once
#include <vector>

namespace shiMap {
	class MapData {
	public:
		virtual int* getMap() = 0;
		virtual olc::vi2d getSpawnPoint() = 0;
		virtual olc::vi2d  getStarPos() = 0;
		std::vector<olc::vi2d> coinPos;
		virtual std::vector<olc::vi2d> getCoinPos() = 0;
	};

	class testMap :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		testMap() {
			coinPos.reserve(2);
			coinPos.push_back({ 4,4 });
			coinPos.push_back({ 5,4 });
		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 3,3 };
		};
		olc::vi2d getStarPos()override {
			return { 5,5 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class level1Map :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		std::vector<olc::vi2d> coinPos;
		level1Map() {
			coinPos.reserve(2);
			coinPos.push_back({ 4,4 });
			coinPos.push_back({ 5,4 });
		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 3,4 };
		};
		olc::vi2d getStarPos()override {
			return { 6,4 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class level2Map :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,1,1,1,0,1,1,1},
		{1,1,1,1,1,1,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		level2Map() {
			coinPos.reserve(4);
			coinPos.push_back({ 4,3 });
			coinPos.push_back({ 5,3 });
			coinPos.push_back({ 6,3 });
			coinPos.push_back({ 6,4 });
		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 3,3 };
		};
		olc::vi2d getStarPos()override {
			return { 6,5 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class level3Map :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,1,1,1},
		{1,1,1,1,0,1,0,1,1,1},
		{1,1,1,1,0,0,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		level3Map() {
			coinPos.reserve(7);
			coinPos.push_back({ 4,3 });
			coinPos.push_back({ 5,3 });
			coinPos.push_back({ 6,3 });
			coinPos.push_back({ 6,4 });
			coinPos.push_back({ 6,5 });
			coinPos.push_back({ 5,5 });
			coinPos.push_back({ 4,5 });
		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 3,3 };
		};
		olc::vi2d getStarPos()override {
			return { 4,4 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class level4Map :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,1,1,1,1,1},
		{1,0,1,1,0,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,0,1,1,0,1,1},
		{1,1,1,1,0,1,1,0,1,1},
		{1,1,1,1,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		level4Map() {
			coinPos.reserve(14);
			coinPos.push_back({ 5,5 });
			coinPos.push_back({ 6,5 });
			coinPos.push_back({ 7,5 });
			coinPos.push_back({ 7,6 });
			coinPos.push_back({ 7,7 });
			coinPos.push_back({ 7,8 });
			coinPos.push_back({ 6,8 });
			coinPos.push_back({ 5,8 });
			coinPos.push_back({ 4,8 });
			coinPos.push_back({ 4,7 });
			coinPos.push_back({ 4,6 });
			coinPos.push_back({ 1,5 });
			coinPos.push_back({ 1,2 });
			coinPos.push_back({ 4,2 });

		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 4,5 };
		};
		olc::vi2d getStarPos()override {
			return { 4,3 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class level5Map :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,1,1},
		{1,0,1,1,0,1,1,0,1,1},
		{1,0,1,1,0,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,1,1},
		{1,0,1,1,0,1,1,0,1,1},
		{1,0,1,1,0,1,1,0,1,1},
		{1,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		level5Map() {
			coinPos.reserve(23);
			coinPos.push_back({ 5,5 });
			coinPos.push_back({ 6,5 });
			coinPos.push_back({ 7,5 });
			coinPos.push_back({ 7,7 });
			coinPos.push_back({ 7,8 });
			coinPos.push_back({ 5,8 });
			coinPos.push_back({ 4,8 });
			coinPos.push_back({ 4,7 });
			coinPos.push_back({ 4,6 });
			coinPos.push_back({ 3,5 });
			coinPos.push_back({ 2,5 });
			coinPos.push_back({ 1,5 });
			coinPos.push_back({ 1,6 });
			coinPos.push_back({ 1,8 });
			coinPos.push_back({ 2,8 });
			coinPos.push_back({ 1,3 });
			coinPos.push_back({ 1,2 });
			coinPos.push_back({ 3,2 });
			coinPos.push_back({ 4,2 });
			coinPos.push_back({ 4,3 });
			coinPos.push_back({ 4,4 });
			coinPos.push_back({ 6,2 });
			coinPos.push_back({ 7,2 });
		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 4,5 };
		};
		olc::vi2d getStarPos()override {
			return { 7,3 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class level6Map :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,0,1,1,1},
		{1,1,1,1,1,1,0,1,1,1},
		{1,1,1,1,1,1,0,1,1,1},
		{0,0,0,0,0,0,0,1,1,1},
		{1,1,1,0,1,1,0,1,1,1},
		{1,1,1,0,1,1,0,1,1,1},
		{1,1,1,0,0,0,0,0,0,0},
		{1,1,1,0,1,1,1,1,1,1},
		{1,1,1,0,1,1,1,1,1,1},
		{1,1,1,0,1,1,1,1,1,1}
		};
		level6Map() {
			coinPos.reserve(20);
			coinPos.push_back({ 7,6 });
			coinPos.push_back({ 8,6 });
			coinPos.push_back({ 9,6 });
			coinPos.push_back({ 6,5 });
			coinPos.push_back({ 6,4 });
			coinPos.push_back({ 6,3 });
			coinPos.push_back({ 6,2 });
			coinPos.push_back({ 6,1 });
			coinPos.push_back({ 6,0 });
			coinPos.push_back({ 0,3 });
			coinPos.push_back({ 1,3 });
			coinPos.push_back({ 2,3 });
			coinPos.push_back({ 3,3 });
			coinPos.push_back({ 4,3 });
			coinPos.push_back({ 5,3 });
			coinPos.push_back({ 3,4 });
			coinPos.push_back({ 3,5 });
			coinPos.push_back({ 3,6 });
			coinPos.push_back({ 3,7 });
			coinPos.push_back({ 3,8 });

		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 6,6 };
		};
		olc::vi2d getStarPos()override {
			return { 3,9 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class level7Map :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,0,1,1},
		{1,1,1,1,1,0,1,0,1,1},
		{1,1,1,1,1,0,1,0,1,1},
		{1,1,0,0,0,0,0,0,1,1},
		{1,1,0,1,0,1,1,1,1,1},
		{1,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		level7Map() {
			coinPos.reserve(11);
			coinPos.push_back({ 7,2 });
			coinPos.push_back({ 7,5 });
			coinPos.push_back({ 5,4 });
			coinPos.push_back({ 4,5 });
			coinPos.push_back({ 4,6 });
			coinPos.push_back({ 4,7 });
			coinPos.push_back({ 3,7 });
			coinPos.push_back({ 2,7 });
			coinPos.push_back({ 2,6 });
			coinPos.push_back({ 2,5 });
			coinPos.push_back({ 3,5 });
		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 4,2 };
		};
		olc::vi2d getStarPos()override {
			return { 5,3 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
	};

	class Bonus :public MapData {
	public:
		int mapData[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,1},
		{1,1,0,0,0,0,0,1,1,1},
		{1,1,0,0,0,0,0,1,1,1},
		{1,1,0,0,0,0,0,1,1,1},
		{1,1,0,0,0,0,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}
		};
		Bonus() {
			coinPos.reserve(19);
			coinPos.push_back({ 3,2 });
			coinPos.push_back({ 4,2 });
			coinPos.push_back({ 5,2 });
			coinPos.push_back({ 6,2 });
			coinPos.push_back({ 5,3 });
			coinPos.push_back({ 4,3 });
			coinPos.push_back({ 3,3 });
			coinPos.push_back({ 2,3 });
			coinPos.push_back({ 3,4 });
			coinPos.push_back({ 4,4 });
			coinPos.push_back({ 5,4 });
			coinPos.push_back({ 6,4 });
			coinPos.push_back({ 5,5 });
			coinPos.push_back({ 4,5 });
			coinPos.push_back({ 3,5 });
			coinPos.push_back({ 2,5 });
			coinPos.push_back({ 3,6 });
			coinPos.push_back({ 4,6 });
			coinPos.push_back({ 5,6 });
		}
		int* getMap() override {
			return &mapData[0][0];
		};
		olc::vi2d getSpawnPoint()override {
			return { 2,2 };
		};
		olc::vi2d getStarPos()override {
			return { 6,6 };
		};
		std::vector<olc::vi2d> getCoinPos()override {
			return coinPos;
		}
		// total 100 Coins
	};

	std::shared_ptr<MapData> maps[9] = {
		std::make_shared<testMap>(),
		std::make_shared<level1Map>(),
		std::make_shared<level2Map>(),
		std::make_shared<level3Map>(),
		std::make_shared<level4Map>(),
		std::make_shared<level5Map>(),
		std::make_shared<level6Map>(),
		std::make_shared<level7Map>(),
		std::make_shared<Bonus>()
	};
}