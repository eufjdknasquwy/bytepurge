#include "core/constants.h"
#include "utils/console_logger.h"
#include <filesystem>
#include <glibmm.h>
namespace fs = std::filesystem;
namespace core
{
    fs::path get_home_dir() // возвращает /home/user
    {
        return Glib::get_home_dir();
    }
    fs::path project_root()
    {
#ifdef PROJECT_ROOT_DIR
        return fs::path(PROJECT_ROOT_DIR);
#else
        auto cwd = fs::current_path();
        if (cwd.filename() == "build" || cwd.filename() == "bin")
        {
            return cwd.parent_path();
        }
        return cwd;
#endif
    }
    fs::path get_categories_dir()
    {
        return project_root() / "src" / "config" / "categories.json";
    }
    fs::path get_user_categories_dir()
    {
        return get_home_dir() / ".config" / "cache-cleaner" / "user_categories.json";
    }
    fs::path get_package_managers_dir()
    {
        return project_root() / "src" / "config" / "package_managers.json";
    }
    fs::path get_css_style_path()
    {
        return project_root() / "src" / "config" / "app_style.css";
    }
    std::string load_embedded_string(const std::string &resource_path)
    {
        try
        {
            GError *error = nullptr;
            GBytes *bytes = g_resources_lookup_data(resource_path.c_str(), G_RESOURCE_LOOKUP_FLAGS_NONE, &error);

            if (error)
            {
                utils::ConsoleLogger::log(core::LogLevel::Error, "Failed to load resource: " + resource_path);
                utils::ConsoleLogger::log(core::LogLevel::Error, std::string("Message: ") + error->message);
                g_error_free(error);
                utils::ConsoleLogger::flush_errors_to_ui();
                return "";
            }

            if (!bytes) return "";

            gsize size;
            gconstpointer data = g_bytes_get_data(bytes, &size);
            std::string result(static_cast<const char *>(data), size);

            g_bytes_unref(bytes);
            return result;
        }
        catch (std::exception &e)
        {
            utils::ConsoleLogger::log(core::LogLevel::Error,
                                      "Unexpected error occured while trying to parse settings resource: ");
            utils::ConsoleLogger::log(core::LogLevel::Error, std::string("Message: ") + e.what());
            utils::ConsoleLogger::flush_errors_to_ui();
            return nullptr;
        }
    }
    std::string format_size(std::uintmax_t bytes)
    {
        const char *units[] = {"B", "KB", "MB", "GB", "TB"};
        double size = static_cast<double>(bytes);
        int unit = 0;

        while (size >= 1024.0 && unit < 4)
        {
            size /= 1024.0;
            ++unit;
        }

        char buf[32];
        if (unit == 0) std::snprintf(buf, sizeof(buf), "%ju %s", bytes, units[unit]);
        else if (unit == 1) std::snprintf(buf, sizeof(buf), "%.0f %s", size, units[unit]);
        else std::snprintf(buf, sizeof(buf), "%.1f %s", size, units[unit]);

        return buf;
    }
} // namespace core
