#pragma once

#include <core/math/Vector2.h>

namespace Zefir
{
    constexpr int PIXELS_PER_METER = 50.0f;

    // ZEFIR AXIS :
    // ORIGIN AT THE CENTER OF THE SCREEN
    // RIGHT HANDED - Y UP
    
    // Convert the position from world coordinates to camera related position
    inline Vector2 WorldToCamera(const Vector2& position, const Camera& cam)
    {
        return { position.x - cam.position.x, position.y - cam.position.y };
    }

    // Convert World Coordinates (meters) to screen coordinates (pixels).
    inline Vector2 WorldToScreenPosition(const Vector2& worldPos, int screenWidth, int screenHeight, const Camera& cam)
    {
        Vector2 pos = WorldToCamera(worldPos, cam);

        pos.x = (PIXELS_PER_METER + cam.zoom) * pos.x + screenWidth / 2;
        pos.y = screenHeight / 2 - (PIXELS_PER_METER + cam.zoom) * pos.y;

        return pos;
    }

    // Given the center position (world coordinates) of a rect and his size, create a SDL_Rect
    // that can be drawn on the screen.
    inline SDL_FRect WorldToScreenRect(const Vector2& center, const Vector2& size, const Camera& cam)
    {
        SDL_FRect rect = {
            center.x - (size.x / 2) * (PIXELS_PER_METER + cam.zoom), center.y - (size.y / 2) * (PIXELS_PER_METER + cam.zoom),
            size.x * (PIXELS_PER_METER + cam.zoom), size.y * (PIXELS_PER_METER + cam.zoom)
        };

        return rect;
    }

    // Convert Screen Coordinates (pixels) to World coordinates (pixels).
    inline Vector2 ScreenToWorld(const Vector2& screenPos, Window* window, const Camera& cam)
    {
        int screenWidth = window->GetWindowSettings().width;
        int screenHeight = window->GetWindowSettings().height;

        float METERS_PER_PIXEL = 1.0f / (PIXELS_PER_METER + cam.zoom);

        Vector2 pos;
        pos.x = screenPos.x * METERS_PER_PIXEL - screenWidth / 2 * METERS_PER_PIXEL;
        pos.y = (screenHeight / 2 - screenPos.y) * METERS_PER_PIXEL;
        pos += cam.position;

        return pos;
    }
}