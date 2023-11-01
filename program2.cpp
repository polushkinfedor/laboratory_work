#include "program2.h"

namespace global {
    string user_input = "";  // переменная пользовательского ввода программы
    string path_to_files = "C:\\Users\\koala\\CLionProjects\\program2\\Files\\";
}

// Дополнительные функции

string delete_extraspace_string(string str) { // удаление пробелов в конце строки
    int index = 0;
    for (int i = str.length()-1; i>=0; i--) { // удаление пробелов в конце строки
        if (str[str.length()-1] != ' ') break; // если последний символ не пробел, то выходим из цикла
        if (str[i] != ' ')  {   // встречаем пробел и удаляем все после него
            index = i+1;        // после чего выходим из цикла
            str.erase(index, str.length()-index);
            break;
        }
    }

    index = 0;
    if (str[0] != ' ') return str; // если первый символ не пробел, то выходим функции
    for (int i = 0; i<str.length(); i++) {
        if (str[i] != ' ')  {    // встречаем пробел и удаляем все до него
            index = i;           // после чего выходим из функции
            str.erase(0, index);
            break;
        }
    }
    return str;
};

void set_color(string text, int color) { // выбор цвета (в значение color подставлять из перечисления serv_colors)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << text;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

bool number_correct(string number) { // строка не должна содержать цифр и спец.символов
    if (number.length() < 1) return 0; // строка не пуста
    for (int i=0; i<number.length(); i++) {
        if (not(number[i] >= '0' && number[i] <= '9')) return 0; // проверка по таблице ACHII
    }
    return 1;
}

// Функционал

string choose_file (bool type_of_file = false) {
    system("cls");
    if (not(type_of_file)) cout << "You choose adresses file:\n";
    else cout << "You choose correspondence file:\n";

    do {
        int counter = 0;
        vector<filesystem::path> file_names;

        for (const auto &entry: filesystem::directory_iterator(global::path_to_files)) {
            if (entry.path().string()[global::path_to_files.length()] == 'c' and type_of_file) {
                file_names.push_back(entry.path());
                counter++;
            } else if (entry.path().string()[global::path_to_files.length()] == 'a' and not(type_of_file)) {
                file_names.push_back(entry.path());
                counter++;
            }
        }

        for (int i = 0; i < counter; i++) {
            cout << i + 1 << ": ";
            set_color(file_names[i].string(), serv_yellow);
            cout << endl;
        }

        getline(cin, global::user_input);
        global::user_input = delete_extraspace_string(global::user_input);


        if (number_correct(global::user_input)) {
            stoi(global::user_input);
            if (stoi(global::user_input) < counter + 1 and stoi(global::user_input) > 0) {
                if (type_of_file == true) return file_names[stoi(global::user_input) - 1].string();
                else if (type_of_file == false) return file_names[stoi(global::user_input) - 1].string();
            }
        }
    } while (true);
}

string what_to_do(string path_file_two, string path_file_one) {
    do {
        system("cls");
        cout << "You connected adresses file:\n";
        set_color(path_file_one, serv_yellow);
        cout << "\nand correspondence file:\n";
        set_color(path_file_two, serv_yellow);
        cout << "\n\nTo create report about this files enter ";
        set_color("/create\n", serv_green);
        cout << "To show part of sorted data in console enter ";
        set_color("/console\n", serv_green);
        cout << "To choose other files enter ";
        set_color("/change\n", serv_green);
        cout << "To exit enter ";
        set_color("/exit\n", serv_green);

        getline(cin, global::user_input);
        global::user_input = delete_extraspace_string(global::user_input);

        if (global::user_input == "/create") return "create";
        else if (global::user_input == "/console") return "console";
        else if (global::user_input == "/exit") return "exit";
        else if (global::user_input == "/change") return "change";
    } while (true);
}

void create_output_file() {

}

void show_info_in_console() {

}

void menu_manager() {
    string func_output = "";
    string path_file_one = ""; // файл корреспонденции
    string path_file_two = ""; // файл адрессов
    bool need_exit = false;
    do {
        path_file_one = choose_file(false);
        path_file_two = choose_file(true);
        func_output = what_to_do(path_file_two, path_file_one);
        if (func_output == "create") create_output_file() ;
        else if (func_output == "console") show_info_in_console();
        else if (func_output == "exit") need_exit = true;
    } while (need_exit != true);
}