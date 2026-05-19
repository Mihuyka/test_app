#include "header.hpp"
#include <cmath>
#include <stdexcept>

my_window::my_window() :
    m_main_box(Gtk::Orientation::VERTICAL,15),
    
    m_math_layout_box(Gtk::Orientation::HORIZONTAL, 10),
    
    m_button_calculate("Вычичслить"),
    
    m_label_result("Результат: ещё не расчитан"),
    
    m_frame_color("Выбор цвета фона (RadioButtons)"),
    
    m_box_color_vertical(Gtk::Orientation::VERTICAL, 5),
    
    m_radio_plum("Цвет Plum (Слиловый)"),
    
    m_radio_bisque("Цвет Bisque (Бежевый)"),
    
    m_frame_title("Управление загаловком (CheckBoxes)"),
    
    m_box_title_vertical(Gtk::Orientation::VERTICAL, 5),
    
    m_check_fio("Показать ФИО"),
    
    m_check_group("Показать Группу и Номер")
{
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
    
    m_radio_bisque.set_group(m_radio_plum);
    
    m_box_color_vertical.append(m_radio_plum);
    m_box_color_vertical.append(m_radio_bisque);
    m_frame_color.set_child(m_box_color_vertical);
    m_main_box.append(m_frame_color);
    
    m_box_title_vertical.append(m_check_fio);
    m_box_title_vertical.append(m_check_group);
    m_frame_title.set_child(m_box_title_vertical);
    m_main_box.append(m_frame_title);
    
    m_button_calculate.signal_clicked().connect(
        sigc::mem_fun(*this, &my_window::on_calculate_button_clicked)
    );
    
    m_radio_plum.signal_toggled().connect(
        sigc::mem_fun(*this, &my_window::on_color_radio_toggled)
    );
    m_radio_bisque.signal_toggled().connect(
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
    if (m_radio_plum.get_active()) {
        remove_css_class("bg-bisque");
        add_css_class("bg-plum");
    } else if (m_radio_bisque.get_active()) {
        remove_css_class("bg-plum");
        add_css_class("bg-bisque");
    }
}

void my_window::on_title_checkbox_toggled() {
    Glib::ustring base_title = "test_app";
    
    if (m_check_fio.get_active() && m_check_group.get_active()) {
        base_title = "Евтерев Т-493";
    }
    else if (m_check_fio.get_active()) {
        base_title = "Евтерев Михаил Алексеевич";
    }
    else if (m_check_group.get_active()) {
        base_title = "Группа: Т-493";
    }

    set_title(base_title);
}

void my_window::show_error_message(const Glib::ustring& title, const Glib::ustring& message) {
    std::shared_ptr<Gtk::AlertDialog> dialog = Gtk::AlertDialog::create(title); //Можно использовать auto
    dialog->set_detail(message);
    dialog->show(*this);
}