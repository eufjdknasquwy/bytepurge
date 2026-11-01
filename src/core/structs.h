#pragma once
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
            bool verbose = false;
            bool dry_run = false;
            bool yes = false;
    };
    inline Args args;
} // namespace core
