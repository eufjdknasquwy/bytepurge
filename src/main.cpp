#include "core/config_loader.h"
#include "core/signal_handler.h"
#include "ui/main_window.h"
#include "ui/message_dialog_helper.h"
#include "utils/args_parser.h"
#include "utils/console_logger.h"
#include "utils/system_detector.h"
#include <thread>
int main(int argc, char *argv[])
{
    core::install_signal_handlers();

    utils::ArgsParser::parse(argc, argv);
    utils::ConsoleLogger::init();
    ui::MessageDialogHelper::init_error_handler();

    std::thread load_config_thread(
        []
        {
            try
            {
                core::ConfigLoader::load_config();
            }
            catch (const std::exception &e)
            {
                utils::ConsoleLogger::log(core::LogLevel::Error, ("Config load failed: " + std::string(e.what())));
                utils::ConsoleLogger::reset_error_buffer();
            }
        });

    std::thread load_pm_config_thread(
        []
        {
            try
            {
                core::ConfigLoader::load_pm_config();
            }
            catch (const std::exception &e)
            {
                utils::ConsoleLogger::log(core::LogLevel::Error,
                                          std::string("Package manager config load failed: ") + e.what());
                utils::ConsoleLogger::reset_error_buffer();
            }
        });

    load_pm_config_thread.join();
    utils::SystemDetector::list_detections();

    auto app = Gtk::Application::create("org.example." + std::string(PROJECT_NAME));

    Glib::signal_io().connect(
        [](const Glib::IOCondition &) -> bool
        {
            char buf[16];
            while (::read(core::get_signal_pipe_fd(), buf, sizeof buf) > 0)
            {
            }
            if (auto win = ui::MainWindow::get_instance())
            {
                win->request_shutdown();
            }
            return true;
        },
        core::get_signal_pipe_fd(), Glib::IO_IN);

    ui::MainWindow main_window;

    utils::ConsoleLogger::log(core::LogLevel::Info, std::string(PROJECT_GENERIC_NAME) + " started");

    load_config_thread.join();
    if (!core::args.tray) main_window.show_window();

    app->hold();
    return app->run();
}
