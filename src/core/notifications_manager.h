#pragma once
namespace core
{
    class NotifyManager
    {
        public:
            NotifyManager() = delete;
            static void send_notification(const std::string &body, const std::string &title = "Cache cleaner");

        private:
    };
} // namespace core
