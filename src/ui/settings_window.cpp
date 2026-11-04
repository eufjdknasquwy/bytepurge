#include "ui/settings_window.h"
#include "core/config_loader.h"
#include "ui/ui_helper.h"
ui::SettingsWindow::SettingsWindow(const core::Config &config) : m_config(config)
{
    m_dialog = Gtk::manage(new Gtk::Dialog(std::string(PROJECT_GENERIC_NAME) + " Settings"));
    m_dialog->set_default_size(400, 300);
    m_dialog->add_button("Cancel", Gtk::RESPONSE_CANCEL);
    m_dialog->add_button("Save", Gtk::RESPONSE_OK);

    m_content_area = m_dialog->get_content_area();
    m_content_area->set_spacing(5);
    ui::UIHelper::set_margin(*m_content_area, 10);

    fill_settings();
}
void ui::SettingsWindow::fill_settings()
{
    m_trash_checkbox = Gtk::manage(new Gtk::CheckButton("Delete caches to trash instead of deleting them permanently"));
    m_trash_checkbox->set_active(m_config.settings.delete_to_trash);
    m_content_area->pack_start(*m_trash_checkbox, false, false, 0);
}
void ui::SettingsWindow::open_settings_window(Gtk::Window &parent)
{
    m_dialog->set_parent(parent);

    m_dialog->show_all();

    if (m_dialog->run() == Gtk::RESPONSE_OK)
    {
        on_save();
    }

    close_settings_window();
}
void ui::SettingsWindow::close_settings_window()
{
    m_dialog->hide();
}
void ui::SettingsWindow::on_save()
{
    core::Settings updated_settings;

    updated_settings.delete_to_trash = m_trash_checkbox->get_active();

    core::ConfigLoader::save_settings(updated_settings);
}
