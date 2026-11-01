#pragma once
#include "core/config_loader.h"
#include "core/structs.h"
#include <cstdint>
#include <future>
namespace core
{
    class CacheCleaner
    {
        public:
            CacheCleaner() = delete;

            static core::ClearReport sort_cache(const std::vector<std::string> &paths_to_clear,
                                                const core::ClearOptions &options = {});
            static bool exists(const std::string &path_str);
            static uintmax_t size(const std::string &path_str);
            static std::future<std::uintmax_t> clear_trash_bin(const core::ClearOptions &options = {});

        private:
            static core::ClearReport s_del_result;
            static std::mutex s_del_result_mutex;
            static const Config &s_config;

            static std::string expand_tilde(const std::string &path);
            static void clear_cache(const std::vector<std::string> &paths_to_clear, const core::ClearOptions &options);

            static std::future<void> run_command(const std::string &command, const core::ClearOptions &options);
            static std::future<void> delete_paths(const std::string &path, const core::ClearOptions &options);
            static std::future<void> del_to_trash(const std::string &path, const core::ClearOptions &options);

            static std::future<void> void_future();
    };
} // namespace core
