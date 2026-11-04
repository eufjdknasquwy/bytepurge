#pragma once
#include "core/config_loader.h"
namespace ui
{
    class SettingsWindow
    {
        public:
            SettingsWindow(const core::Config &config);
            void open_settings_window(Gtk::Window &parent);
            void close_settings_window();

        private:
            const core::Config &m_config;
            Gtk::Dialog *m_dialog = nullptr;
            Gtk::Box *m_content_area = nullptr;

            Gtk::CheckButton *m_trash_checkbox = nullptr;

            void fill_settings();
            void on_save();
    };
} // namespace ui
