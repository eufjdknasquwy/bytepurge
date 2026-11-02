#pragma once
#include "core/enums.h"
namespace core
{
    struct ClearReport
    {
            std::vector<std::string> paths;
            std::map<std::string, int> commands;
            std::uintmax_t freed_bytes = 0;
    };
    struct ClearOptions
    {
            bool dry_run = false;
            bool cli = false;
            bool preview = false;
    };
    struct Args
    {
            bool tray = false;
            bool list = false;
            bool verbose = false;
            bool quiet = false;

            bool dry_run = false;
            bool yes = false;

            bool clear = false;
            std::vector<core::DangerLevel> clear_categories;
            bool trash = false;
    };
    inline Args args;
} // namespace core
