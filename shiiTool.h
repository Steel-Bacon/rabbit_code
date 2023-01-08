#pragma once
#include "olcPixelGameEngine.h"

namespace shi {
	class SprAnima {
	public:
		struct _frame {
			std::shared_ptr<olc::Sprite> sprite;
			double duration;
		};
		std::vector<_frame> frameList;
		void addFrame(std::shared_ptr<olc::Sprite> sprite, double duration) {
			frameList.push_back({ sprite,duration });
		}
	};

	struct SimpleSprite {
		std::shared_ptr<olc::Sprite> sprite;
		std::unique_ptr<olc::Decal> decal;
		std::shared_ptr<SprAnima> animation = nullptr;
		int aniIndex = 0;
		float aniDuration = 0.0;
		olc::vi2d pos;
		olc::vf2d scale = {1.0,1.0};
		olc::Pixel tint = olc::WHITE;
		SimpleSprite() {};
		SimpleSprite(const char* path, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			ini(path, pos, scale, tint); 
		}; 
		SimpleSprite(std::shared_ptr<olc::Sprite> sprite, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			ini(sprite, pos, scale, tint);
		};
		void ini(const char* path, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			this->pos = pos;
			this->scale = scale;
			this->tint = tint;
			sprite = std::make_shared<olc::Sprite>(path);
			decal = std::make_unique<olc::Decal>(sprite.get());
		}; 
		void ini(std::shared_ptr<olc::Sprite> sprite, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			this->pos = pos;
			this->scale = scale;
			this->tint = tint;
			this->sprite = sprite;
			decal = std::make_unique<olc::Decal>(sprite.get());
		}; 
		void ini(std::shared_ptr<SprAnima> ani, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			this->pos = pos;
			this->scale = scale;
			this->tint = tint;
			this->sprite = ani->frameList[0].sprite;
			decal = std::make_unique<olc::Decal>(sprite.get());
			animation = ani;
		};
		void draw(olc::PixelGameEngine* engine) {
			engine->DrawDecal(pos, decal.get(), scale, tint);
		}
		olc::vi2d getSize() {
			return olc::vi2d(sprite.get()->width * scale.x, sprite.get()->height * scale.y);
		}
		void setSize(olc::vi2d size) {
			scale = { (float)size.x / sprite.get()->width, size.y / (float)sprite.get()->height };
		}
		void setSprite(std::shared_ptr<olc::Sprite> newSprite) {
			sprite = newSprite;
			decal = std::make_unique<olc::Decal>(sprite.get());
		}
		void drawAnimation(olc::PixelGameEngine* engine, float fElapsedTime) {
			if (animation != nullptr) {
				aniDuration -= fElapsedTime;
				if (aniDuration <= 0) {
					aniIndex++;
					if (aniIndex >= animation->frameList.size()) aniIndex = 0;
					aniDuration = animation->frameList[aniIndex].duration;
				}
				sprite = animation->frameList[aniIndex].sprite;
				decal = std::make_unique<olc::Decal>(sprite.get());
			}
			draw(engine);
		}
	};
}
