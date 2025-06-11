#pragma once

#include <core/math/Vector2.h>

namespace Zefir
{
    constexpr int PIXELS_PER_METER = 50.0f;
    constexpr float METERS_PER_PIXEL = 1.0f / PIXELS_PER_METER;

    // ZEFIR AXIS :
    // ORIGIN AT THE CENTER OF THE SCREEN
    // RIGHT HANDED - Y UP
    
    // Convert World Coordinates (meters) to screen coordinates (pixels).
    inline Vector2 WorldToScreenPosition(const Vector2& worldPos, Window* window)
    {
        int screenWidth, screenHeight;
        SDL_GetWindowSize(window->GetSDLWindow(), &screenWidth, &screenHeight);

        float x = PIXELS_PER_METER * worldPos.x + screenWidth / 2;
        float y = screenHeight / 2 - PIXELS_PER_METER * worldPos.y;
        return Vector2{ x, y };
    }

    // Given the center position (world coordinates) of a rect and his size, create a SDL_Rect
    // that can be drawn on the screen.
    inline SDL_Rect WorldToScreenRect(const Vector2& center, const Vector2& size)
    {
        SDL_Rect rect = {
            center.x - (size.x / 2) * PIXELS_PER_METER, center.y - (size.y / 2) * PIXELS_PER_METER,
            size.x * PIXELS_PER_METER, size.y * PIXELS_PER_METER
        };

        return rect;
    }

    // Convert Screen Coordinates (pixels) to World coordinates (pixels).
    inline Vector2 ScreenToWorld(const Vector2& screenPos, Window* window)
    {
        int screenWidth, screenHeight;
        SDL_GetWindowSize(window->GetSDLWindow(), &screenWidth, &screenHeight);

        float x = screenPos.x * METERS_PER_PIXEL - screenWidth / 2 * METERS_PER_PIXEL;
        float y = (screenHeight / 2 - screenPos.y) * METERS_PER_PIXEL;
        return Vector2{ x, y };
    }

    // Convert the position from world coordinates to camera related position
    inline Vector2 WorldToCamera(const Vector2& position, const Camera& cam)
    {
        return { position.x - cam.position.x, position.y - cam.position.y };
    }
}