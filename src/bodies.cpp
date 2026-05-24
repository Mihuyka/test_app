#include "header.hpp"
#include <cmath>
#include <stdexcept>

my_window::my_window() :
    m_main_box(Gtk::Orientation::VERTICAL,15),
    
    m_math_layout_box(Gtk::Orientation::HORIZONTAL, 10),
    
    m_button_calculate("Вычичслить"),
    
    m_label_result("Результат: ещё не расчитан"),
    
    m_frame_color("Цвет фона:"),
    
    m_box_color(Gtk::Orientation::VERTICAL, 5),
    
    m_radio_default("Default"),
    
    m_radio_amber("Amber"),
    
    m_radio_dark_blue("Dark blue"),
    
    m_frame_title("Загаловок:"),
    
    m_box_title(Gtk::Orientation::VERTICAL, 5),
    
    m_check_fio("ФИО"),
    
    m_check_group("Группа")
{
    Gtk::Settings::get_for_display(get_display())->set_property("gtk-application-prefer-dark-theme", true);
    
    set_title("test_app");
    set_default_size(450, 400);
    
    m_main_box.set_margin(15);
    set_child(m_main_box);
    
    m_entry_x1.set_placeholder_text("Введите X1");
    m_entry_x2.set_placeholder_text("Введите X2");
    
    m_math_layout_box.append(m_entry_x1);
    m_math_layout_box.append(m_entry_x2);
    m_math_layout_box.append(m_button_calculate);
    
    m_main_box.append(m_math_layout_box);
    m_main_box.append(m_label_result);
    
    m_radio_amber.set_group(m_radio_dark_blue);
    m_radio_default.set_group(m_radio_dark_blue);
    
    m_box_color.append(m_radio_default);
    m_box_color.append(m_radio_amber);
    m_box_color.append(m_radio_dark_blue);
    m_frame_color.set_child(m_box_color);
    m_main_box.append(m_frame_color);
    
    m_box_title.append(m_check_fio);
    m_box_title.append(m_check_group);
    m_frame_title.set_child(m_box_title);
    m_main_box.append(m_frame_title);
    
    m_button_calculate.signal_clicked().connect(
        sigc::mem_fun(*this, &my_window::on_calculate_button_clicked)
    );
    
    m_radio_default.signal_toggled().connect(
        sigc::mem_fun(*this, &my_window::on_color_radio_toggled)
    );
    m_radio_amber.signal_toggled().connect(
        sigc::mem_fun(*this, &my_window::on_color_radio_toggled)
    );
    m_radio_dark_blue.signal_toggled().connect(
        sigc::mem_fun(*this, &my_window::on_color_radio_toggled)
    );
    
    m_check_fio.signal_toggled().connect(
        sigc::mem_fun(*this, &my_window::on_title_checkbox_toggled)
    );
    m_check_group.signal_toggled().connect(
        sigc::mem_fun(*this, &my_window::on_title_checkbox_toggled)
    );
}

my_window::~my_window() {}

void my_window::on_calculate_button_clicked() {
    try {
        double x1 = std::stod(m_entry_x1.get_text());
        double x2 = std::stod(m_entry_x2.get_text());
        
        if (x2 == 0) {
            throw std::runtime_error("Критическая ошибка: Деление на ноль невозможно!");
        }
        
        if (x2 < 0) {
            throw std::runtime_error("Критическая ошибка: Нельзя извлечь корень из отрицательного числа!");
        }
        
        double result_value = std::sqrt(x2) + (x1 / x2);
        m_label_result.set_text("Результат: " + std::to_string(result_value));
    }
    catch (const std::invalid_argument&) {
        show_error_message("Ошибка ввода", "Пожалуйста, заполните оба поля корректными числами.");
    }
    catch (const std::runtime_error& error) {
        show_error_message("Математическая ошибка", error.what());
    }
}

void my_window::on_color_radio_toggled() {
    if (m_radio_amber.get_active()) {
        remove_css_class("bg-dark-blue");
        add_css_class("bg-amber");
    } else if (m_radio_dark_blue.get_active()) {
        remove_css_class("bg-amber");
        add_css_class("bg-dark-blue");
    } else if (m_radio_default.get_active()) {
        remove_css_class("bg-amber");
        remove_css_class("bg-dark-blue");
    }
}

void my_window::on_title_checkbox_toggled() {
    Glib::ustring base_title = "test_app";
    
    if (m_check_fio.get_active() && m_check_group.get_active()) {
        base_title = "Евтерев Михаил Алексеевич Т-493";
    }
    else if (m_check_fio.get_active()) {
        base_title = "Евтерев Михаил Алексеевич";
    }
    else if (m_check_group.get_active()) {
        base_title = "Т-493";
    }

    set_title(base_title);
}

void my_window::show_error_message(const Glib::ustring& title, const Glib::ustring& message) {
    std::shared_ptr<Gtk::AlertDialog> dialog = Gtk::AlertDialog::create(title); //Можно использовать auto
    dialog->set_detail(message);
    dialog->show(*this);
}
