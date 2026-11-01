#include "core/tray.h"
#include "ui/main_window.h"
#include <functional>
#include <gtkmm.h>
#include <libayatana-appindicator3-0.1/libayatana-appindicator/app-indicator.h>
core::Tray::Tray(ui::MainWindow &main_window) : m_main_window(main_window)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    m_indicator = app_indicator_new("cache-cleaner", "cache-cleaner", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
#pragma GCC diagnostic pop

    app_indicator_set_status(m_indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_icon_theme_path(m_indicator, "/usr/share/icons");

    m_menu = Gtk::manage(new Gtk::Menu());
    add_items();
    m_menu->show_all();

    app_indicator_set_menu(m_indicator, GTK_MENU(m_menu->gobj()));
}
core::Tray::~Tray()
{
    if (m_indicator)
    {
        g_object_unref(m_indicator);
    }
}
void core::Tray::add_items()
{
    m_menu->append(*create_menu_item("Show window", DEFAULT_WINDOW_MAXIMIZE_ICON,
                                     [this]()
                                     {
                                         m_main_window.hide_window();
                                         m_main_window.show_window();
                                     }));
    m_menu->append(
        *create_menu_item("Minimize window", DEFAULT_WINDOW_MINIMIZE_ICON, [this]() { m_main_window.hide_window(); }));
    m_menu->append(*create_menu_item("Scan cache", ui::MainWindow::DEFAULT_SCAN_CACHE_BUTTON_ICON,
                                     [this]() { m_main_window.scan_cache(); }));
    m_menu->append(*create_menu_item("Clear trash", ui::MainWindow::DEFAULT_CLEAR_TRASH_BUTTON_ICON,
                                     [this]() { m_main_window.clear_trash_bin(); }));
    m_menu->append(
        *create_menu_item("Exit", DEFAULT_APPLICATION_QUIT_ICON, [this]() { m_main_window.get_window().close(); }));
}
Gtk::MenuItem *core::Tray::create_menu_item(const std::string &text, const std::string &icon_name,
                                            std::function<void()> callback)
{
    auto item = Gtk::manage(new Gtk::MenuItem());

    auto box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 6));

    auto icon = Gtk::manage(new Gtk::Image());
    icon->set_from_icon_name(icon_name, Gtk::ICON_SIZE_MENU);
    box->pack_start(*icon, false, false, 0);

    auto label = Gtk::manage(new Gtk::Label(text));
    label->set_halign(Gtk::ALIGN_START);
    box->pack_start(*label, true, true, 0);

    item->add(*box);
    item->signal_activate().connect(callback);

    return item;
}
