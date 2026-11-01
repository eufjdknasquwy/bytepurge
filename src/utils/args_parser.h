#pragma once
namespace utils
{
    class ArgsParser
    {
        public:
            ArgsParser() = delete;
            static void parse(int &argc, char *argv[]);
            static void print_help();

        private:
            static constexpr int DEFAULT_HELP_FLAG_WIDTH = 40;
            static constexpr int EXIT_CODE_NO_ERRS = 0;
            static constexpr int EXIT_CODE_ERR = 1;

            static constexpr const char *CLEAR_SAFE = "--clear-safe";
            static constexpr const char *CLEAR_WARNING = "--clear-warning";
            static constexpr const char *CLEAR_UNKNOWN = "--clear-unknown";
            static constexpr const char *CLEAR_SYSTEM = "--clear-system";
            static constexpr const char *CLEAR_USER = "--clear-user";
    };
} // namespace utils
