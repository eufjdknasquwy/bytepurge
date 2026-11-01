#include "core/notifications_manager.h"
#include "core/enums.h"
#include "utils/console_logger.h"
#include <giomm.h>
#include <giomm/dbusconnection.h>
void core::NotifyManager::send_notification(const std::string &body, const std::string &title)
{
    try
    {
        auto connection = Gio::DBus::Connection::get_sync(Gio::DBus::BusType::BUS_TYPE_SESSION);
        auto proxy = Gio::DBus::Proxy::create_sync(connection, "org.freedesktop.Notifications",
                                                   "/org/freedesktop/Notifications", "org.freedesktop.Notifications");

        auto params = Glib::VariantContainerBase::create_tuple({
            Glib::Variant<Glib::ustring>::create("cache-cleaner"),                 // app_name
            Glib::Variant<guint32>::create(0),                                     // replaces_id
            Glib::Variant<Glib::ustring>::create("cache-cleaner"),                 // app_icon
            Glib::Variant<Glib::ustring>::create(title),                           // summary
            Glib::Variant<Glib::ustring>::create(body),                            // body
            Glib::Variant<std::vector<Glib::ustring>>::create({}),                 // actions
            Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create({}), // hints
            Glib::Variant<int>::create(-1)                                         // timeout
        });

        proxy->call_sync("Notify", params);
    }
    catch (const std::exception &e)
    {
        utils::ConsoleLogger::log(core::LogLevel::Error, ("DBus notify failed: " + std::string(e.what())));
    }
}
