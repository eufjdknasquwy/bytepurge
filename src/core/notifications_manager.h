#pragma once
namespace core
{
    class NotifyManager
    {
        public:
            NotifyManager() = delete;
            static void send_notification(const std::string &body,
                                          const std::string &title = std::string(PROJECT_GENERIC_NAME));

        private:
    };
} // namespace core
