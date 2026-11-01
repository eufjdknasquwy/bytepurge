#include "cli_tools.h"
#include "core/cleaner.h"
#include "core/config_loader.h"
#include "core/enums.h"
#include <iostream>
#include <string>
bool core::cli::CliTools::ask_confirmation(const char *prompt)
{
    std::cout << prompt << " [y/N]: ";
    std::string answer;
    std::getline(std::cin, answer);

    std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer == "y";
}
void core::cli::CliTools::delete_category(core::DangerLevel danger)
{
    core::ConfigLoader::load_config();
    core::ConfigLoader::load_pm_config();
    auto dirty_paths = core::ConfigLoader::get_paths_by_danger(danger);
    std::vector<std::string> paths;

    for (const auto &[name, path] : dirty_paths)
    {
        if (!core::CacheCleaner::exists(path))
        {
            continue;
        }
        paths.push_back(path);
    }
    if (paths.size() <= 0)
    {
        std::cout << "No cache to clear" << "\n";
        return;
    }

    core::ClearOptions options;
    options.dry_run = core::args.dry_run;
    options.cli = true;

    if (danger == core::DangerLevel::Safe)
    {
        if (!core::args.yes)
        {
            std::cout << "About to clear " << paths.size() << " paths (Safe):\n";
            for (const auto &p : paths)
                std::cout << "  " << p << "\n";
            std::cout << "\n";
        }
        if (!core::args.yes && !options.dry_run)
        {
            if (!ask_confirmation("Continue?")) return;
        }

        core::CacheCleaner::sort_cache(paths, options);
        return;
    }

    if (!core::args.yes)
    {
        std::cout << "Warning: about to clear " << paths.size() << " paths:\n";
        for (const auto &p : paths)
            std::cout << "  " << p << "\n";
        std::cout << "\n";
    }
    if (!core::args.yes && !options.dry_run)
    {
        if (!ask_confirmation("Are you sure? This may break some programs")) return;

        if (!ask_confirmation("Totally sure?")) return;
    }

    std::cout << "\n";
    core::CacheCleaner::sort_cache(paths, options);
}
std::map<std::string, core::DangerLevel> core::cli::CliTools::list_all_categories()
{
    core::ConfigLoader::load_config();
    core::ConfigLoader::load_pm_config();

    auto safe_paths = core::ConfigLoader::get_paths_by_danger(core::DangerLevel::Safe);
    auto warning_paths = core::ConfigLoader::get_paths_by_danger(core::DangerLevel::Warning);
    auto unknown_paths = core::ConfigLoader::get_paths_by_danger(core::DangerLevel::Unknown);
    auto system_paths = core::ConfigLoader::get_paths_by_danger(core::DangerLevel::System);
    auto user_paths = core::ConfigLoader::get_paths_by_danger(core::DangerLevel::User);

    std::map<std::string, core::DangerLevel> all_paths;

    auto add_if_exists = [&all_paths](core::DangerLevel danger, const auto &paths)
    {
        for (const auto &[name, path] : paths)
        {
            if (core::CacheCleaner::exists(path))
            {
                all_paths[path] = danger;
            }
        }
    };

    add_if_exists(core::DangerLevel::Safe, safe_paths);
    add_if_exists(core::DangerLevel::Warning, warning_paths);
    add_if_exists(core::DangerLevel::Unknown, unknown_paths);
    add_if_exists(core::DangerLevel::System, system_paths);
    add_if_exists(core::DangerLevel::User, user_paths);

    return all_paths;
}
void core::cli::CliTools::clear_trash()
{
    core::ClearOptions options;
    options.dry_run = core::args.dry_run;
    options.cli = true;

    if (!ask_confirmation("Are you sure you want to clear trash bin?")) return;
    core::CacheCleaner::clear_trash_bin(options);
}
