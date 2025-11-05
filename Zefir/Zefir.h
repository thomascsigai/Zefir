#pragma once

// Used by applications to call Zefir components

// Core components
#include <core/window/Window.h>
#include <core/debug/Log.h>
#include <core/math/Vector2.h>
#include <core/time/Timer.h>
#include <core/app/Application.h>
#include <core/Engine.h>

// Resource manager components
#include <resource/ResourceManager.h>
#include <resource/IResource.h>
#include <resource/types/Texture.h>
#include <resource/types/AnimatedTexture.h>
#include <resource/types/Sound.h>
#include <resource/types/Font.h>
// -- Resources Metadata
#include <resource/types/meta/AnimationMeta.h>

// Renderer components
#include <renderer/Renderer.h>

// Scene components
#include <scene/GameObject.h>
#include <scene/Transform2D.h>

// Sound components
#include <sound/SoundManager.h>

// Physics components

// Thirdparty libraries
// -- SDL2
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>