#include "core/signal_handler.h"
#include "core/enums.h"
#include "utils/console_logger.h"
#include <csignal>
#include <fcntl.h>
#include <unistd.h>
namespace core
{
    std::atomic<bool> g_shutdown_requested{false};
    namespace
    {
        std::atomic<int> g_sig_count{0};
        int g_signal_pipe[2] = {-1, -1};

        extern "C" void on_signal(int sig)
        {
            int n = g_sig_count.fetch_add(1) + 1;

            if (n >= 3)
            {
                ::_exit(130);
            }

            g_shutdown_requested.store(true, std::memory_order_relaxed);

            char c = static_cast<char>(sig);
            ssize_t r = ::write(g_signal_pipe[1], &c, 1);
            (void)r;
        }
    } // namespace
    void install_signal_handlers()
    {
        if (::pipe(g_signal_pipe) != 0)
        {
            utils::ConsoleLogger::log(LogLevel::Error, "Failed to create signal pipe");
            return;
        }
        ::fcntl(g_signal_pipe[0], F_SETFL, O_NONBLOCK);
        ::fcntl(g_signal_pipe[1], F_SETFL, O_NONBLOCK);

        struct sigaction sa{};
        sa.sa_handler = on_signal;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        ::sigaction(SIGINT, &sa, nullptr);
        ::sigaction(SIGTERM, &sa, nullptr);
    }
    int get_signal_pipe_fd()
    {
        return g_signal_pipe[0];
    }
} // namespace core
