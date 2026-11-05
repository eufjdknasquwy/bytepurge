#pragma once
#include "core/enums.h"
#include "core/structs.h"
#include <nlohmann/json_fwd.hpp>
#include <string>
using json = nlohmann::json;
namespace core
{
    struct CacheEntry
    {
            std::string name = "";
            std::string desc = "";
            std::string path = "";
            std::string type = "";
            std::string command = "";
            DangerLevel danger = DangerLevel::Unknown;
            bool root = false;
    };
    struct Settings
    {
            bool delete_to_trash = false;
    };
    struct Config
    {
            std::vector<CacheEntry> entries;
            Settings settings;
    };
    class ConfigLoader
    {
        public:
            ConfigLoader() = delete;
            static void load_config();
            static void load_pm_config();
            static std::map<std::string, std::string> get_paths_by_danger(core::DangerLevel danger);
            static const core::Config &get_config()
            {
                return s_config;
            }
            static std::string danger_to_str(core::DangerLevel d);
            static void export_report_to_json(std::ofstream &report_file, core::ClearReport &clear_report);
            static void save_settings(Settings &settings);

        private:
            static core::Config s_config;

            static void fill_cache_entry(core::CacheEntry &cache, const json &entry, core::DangerLevel danger);
            static DangerLevel str_to_danger(const std::string_view d);

            static void load_user_config();
            static void ensure_user_config_exists();

            static void load_settings();
            static void ensure_settings_exist();

            static int load_json_file(json &json_config, const std::string &path);
            static json load_embedded_json(const std::string &resource_path);
            static void export_to_json(std::ofstream &file, json &j);
    };
} // namespace core
