#include "header.hpp"

int main(int argc, char* argv[]) {
    std::shared_ptr<Gtk::Application> app = Gtk::Application::create("by.mihuyka.testapp");
    
    std::shared_ptr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    
    css_provider->load_from_data(
        "window.bg-amber { background: #893101; }"
        "window.bg-dark-blue { background: #00072D; }"
    );
    
    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(), 
        css_provider, 
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    
    return app->make_window_and_run<my_window>(argc, argv);
}
