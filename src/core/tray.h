#pragma once
#include <functional>
#include <gtkmm.h>
#include <libayatana-appindicator3-0.1/libayatana-appindicator/app-indicator.h>
namespace ui
{
    class MainWindow;
}
namespace core
{
    class Tray
    {
        public:
            explicit Tray(ui::MainWindow &main_window);
            ~Tray();

        private:
            static constexpr const char *DEFAULT_WINDOW_MAXIMIZE_ICON = "window-maximize";
            static constexpr const char *DEFAULT_WINDOW_MINIMIZE_ICON = "window-minimize";
            static constexpr const char *DEFAULT_APPLICATION_QUIT_ICON = "application-exit";

            AppIndicator *m_indicator = nullptr;
            Gtk::Menu *m_menu = nullptr;
            ui::MainWindow &m_main_window;

            void add_items();
            Gtk::MenuItem *create_menu_item(const std::string &text, const std::string &icon_name,
                                            std::function<void()> callback);
    };
} // namespace core
