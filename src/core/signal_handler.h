#pragma once
#include <atomic>
namespace core
{
    extern std::atomic<bool> g_shutdown_requested;
    void install_signal_handlers();
    int get_signal_pipe_fd();
    inline bool shutdown_requested()
    {
        return g_shutdown_requested.load(std::memory_order_relaxed);
    }
} // namespace core
