#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <AnimationMeta.h>

#include <Renderer.h>
#include <Texture.h>
#include <Log.h>

namespace Zefir
{
	class AnimatedTexture : public Texture
	{
	public:
		AnimatedTexture(const std::string& path, Renderer* renderer)
			: Texture(path, renderer), m_MetaData() {}

		bool Load() override;
		bool IsAnimated() override { return true; }

		Uint16 GetFrameW() const;
		Uint16 GetFrameH() const;
		Uint16 GetFrameCount() const;
		float GetFrameTime() const;

	private:
		AnimationData m_MetaData;
	};
}