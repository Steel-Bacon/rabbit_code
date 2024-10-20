#pragma once
#include "olcPixelGameEngine.h"

namespace shi {
	class State {
	public:
		std::shared_ptr<State> _newState;
		template<class T> 
		void swapState(){
			static_assert( std::is_base_of<State, T>::value );
			_newState = std::make_shared<T>();
		}
		virtual bool ini() = 0;
		virtual bool run(float fElapsedTime, olc::PixelGameEngine* engine) = 0;
	};

	class StateManager {
	private:
		std::shared_ptr<State> currentState;
		float targetTime = 0, accTime = 0;
	public:
		template<class T> 
		void setState() {
			static_assert( std::is_base_of<State, T>::value );
			currentState = std::make_shared<T>();
			currentState->ini();
		}
		bool run(float fElapsedTime, olc::PixelGameEngine* engine) {
			if(currentState->_newState != nullptr) {
				currentState = currentState->_newState;
				currentState->ini();
			}
			if(targetTime > 0) {
				accTime += fElapsedTime - targetTime;
				if(accTime < 0) std::this_thread::sleep_for(std::chrono::milliseconds( (int)(-accTime * 1024) ));
				if(accTime > targetTime) accTime = 0;
			}
			return currentState->run(fElapsedTime, engine);
		}
		void setFPS(int targetFPS = 0) {
			if(targetFPS > 0) targetTime = 1.0/targetFPS;
			else targetTime = 0;
		}
	};

	class SprAnima {
	public:
		struct _frame {
			std::shared_ptr<olc::Sprite> sprite;
			float duration;
		};
		std::vector<_frame> frameList;
		void addFrame(std::shared_ptr<olc::Sprite> sprite, float duration) {
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
		olc::vi2d size = {0,0};
		olc::vf2d scale = {1.0,1.0};
		olc::Pixel tint = olc::WHITE;
		SimpleSprite() {};
		SimpleSprite(const char* path, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			sprite = std::make_shared<olc::Sprite>(path);
			ini(sprite, pos, scale, tint); 
		}; 
		SimpleSprite(std::shared_ptr<olc::Sprite> sprite, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			ini(sprite, pos, scale, tint);
		};
		void ini(std::shared_ptr<olc::Sprite> sprite, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			this->pos = pos;
			this->scale = scale;
			this->tint = tint;
			setSprite(sprite);
		}; 
		void ini(std::shared_ptr<SprAnima> ani, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			this->pos = pos;
			this->scale = scale;
			this->tint = tint;
			setSprite(ani->frameList[0].sprite);
			animation = ani;
			aniDuration = animation->frameList[0].duration;
		};
		void draw(olc::PixelGameEngine* engine) {
			engine->DrawDecal(pos, decal.get(), scale, tint);
		}
		olc::vi2d getSize() {
			return size;
		}
		void setSize(olc::vi2d newSize) {
			size = newSize;
			scale = { (float)size.x / sprite->width, size.y / (float)sprite->height };
		}
		void setSprite(std::shared_ptr<olc::Sprite> newSprite) {
			sprite = newSprite;
			decal = std::make_unique<olc::Decal>(sprite.get());
			size = sprite->Size() * scale;
		}
		void runAnimation(float fElapsedTime) {
			aniDuration -= fElapsedTime;
			if (aniDuration <= 0) {
				aniIndex++;
				if (aniIndex >= animation->frameList.size()) aniIndex = 0;
				aniDuration = animation->frameList[aniIndex].duration;
				setSprite(animation->frameList[aniIndex].sprite);
			}
		}
		bool contain(olc::vi2d point) {
			return point.x >= pos.x && point.x <= pos.x + size.x && point.y >= pos.y && point.y <= pos.y + size.y;
		}
	};
}
