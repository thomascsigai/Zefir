#pragma once

#include <SDL.h>

namespace Zefir
{
    class Timer
    {
    public:
        Timer();

        void Start();
        void Stop();
        void Pause();
        void Unpause();

        Uint32 GetTicks() const;

        bool IsStarted() const;
        bool IsPaused() const;

    private:
        Uint32 m_StartTicks;
        Uint32 m_PausedTicks;

        bool m_Paused;
        bool m_Started;
    };
}