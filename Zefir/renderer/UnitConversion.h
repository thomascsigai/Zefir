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
    inline Vector2 WorldToScreenPosition(const Vector2& worldPos, std::size_t screenWidth, std::size_t screenHeight)
    {
        float x = PIXELS_PER_METER * worldPos.x + screenWidth / 2;
        float y = screenHeight / 2 - PIXELS_PER_METER * worldPos.y;
        return Vector2{ x, y };
    }

    // Convert Screen Coordinates (pixels) to World coordinates (pixels).
    inline Vector2 ScreenToWorld(const Vector2& screenPos, std::size_t screenWidth, std::size_t screenHeight)
    {
        float x = screenPos.x * METERS_PER_PIXEL - screenWidth / 2 * METERS_PER_PIXEL;
        float y = (screenHeight / 2 - screenPos.y) * METERS_PER_PIXEL;
        return Vector2{ x, y };
    }

}