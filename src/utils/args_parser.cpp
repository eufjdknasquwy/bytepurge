#include "utils/args_parser.h"
#include "core/cli_tools.h"
#include "core/config_loader.h"
#include "core/enums.h"
#include "core/structs.h"
#include "utils/console_logger.h"
#include <string>
void utils::ArgsParser::parse(int &argc, char *argv[])
{
    std::vector<const char *> s_actions;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            print_help();
            std::exit(EXIT_CODE_NO_ERRS);
        }
        else if (arg == "-v" || arg == "--version")
        {
            utils::ConsoleLogger::printmsg(std::string(PROJECT_NAME) + " v" + std::string(PROJECT_VERSION));
            std::exit(EXIT_CODE_NO_ERRS);
        }
        else if (arg == "-t" || arg == "--tray") core::args.tray = true;
        else if (arg == "-l" || arg == "--list")
        {
            const std::map<std::string, core::DangerLevel> all_paths = core::cli::CliTools::list_all_categories();
            for (const auto &[path, danger] : all_paths)
            {
                utils::ConsoleLogger::print_help_msg(10, "[" + core::ConfigLoader::danger_to_str(danger) + "]", path);
            }
            std::exit(EXIT_CODE_NO_ERRS);
        }
        else if (arg == "-V" || arg == "--verbose") core::args.verbose = true;
        else if (arg == "-n" || arg == "--dry-run") core::args.dry_run = true;
        else if (arg == "-y" || arg == "--yes") core::args.yes = true;
        else if (arg == CLEAR_SAFE) s_actions.push_back(CLEAR_SAFE);
        else if (arg == CLEAR_WARNING) s_actions.push_back(CLEAR_WARNING);
        else if (arg == CLEAR_UNKNOWN) s_actions.push_back(CLEAR_UNKNOWN);
        else if (arg == CLEAR_SYSTEM) s_actions.push_back(CLEAR_SYSTEM);
        else if (arg == CLEAR_USER) s_actions.push_back(CLEAR_USER);
        else if (arg == "--trash") s_actions.push_back("--trash");
        else
        {
            utils::ConsoleLogger::printmsg("Unknown parameter '" + arg + "', see --help or -h");
            std::exit(EXIT_CODE_ERR);
        }
    }
    if (s_actions.empty()) return;
    for (std::string_view action : s_actions)
    {
        if (action == CLEAR_SAFE) core::cli::CliTools::delete_category(core::DangerLevel::Safe);
        if (action == CLEAR_WARNING) core::cli::CliTools::delete_category(core::DangerLevel::Warning);
        if (action == CLEAR_UNKNOWN) core::cli::CliTools::delete_category(core::DangerLevel::Unknown);
        if (action == CLEAR_SYSTEM) core::cli::CliTools::delete_category(core::DangerLevel::System);
        if (action == CLEAR_USER) core::cli::CliTools::delete_category(core::DangerLevel::User);
        if (action == "--trash") core::cli::CliTools::clear_trash();
    }
    std::exit(EXIT_CODE_NO_ERRS);
}
void utils::ArgsParser::print_help()
{
    utils::ConsoleLogger::printmsg("Usage: cache-cleaner [OPTION...]");
    utils::ConsoleLogger::printmsg("");
    utils::ConsoleLogger::printmsg("Options:");

    utils::ConsoleLogger::printmsg("");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "General options:", "");
    utils::ConsoleLogger::printmsg("");

    // parameters with descriptions
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-h, --help", "Show this help message");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-v, --version", "Show cache cleaner version");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-t, --tray", "Launch program in tray");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-l, --list", "List available to clear caches");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-V, --verbose", "Include debug messages in logs");

    utils::ConsoleLogger::printmsg("");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "Clear options:", "");
    utils::ConsoleLogger::printmsg("");

    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-n, --dry-run [--clear-category]",
                                         "Doesn't clear anything, only a preview");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-y, --yes", "Skips confirmations");
    utils::ConsoleLogger::printmsg("");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, CLEAR_SAFE, "Clear cache in safe category");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, CLEAR_WARNING, "Clear cache in warning category");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, CLEAR_UNKNOWN, "Clear cache in unknown category");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, CLEAR_SYSTEM, "Clear cache in system category");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, CLEAR_USER, "Clear cache in user category");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "--trash", "Clear trash bin");

    utils::ConsoleLogger::printmsg("");
}
