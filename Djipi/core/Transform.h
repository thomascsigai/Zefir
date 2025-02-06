#pragma once

#include <SDL.h>

struct Transform
{
	float x = 0, y = 0;
	float w = 0, h = 0;

	SDL_FRect collider = {};

	void SetPosition(float _x, float _y)
	{
		x = _x; y = _y;
		UpdateCollider();
	}

	void SetSize(float _w, float _h)
	{
		w = _w; h = _h;
		UpdateCollider();
	}

	void UpdateCollider() { collider = { x, y, w, h }; }
};