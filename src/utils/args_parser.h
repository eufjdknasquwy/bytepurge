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

            static constexpr const char *SAFE_CATEGORY = "--safe";
            static constexpr const char *WARNING_CATEGORY = "--warning";
            static constexpr const char *UNKNOWN_CATEGORY = "--unknown";
            static constexpr const char *SYSTEM_CATEGORY = "--system";
            static constexpr const char *USER_CATEGORY = "--user";
    };
} // namespace utils
