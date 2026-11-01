#pragma once
#include "core/enums.h"
namespace core::cli
{
    class CliTools
    {
        public:
            CliTools() = delete;
            static void delete_category(core::DangerLevel danger);
            static std::map<std::string, core::DangerLevel> list_all_categories();
            static void clear_trash();

        private:
            static bool ask_confirmation(const char *prompt);
    };
} // namespace core::cli
