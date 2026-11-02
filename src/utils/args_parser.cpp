#include "utils/args_parser.h"
#include "core/cleaner.h"
#include "core/cli_tools.h"
#include "core/config_loader.h"
#include "core/constants.h"
#include "core/enums.h"
#include "core/structs.h"
#include "utils/console_logger.h"
#include <string>
void utils::ArgsParser::parse(int &argc, char *argv[])
{
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
        else if (arg == "-l" || arg == "--list") core::args.list = true;
        else if (arg == "-V" || arg == "--verbose") core::args.verbose = true;
        else if (arg == "-q" || arg == "--quiet") core::args.quiet = true;
        else if (arg == "-n" || arg == "--dry-run") core::args.dry_run = true;
        else if (arg == "-y" || arg == "--yes") core::args.yes = true;
        else if (arg == "-c" || arg == "--clear") core::args.clear = true;
        else if (arg == SAFE_CATEGORY) core::args.clear_categories.push_back(core::DangerLevel::Safe);
        else if (arg == WARNING_CATEGORY) core::args.clear_categories.push_back(core::DangerLevel::Warning);
        else if (arg == UNKNOWN_CATEGORY) core::args.clear_categories.push_back(core::DangerLevel::Unknown);
        else if (arg == SYSTEM_CATEGORY) core::args.clear_categories.push_back(core::DangerLevel::System);
        else if (arg == USER_CATEGORY) core::args.clear_categories.push_back(core::DangerLevel::User);
        else if (arg == "--trash") core::args.trash = true;
        else
        {
            utils::ConsoleLogger::printmsg("Unknown parameter '" + arg + "', see --help or -h");
            std::exit(EXIT_CODE_ERR);
        }
    }
    if (core::args.list)
    {
        const std::map<std::string, core::DangerLevel> all_paths = core::cli::CliTools::list_all_categories();
        std::string size_str;
        for (const auto &[path, danger] : all_paths)
        {
            uintmax_t bytes = core::CacheCleaner::size(path);
            size_str = bytes == core::UNKNOWN_SIZE ? "Unknown size" : core::format_size(bytes);
            utils::ConsoleLogger::print_cache(10, "[" + core::ConfigLoader::danger_to_str(danger) + "]", path,
                                              size_str);
        }
        std::exit(EXIT_CODE_NO_ERRS);
    }
    if (core::args.clear)
    {
        if (core::args.clear_categories.empty())
        {
            utils::ConsoleLogger::printerr("'--clear' option is used, but no choosed categories were found");
            std::exit(EXIT_CODE_ERR);
        }
        for (const auto &category : core::args.clear_categories)
        {
            core::cli::CliTools::delete_category(category);
        }
    }
    if (core::args.trash) core::cli::CliTools::clear_trash();
}
void utils::ArgsParser::print_help()
{
    utils::ConsoleLogger::printmsg("Usage: " + std::string(PROJECT_NAME) + " [OPTION...]");
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
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-q, --quiet", "Log only warning and error messages");

    utils::ConsoleLogger::printmsg("");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "Clear options:", "");
    utils::ConsoleLogger::printmsg("");

    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-n, --dry-run",
                                         "Doesn't clear anything, only a preview");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-y, --yes", "Skips confirmations");
    utils::ConsoleLogger::printmsg("");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "-c, --clear", "Clear cache in x category");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "--trash", "Clear trash bin");

    utils::ConsoleLogger::printmsg("");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, "Categories:", "");
    utils::ConsoleLogger::printmsg("");

    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, SAFE_CATEGORY, "Safe category: safe to clear caches");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, WARNING_CATEGORY,
                                         "Warning category: caches that need caution");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, UNKNOWN_CATEGORY,
                                         "Unknown category: unsorted and unknown cache");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, SYSTEM_CATEGORY,
                                         "System category: system caches such as distribution package managers");
    utils::ConsoleLogger::print_help_msg(DEFAULT_HELP_FLAG_WIDTH, USER_CATEGORY, "User category");

    utils::ConsoleLogger::printmsg("");
}
