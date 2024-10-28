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
			std::shared_ptr<olc::Renderable> renderable;
			float duration;
		};
		std::vector<_frame> frameList;
		float fullLoopDuration = 0.0;
		void addFrame(const char* path, float duration) {
			std::shared_ptr<olc::Renderable> renderable = std::make_shared<olc::Renderable>();
			renderable->Load(path);
			addFrame(renderable, duration);
		}
		void addFrame(std::shared_ptr<olc::Renderable> renderable, float duration) {
			frameList.push_back({ renderable,duration });
			fullLoopDuration += duration;
		}
	};

	struct SimpleSprite {
		std::shared_ptr<olc::Renderable> renderable;
		std::shared_ptr<SprAnima> animation = nullptr;
		int aniIndex = 0;
		float aniDuration = 0.0;
		olc::vi2d pos;
		olc::vi2d size = {0,0};
		olc::vf2d scale = {1.0,1.0};
		olc::Pixel tint = olc::WHITE;
		SimpleSprite() {};
		SimpleSprite(const char* path, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			renderable = std::make_shared<olc::Renderable>();
			renderable->Load(path);
			ini(renderable, pos, scale, tint); 
		}; 
		SimpleSprite(std::shared_ptr<olc::Renderable> renderable, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			ini(renderable, pos, scale, tint);
		};
		void ini(std::shared_ptr<olc::Renderable> renderable, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			this->pos = pos;
			this->scale = scale;
			this->tint = tint;
			setRenderable(renderable);
		}; 
		void ini(std::shared_ptr<SprAnima> ani, const olc::vi2d& pos = { 0,0 }, const olc::vf2d& scale = { 1.0f,1.0f }, const olc::Pixel& tint = olc::WHITE) {
			this->pos = pos;
			this->scale = scale;
			this->tint = tint;
			setAnimation(ani);
		};
		void draw(olc::PixelGameEngine* engine) {
			engine->DrawDecal(pos, renderable->Decal(), scale, tint);
		}
		olc::vi2d getSize() {
			return size;
		}
		void setSize(olc::vi2d newSize) {
			size = newSize;
			if(renderable != nullptr) scale = { (float)size.x / renderable->Sprite()->width, (float)size.y / renderable->Sprite()->height };
		}
		void setRenderable(std::shared_ptr<olc::Renderable> newRenderable) {
			renderable = newRenderable;
			size = renderable->Sprite()->Size() * scale;
		}
		void setAnimation(std::shared_ptr<SprAnima> newAnimation) {
			animation = newAnimation;
			aniIndex = 0;
			aniDuration = animation->frameList[0].duration;
			setRenderable(animation->frameList[0].renderable);
		}
		void runAnimation(float fElapsedTime) {
			aniDuration -= fElapsedTime;
			if (aniDuration <= 0) {
				aniIndex++;
				if (aniIndex >= animation->frameList.size()) aniIndex = 0;
				aniDuration += animation->frameList[aniIndex].duration;
				setRenderable(animation->frameList[aniIndex].renderable);
			}
		}
		bool contain(olc::vi2d point) {
			return point.x >= pos.x && point.x <= pos.x + size.x && point.y >= pos.y && point.y <= pos.y + size.y;
		}
		bool collide(SimpleSprite& spr) {
			return collide(spr.pos, spr.size);
		}
		bool collide(olc::vi2d _pos, olc::vi2d _size) {
			return !(_pos.x + _size.x < pos.x //onLeft
				|| _pos.x > pos.x + size.x //onRight
				|| _pos.y + _size.y < pos.y //above
				|| _pos.y > pos.y + size.y); //below
		}
	};
}
