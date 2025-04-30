#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <Renderer.h>
#include <Texture.h>
#include <Log.h>

namespace Zefir
{
	class AnimatedTexture : public Texture
	{
	public:
		AnimatedTexture(const std::string& path, Renderer* renderer)
			: Texture(path, renderer)
		{
			m_NumberOfFrames = 3;
			m_FrameTime = 100.0f;
			m_FrameW = 50;
			m_FrameH = 53;
		}

		bool IsAnimated() override { return true; }

		Uint16 GetFrameW() { return m_FrameW; }
		Uint16 GetFrameH() { return m_FrameH; }
		Uint16 GetNumberOfFrames() { return m_NumberOfFrames; }

		float GetFrameTime() { return m_FrameTime; }

	private:
		Uint16 m_NumberOfFrames;
		float m_FrameTime; // Frame duration (in ms)
		Uint16 m_FrameW, m_FrameH;
	};
}