#ifndef TEST_APP_HPP
#define TEST_APP_HPP

#include <gtkmm.h>

class my_window : public Gtk::Window {
    public:
        my_window();
    
        ~my_window() override;
        
    protected:
        ///
        void on_calculate_button_clicked();
        
        void on_color_radio_toggled();
        
        void on_title_checkbox_toggled();
        
        
        void show_error_message(const Glib::ustring& title, const Glib::ustring& message);
        
        ///
        Gtk::Box m_main_box;
        
        ///
        Gtk::Box m_math_layout_box;
        
        Gtk::Entry m_entry_x1;
        
        Gtk::Entry m_entry_x2;
        
        Gtk::Button m_button_calculate;
        
        Gtk::Label m_label_result;
        
        ///
        Gtk::Frame m_frame_color;
        
        Gtk::Box m_box_color;
        
        Gtk::CheckButton m_radio_default;
        
        Gtk::CheckButton m_radio_amber;
        
        Gtk::CheckButton m_radio_dark_blue;
        
        ///
        Gtk::Frame m_frame_title;
        
        Gtk::Box m_box_title;
        
        Gtk::CheckButton m_check_fio;
        
        Gtk::CheckButton m_check_group;
};
#endif
