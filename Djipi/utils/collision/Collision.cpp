#include <Collision.h>

namespace Djipi
{
	bool CheckCollisionAABB(SDL_FRect a, SDL_FRect b)
	{
		float leftA, rightA, topA, bottomA;
		float leftB, rightB, topB, bottomB;

		leftA = a.x;	rightA = a.x + a.w;
		topA = a.y;	bottomA = a.y + a.h;

		leftB = b.x;	rightB = b.x + b.w;
		topB = b.y;	bottomB = b.y + b.h;

		//If any of the sides from A are outside of B
		if (bottomA <= topB) return false;
		if (topA >= bottomB) return false;
		if (rightA <= leftB) return false;
		if (leftA >= rightB) return false;

		//If none of the sides from A are outside B
		return true;
	}
}