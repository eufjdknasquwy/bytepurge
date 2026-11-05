#pragma once
#include <filesystem>
namespace fs = std::filesystem;
namespace core
{
    fs::path get_home_dir();
    fs::path get_categories_dir();
    fs::path get_user_categories_dir();
    fs::path get_package_managers_dir();
    fs::path get_css_style_path();
    std::string load_embedded_string(const std::string &resource_path);
    std::string format_size(std::uintmax_t bytes);
    std::string expand_tilde(const std::string &path);

    inline constexpr int MIN_WIN_WIDTH = 650;
    inline constexpr int MIN_WIN_HEIGHT = 550;

    inline constexpr int DEFAULT_WIN_WIDTH = 750;
    inline constexpr int DEFAULT_WIN_HEIGHT = 650;

    inline constexpr int DEFAULT_FORCE_EXIT_TIMEOUT = 10;

    inline constexpr const char *DEFAULT_INTERRUPT_MESSAGE =
        "Shutdown requested by user, finishing current operation safely...";

    inline constexpr std::uintmax_t UNKNOWN_SIZE = UINT32_MAX;

    inline constexpr const char *DEFAULT_CATEGORIES_PATH = "/org/example/bytepurge/categories.json";
    inline constexpr const char *DEFAULT_PACKAGE_MANAGERS_PATH = "/org/example/bytepurge/package_managers.json";
    inline constexpr const char *DEFAULT_APP_STYLE_PATH = "/org/example/bytepurge/app_style.css";
    inline constexpr const char *DEFAULT_USER_CATEGORIES_TEMPLATE_PATH =
        "/org/example/bytepurge/user_categories_template.json";
    inline constexpr const char *DEFAULT_USER_CATEGORIES_PATH = "~/.config/bytepurge/user_categories.json";
    inline constexpr const char *DEFAULT_SETTINGS_PATH = "~/.config/bytepurge/settings.json";
} // namespace core
