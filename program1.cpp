#include "program1.h"

// Область имен для глобальных переменных
namespace global {
    bool program_exit = false; // необходимость выхода из программы
    string user_input = "";  // переменная пользовательского ввода программы
    string menu_position = "choose_file"; // переменная отвечающая за положение пользователя в меню
    string path_to_files = "C:\\Users\\koala\\CLionProjects\\program1\\Files\\";
}

// -*-*-*-*-*-*-*-*-!
// Служебные функции!
// -*-*-*-*-*-*-*-*-!

bool service_command() { // служебные команды перемещения по меню
    if (global::user_input == "/exit" or global::user_input == "e")  { // при получении от пользователя комманды exit переставляет глобальную переменную program_exit
        global::program_exit = true;      // а также возвращает переменную типа bool для возможности выхода из функций, циклоа и др.
        return true;
    }
    else return 0;
}

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
}

string make_date() { // возвращает время системы
    time_t curr_time = time(nullptr);
    tm* time_info = localtime(&curr_time);
    string year = to_string(time_info->tm_year + 1900);
    string mounth = to_string(time_info->tm_mon + 1);
    string day = to_string(time_info->tm_mday);
    string time_hms = to_string(time_info->tm_hour) + "-" + to_string(time_info->tm_min) + "-" + to_string(time_info->tm_sec);
    return (day + "_" + mounth + "_" + year + "_" + time_hms);
}

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*!
// функции смены цвета текста в консоли!
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*!

void set_color(string text, int color) { // выбор цвета (в значение color подставлять из перечисления serv_colors)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << text;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// -*-*-*-*-*-*-*-*-*-*-*-!
// блок логических функций!
// -*-*-*-*-*-*-*-*-*-*-*-!

bool is_leap(int year) { // функция определяет является ли год високосным
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool date_correct(string date) { // является ли строка корректной датой
    static int MAX_VALID_YR = 9999; // константа максимального года
    static int MIN_VALID_YR = 1800; // константа минимального года

    if (date.length() != 10 or date[2] != '.' or date[5] != '.') return 0; // проверяем что дата верна по длине и разделена точками

    string day = "00"; // заполняем отдельные строковые переменные для дня месяца и года
    day [0] = date[0];
    day [1] = date[1];

    string mounth = "00";
    mounth [0] = date[3];
    mounth [1] = date[4];

    string year = "0000";
    year [0] = date[6];
    year [1] = date[7];
    year [2] = date[8];
    year [3] = date[9];

    if (not(number_correct(day) and number_correct(mounth) and number_correct(year))) return 0;// проверка на то, что все переменные которые должны быть числами ими и являются

    int d = stoi(day); // после проверки переводим день месяц и год в число
    int m = stoi(mounth);
    int y = stoi(year);

    if (y > MAX_VALID_YR || y < MIN_VALID_YR) return 0; // границы ввода года
    if (m < 1 || m > 12) return 0; // границы ввода месяца
    if (d < 1 || d > 31) return 0; // границы ввода дня

    // В високосный год в феврале 29 дней
    if (m == 2) {
        if (is_leap(y)) return (d <= 29);
        else return (d <= 28);
    }

    // Месяца апрель, июнь, сентябрь и октябрь состоят из 30 или меньше дней
    if (m == 4 || m == 6 || m == 9 || m == 11) return (d <= 30);

    return 1;
}

bool word_correct(string word) { // строка не должна содержать цифр и спец.символов
    if (word.length() < 1) return 0; // строка не пуста
    for (int i=0; i<word.length(); i++) {
        if (not((word[i] >= 'A' && word[i] <= 'Z') or (word[i] >= 'a' && word[i] <= 'z'))) return 0; // проверка по таблице ACHII
    }
    return 1;
}

bool number_correct(string number) { // строка не должна содержать цифр и спец.символов
    if (number.length() < 1) return 0; // строка не пуста
    for (int i=0; i<number.length(); i++) {
        if (not(number[i] >= '0' && number[i] <= '9')) return 0; // проверка по таблице ACHII
    }
    return 1;
}

bool noun_correct(string noun) { // строка не должна содержать цифр и спец.символов кроме пробелов
    if (noun.length() < 1) return 0; // строка не пуста
    for (int i=0; i<noun.length(); i++) {
        if (not((noun[i] >= 'A' && noun[i] <= 'Z') or (noun[i] >= 'a' && noun[i] <= 'z') or noun[i] == ' '))
            return 0;// проверка по таблице ACHII
    }
    return 1;
}

bool without_special_symbols(string str) { // строка не должна содержать спец.символов
    if (str.length() < 1) return 0; // строка не пуста
    for (int i=0; i<str.length(); i++) {
        if (not((str[i] >= 'A' && str[i] <= 'Z') or (str[i] >= 'a' && str[i] <= 'z') or
                (str[i] >= '0' && str[i] <= '9') or str[i] == ' '))
            return 0; // проверка по таблице ACHII
    }
    return 1;
}

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*!
// блок функций отвечающих за открытие и работу с файлами!
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*!

void work_correspondence_file(const string& file_name = global::path_to_files + "correspondence_file_" + make_date() + ".txt", bool is_new = 1) { // при необъявленной строке file_name мы создаем новый файл
    int counter = 0; // счетчик определяющий итерацию цикла
    TCorrespondence current_input_correspondence;   // объект структуры
    bool end_work_with_file = false;    // необходимость завершения работы с файлом
    ofstream correspondence_file;
    (is_new) ? correspondence_file.open(file_name) : correspondence_file.open(file_name, ios::app);

    do {
        system("cls");     // вывод инфомации для пользователя
        cout << "You are working with correspondence file " << endl;
        set_color(file_name, serv_blue);
        cout << "\nenter information in format " << endl;
        set_color("\"TYPE(without numbers) DATE(DD.MM.YYYY) ORGANISATION NAME(without numbers)\"\n\n", serv_yellow);
        cout << "enter ";
        set_color("/back ", serv_green);
        cout << "to go to choose file menu or enter ";
        set_color("/exit ", serv_green);
        cout << "to exit program.\n";
        set_color("!Warning! if you dont complete entering information (entered all three fields) about correspondence,\nthan information will not be safed in the file\n\n", serv_red);

        switch (counter) { // вывод вспомогательной информации позволяющей пользователю понять, что он вводит
            case 0: // первая итерация цикла
                cout << "TYPE: ";
                break;
            case 1: // вторая итерация цикла
                cout << "TYPE: " << current_input_correspondence.type << endl;
                cout << "DATE: ";
                break;
            case 2: // третья итерация цикла
                cout << "TYPE: " << current_input_correspondence.type << endl;
                cout << "DATE: " << current_input_correspondence.date << endl;
                cout << "ORGANISATION NAME: ";
                break;
        }

        getline(cin, global::user_input); // получение данных от пользователя
        global::user_input = delete_extraspace_string(global::user_input);

        end_work_with_file = service_command(); // проверка на выход из программы
        if (global::user_input == "/back") { // обработка служебной команды
            global::menu_position = "correspondence_file";
            end_work_with_file = true;
        }

        switch (counter) { // проверка и присвоение данных объекту структуры в зависимости от итерации цикла
            case 0: // первая итерация цикла
                if (word_correct(global::user_input)) {
                    current_input_correspondence.type = global::user_input;
                    counter++;
                }
                else if (not(global::user_input == "/back" or global::user_input == "/exit")) {
                    set_color("entered type of correspondence incorrect, enter any key", serv_yellow);
                    global::user_input = getch();
                }
                break;
            case 1: // вторая итерация цикла
                if (date_correct(global::user_input)) {
                    current_input_correspondence.date = global::user_input;
                    counter++;
                }
                else if (not(global::user_input == "/back" or global::user_input == "/exit")) {
                    set_color("entered date incorrect, enter any key", serv_yellow);
                    global::user_input = getch();
                }
                break;
            case 2: // третья итерация цикла
                if (without_special_symbols(global::user_input)) {
                    current_input_correspondence.organisation_name = global::user_input;
                    correspondence_file << current_input_correspondence.type << "!" << current_input_correspondence.date;   // вывод информации в файл
                    correspondence_file << "!" << current_input_correspondence.organisation_name << "\n";
                    counter = 0; // после третьей итерации цикла мы обнуляем счетчик
                }
                else if (not(global::user_input == "/back" or global::user_input == "/exit")) {
                    set_color("entered organisation name incorrect, enter any key", serv_yellow);
                    global::user_input = getch();
                }
                break;
        }

    } while(end_work_with_file != true);
    correspondence_file.close(); // при выходе из функции заполнения закрываем файл
    if (current_input_correspondence.organisation_name == "") filesystem::remove(file_name); // если последнее поле структуры не было заполнено => файл пустой и мы его удаляем
}

void work_adresses_file(const string& file_name = global::path_to_files + "adresses_file_" + make_date() + ".txt", bool is_new = 1) { // при необъявленной строке file_name мы создаем новый файл
    int counter = 0; // счетчик определяющий итерацию цикла
    TAdresses current_input_adresses; // объект структуры
    bool end_work_with_file = false; // необходимость завершения работы с файлом
    ofstream adresses_file;
    (is_new) ? adresses_file.open(file_name) : adresses_file.open(file_name, ios::app);

    do {
        system("cls");  // вывод инфомации для пользователя
        cout << "You are working with adresses file " << endl;
        set_color(file_name, serv_blue);
        cout << "\nenter information in format " << endl;
        set_color("\"ORGANISATION NAME(without numbers) ADRESS(---) CHIEF SURNAME(without numbers)\"\n\n", serv_yellow);
        cout << "enter ";
        set_color("/back ", serv_green);
        cout << "to go to choose file menu or enter ";
        set_color("/exit ", serv_green);
        cout << "to exit program.\n";
        set_color("!Warning! if you dont complete entering information about organisation adresses\n(entered all three fields), than information will not be safed in the file\n\n", serv_red);

        switch (counter) { // вывод вспомогательной информации позволяющей пользователю понять, что он вводит
            case 0: // первая итерация цикла
                cout << "ORGANISATION NAME: ";
                break;
            case 1: // вторая итерация цикла
                cout << "ORGANISATION NAME: " << current_input_adresses.organisation_name << endl;
                cout << "ADRESS: ";
                break;
            case 2: // третья итерация цикла
                cout << "ORGANISATION NAME: " << current_input_adresses.organisation_name << endl;
                cout << "ADRESS: " << current_input_adresses.adress << endl;
                cout << "CHIEF SURNAME: ";
                break;
        }

        getline(cin, global::user_input); // получение данных от пользователя
        global::user_input = delete_extraspace_string(global::user_input);

        end_work_with_file = service_command(); // проверка на выход из программы
        if (global::user_input == "/back") { // обработка служебной команды
            global::menu_position = "adresses_file";
            end_work_with_file = true;
        }

        switch (counter) { // вывод вспомогательной информации позволяющей пользователю понять, что он вводит
            case 0: // первая итерация цикла
                if (noun_correct(global::user_input)) {
                    current_input_adresses.organisation_name = global::user_input;
                    counter++;
                }
                else if (global::user_input != "/back" or global::user_input != "/exit") {
                    set_color("entered oraganisation name incorrect, enter any key", serv_yellow);
                    global::user_input = getch();
                }
                break;
            case 1: // вторая итерация цикла
                if (without_special_symbols(global::user_input)) {
                    current_input_adresses.adress = global::user_input;
                    counter++;
                }
                else if (global::user_input != "/back" or global::user_input != "/exit") {
                    set_color("entered adress of oraganisation incorrect, enter any key", serv_yellow);
                    global::user_input = getch();
                }
                break;
            case 2: // третья итерация цикла
                if (word_correct(global::user_input)) {
                    current_input_adresses.surname_chief = global::user_input;
                    adresses_file << current_input_adresses.organisation_name << "!" << current_input_adresses.adress; // вывод информации в файл
                    adresses_file << "!" << current_input_adresses.surname_chief << "\n";
                    counter = 0; // после третьей итерации цикла мы обнуляем счетчик
                }
                else if (global::user_input != "/back" or global::user_input != "/exit") {
                    set_color("entered chif surname incorrect, enter any key", serv_yellow);
                    global::user_input = getch();
                }
                break;
        }

    } while(end_work_with_file != true);
    adresses_file.close(); // при выходе из функции заполнения закрываем файл
    if (current_input_adresses.surname_chief == "") filesystem::remove(file_name); // если последнее поле структуры не было заполнено => файл пустой и мы его удаляем
}

// -*-*-*-*-*-*-*-*-*-*!
// блок рабочих функций!
// -*-*-*-*-*-*-*-*-*-*!

void enter_filename(bool type_of_file) { // поиск файла по имени
    bool file_was_open = false;
    int counter = 0;    // счетчик размера массива путей
    vector<filesystem::path> file_names;    // вектор путей к файлам
    string type;
    (type_of_file) ? type="correspondence_file_" : type="adresses_file_";

    for (const auto & entry : filesystem::directory_iterator(global::path_to_files)) {
        if (entry.path().string()[global::path_to_files.length()] == 'c' and type_of_file) { // если после пути стоит буква c => correspondence_file + проверка что открываем именно его
            file_names.push_back(entry.path()); // добавляем подходящий путь в вектор
            counter++; // увеличиваем счетчик размера вектора
        }
        else if (entry.path().string()[global::path_to_files.length()] == 'a' and not(type_of_file)) { // если после пути стоит буква a => adresses_file + проверка что открываем именно его
            file_names.push_back(entry.path());
            counter++;
        }
    }

    getline(cin, global::user_input);
    global::user_input = delete_extraspace_string(global::user_input);

    service_command(); // проврека комманд перехода
    if (global::user_input == "/back") (type_of_file) ? global::menu_position = "format_of_open_cor" : global::menu_position = "format_of_open_add";

    for (int i=0; i<counter; i++) {
        if (global::path_to_files + type + global::user_input + ".txt" == file_names[i].string()) { // если ввод пользователя совпал с одним из путей, открываем
            if (type_of_file) work_correspondence_file(file_names[i].string(), false); // на дозапись
            else work_adresses_file(file_names[i].string(), false);
            file_was_open = true;
        }
    }

    if (not(file_was_open) and not(global::user_input == "/back" or global::user_input == "/exit")) { // если не был открыт файл а ввод пользователя
        system("cls");                                                                       // это не служебная комманды, то уведомляем что такого файла нет
        cout << "file with time of creation ";
        set_color(global::user_input, serv_yellow);
        cout << " doesnt exist, enter any key to continue\n\n";
        global::user_input = getch();   // задержка чтобы дать пользователю прочитать оповещение
    }
}

void list_files(bool type_of_file) { //вывод списков файлов для дозаписи
    int counter = 0;
    vector<filesystem::path> file_names;

    for (const auto & entry : filesystem::directory_iterator(global::path_to_files)) {
        if (entry.path().string()[global::path_to_files.length()] == 'c' and type_of_file) {
            file_names.push_back(entry.path());
            counter++;
        }
        else if (entry.path().string()[global::path_to_files.length()] == 'a' and not(type_of_file)) {
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

    service_command();
    if (global::user_input == "/back") (type_of_file) ? global::menu_position = "format_of_open_cor" : global::menu_position = "format_of_open_add";
    else {
        if (number_correct(global::user_input)) {
            stoi(global::user_input);
            if (stoi(global::user_input) < counter + 1 and stoi(global::user_input) > 0) {
                if (type_of_file == true) work_correspondence_file(file_names[stoi(global::user_input) - 1].string(), false);
                else if (type_of_file == false) work_adresses_file(file_names[stoi(global::user_input) - 1].string(), false);
            }
            else (type_of_file) ? global::menu_position = "list_cor_file" : global::menu_position = "list_add_file";
        }
        else (type_of_file) ? global::menu_position = "list_cor_file" : global::menu_position = "list_add_file";
    }
}

void search_list_filename(bool type_of_file) { // создание списка файлов, содержащих указанную пользователем часть имени
    bool file_was_open = false;
    bool need_exit = false;
    int counter = 0;    // счетчик строк путей файлов выбранного типа
    int file_number = 0;
    map <int,int>file_map;    // номер выводимого на экран файла (409 строка)
    vector<filesystem::path> file_names;

    for (const auto & entry : filesystem::directory_iterator(global::path_to_files)) {
        if (entry.path().string()[global::path_to_files.length()] == 'c' and type_of_file) {
            file_names.push_back(entry.path());
            counter++;
        }
        else if (entry.path().string()[global::path_to_files.length()] == 'a' and not(type_of_file)) {
            file_names.push_back(entry.path());
            counter++;
        }
    }

    getline(cin, global::user_input);
    global::user_input = delete_extraspace_string(global::user_input);

    if (global::user_input == "/exit")  global::program_exit = true;
    if (global::user_input == "/back") (type_of_file) ? global::menu_position = "format_of_open_cor" : global::menu_position = "format_of_open_add";
    if (global::user_input == "/cont") return;

    short_list_message();
    for (int i=0; i<counter; i++) {
        if (file_names[i].string().find(global::user_input) != -1) {
            file_number++;
            file_map[file_number] = i; // соотносим номер файла в списке с его номером в массиве file_names
            cout << file_number << ": ";
            set_color(file_names[i].string(), serv_yellow);
            cout << endl;
            file_was_open = true;
        }
    }

    if (not(file_was_open) and not(global::user_input == "/back" or global::user_input == "/exit")) {
        system("cls");
        cout << "file with part of name ";
        set_color(global::user_input, serv_yellow);
        cout << " doesnt exist, enter any key to continue\n\n";
        global::user_input = getch();
        return;
    }

    choose_list_filename(type_of_file, need_exit, file_number, file_map, file_names);
}

void choose_list_filename(bool type_of_file , bool need_exit, int file_number, map<int,int> file_map, vector<filesystem::path> file_names) { // выбор файла из короткого списка
    while (not need_exit) {
        global::user_input = getch();

        if (service_command()) need_exit = true;
        else if (global::user_input == "b") {
            (type_of_file) ? global::menu_position = "format_of_open_cor" : global::menu_position = "format_of_open_add";
            need_exit = true;
        }
        else if (global::user_input == "c") return;
        else {
            if (number_correct(global::user_input)) {
                stoi(global::user_input);
                if (stoi(global::user_input) < file_number + 1 and stoi(global::user_input) > 0) {
                    if (type_of_file == true) work_correspondence_file(file_names[file_map[stoi(global::user_input)]].string(), false);
                    if (type_of_file == false) work_adresses_file(file_names[file_map[stoi(global::user_input)]].string(), false);
                    need_exit = true;
                }
            }
        }
    }
}

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*!
// блок функций отвечающих за передвижение пользователя по меню!
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*!

void menu_manager() {
    global::program_exit = false;
    string menu_position = "choose_file";
    do {
        if (global::menu_position == "choose_file") menu_choose_file();
        else if (global::menu_position == "format_of_open_cor") menu_format_of_open_cor();
        else if (global::menu_position == "format_of_open_add") menu_format_of_open_add();
        else if (global::menu_position == "list_cor_file") menu_list_correspondence_file();
        else if (global::menu_position == "list_add_file") menu_list_adresses_file();
        else if (global::menu_position == "name_cor_file") menu_enter_filename_cor();
        else if (global::menu_position == "name_add_file") menu_enter_filename_add();
        else if (global::menu_position == "search_cor_file") menu_search_filename_cor();
        else if (global::menu_position == "search_add_file") menu_search_filename_add();
        else if (global::menu_position == "correspondence_file") menu_correspondence_file();
        else if (global::menu_position == "adresses_file") menu_adresses_file();
        system("cls");
    } while (global::program_exit != true);
}

void menu_choose_file() {
    cout << "The program you have launched allows you to generate two external files based on the information\n";
    cout << "entered by the user, which will be located on the computer at the address ";
    set_color("\"C:\\Users\\koala\\CLionProjects\\program1\\Files\\\"\n\n", serv_yellow);
    set_color("names of files will be generated based on current date and time\n\n", serv_blue);

    cout << "- to choose correspondence file enter ";
    set_color("1\n", serv_green);
    cout << "- to choose adresses file enter ";
    set_color("2\n", serv_green);
    cout << "- to exit the program, enter ";
    set_color("/exit\n", serv_green);
    cout << endl;

    global::user_input = getch();

    if (global::user_input == "/") {
        cout << "/";
        global::user_input = getch();
        if (global::user_input == "e") {
            cout << "e";
            global::user_input = getch();
            if (global::user_input == "x") {
                cout << "x";
                global::user_input = getch();
                if (global::user_input == "i") {
                    cout << "i";
                    global::user_input = getch();
                    if (global::user_input == "t") {
                        cout << "t";
                        global::program_exit = true;
                    }
                }
            }
        }
    }
    if (global::user_input == "1") global::menu_position = "correspondence_file";
    else if (global::user_input == "2") global::menu_position = "adresses_file";
}

void menu_correspondence_file() {
    cout << "you are working with a file of sent correspondence, a file named ";
    set_color("\"correspondence_file_DAY_MON_YYYY_HH-MM-SS\"\n", serv_yellow);
    cout << "will be created at ";
    set_color("\"C:\\Users\\koala\\CLionProjects\\program1\\Files\\\" \n", serv_yellow);
    cout << endl;
    cout << "to create a new file, enter ";
    set_color("/new\n", serv_green);
    cout << "to open an existing file, enter ";
    set_color("/open\n", serv_green);
    cout << "if you want go to choose file menu enter ";
    set_color("/back\n", serv_green);
    cout << "if you want exit -- enter ";
    set_color("/exit\n", serv_green);
    cout << endl;

    getline(cin, global::user_input);
    global::user_input = delete_extraspace_string(global::user_input);

    if (global::user_input == "/new") work_correspondence_file();
    else if (global::user_input == "/open") global::menu_position = "format_of_open_cor";
    else if (global::user_input == "/back") global::menu_position = "choose_file";
    service_command(); // проверка на выход из программы
}

void menu_adresses_file() {
    cout << "you are working with a file of addresses of organizations, a file named ";
    set_color("\"adresses_file_DAY_MON_YYYY_HH-MM-SS\"\n", serv_yellow);
    cout << "will be created at ";
    set_color("\"C:\\Users\\koala\\CLionProjects\\program1\\Files\\\" \n", serv_yellow);
    cout << endl;
    cout << "to create a new file, enter ";
    set_color("/new\n", serv_green);
    cout << "to open an existing file, enter ";
    set_color("/open\n", serv_green);
    cout << "if you want go to choose file menu enter ";
    set_color("/back\n", serv_green);
    cout << "if you want exit -- enter ";
    set_color("/exit\n", serv_green);
    cout << endl;

    getline(cin, global::user_input);
    global::user_input = delete_extraspace_string(global::user_input);

    if (global::user_input == "/new") work_adresses_file();
    else if (global::user_input == "/open") global::menu_position = "format_of_open_add";
    else if (global::user_input == "/back") global::menu_position = "choose_file";
    service_command(); // проверка на выход из программы
}

void menu_format_of_open_cor() {
    system("cls");
    set_color("Correspondence Files\n", serv_blue);
    cout << "If you want choose file from list enter ";
    set_color("/list\n", serv_green);
    cout << "If you want choose file and you know full name enter ";
    set_color("/name\n", serv_green);
    cout << "If you want choose file and you know part of full name enter ";
    set_color("/search\n\n", serv_green);
    cout << "-to go to choose adress or correspondence files enter ";
    set_color("/menu\n", serv_green);
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    getline(cin, global::user_input);
    global::user_input = delete_extraspace_string(global::user_input);

    service_command();
    if (global::user_input == "/back") global::menu_position = "correspondence_file";
    else if (global::user_input == "/menu") global::menu_position = "choose_file";
    else if (global::user_input == "/list") global::menu_position = "list_cor_file";
    else if (global::user_input == "/name") global::menu_position = "name_cor_file";
    else if (global::user_input == "/search") global::menu_position = "search_cor_file";
}

void menu_format_of_open_add() {
    system("cls");
    set_color("Adresses Files\n", serv_blue);
    cout << "If you want choose file from list enter ";
    set_color("/list\n", serv_green);
    cout << "If you want choose file and you know full name enter ";
    set_color("/name\n", serv_green);
    cout << "If you want choose file and you know part of full name enter ";
    set_color("/search\n\n", serv_green);
    cout << "-to go to choose adress or correspondence files enter ";
    set_color("/menu\n", serv_green);
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    getline(cin, global::user_input);
    global::user_input = delete_extraspace_string(global::user_input);

    service_command();
    if (global::user_input == "/back") global::menu_position = "adresses_file";
    else if (global::user_input == "/menu") global::menu_position = "choose_file";
    else if (global::user_input == "/list") global::menu_position = "list_add_file";
    else if (global::user_input == "/name") global::menu_position = "name_add_file";
    else if (global::user_input == "/search") global::menu_position = "search_add_file";
}

void menu_enter_filename_cor() {
    system("cls");
    cout << "Enter time of creation of file (DD_MM_YYYY_TT-TT-TT), which you want to complete" << endl;
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    enter_filename(true);
}

void menu_enter_filename_add() {
    system("cls");
    cout << "Enter time of creation of file (adresses_file_DD_MM_YYYY_TT-TT-TT), which you want to complete" << endl;
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    enter_filename(false);
}

void menu_list_correspondence_file() {
    system("cls");
    cout << "Enter number of file, which you want to complete" << endl;
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    list_files(true);
}

void menu_list_adresses_file() {
    system("cls");
    cout << "Enter number of file, which you want to complete" << endl;
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    list_files(false);
}

void menu_search_filename_cor() {
    system("cls");
    cout << "Enter any part of name of file (DD_MM_YYYY_TT-TT-TT), which you want to complete" << endl;
    cout << "and then choose one of the files from list" << endl;
    cout << "-to continue search if you enter wrong information enter ";
    set_color("/cont\n", serv_green);
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    search_list_filename(true);
}

void menu_search_filename_add() {
    system("cls");
    cout << "Enter any part of name of file (DD_MM_YYYY_TT-TT-TT), which you want to complete" << endl;
    cout << "and then choose one of the files from list" << endl;
    cout << "-to continue search if you enter wrong information enter ";
    set_color("/continue\n", serv_green);
    cout << "-to go back enter ";
    set_color("/back\n", serv_green);
    cout << "-to exit program enter ";
    set_color("/exit\n\n", serv_green);

    search_list_filename(false);
}

void short_list_message() {
    system("cls");
    cout << "Enter number of file, which you want to complete" << endl;
    cout << "-to continue search if you enter wrong information enter ";
    set_color("c\n", serv_green);
    cout << "-to go back enter ";
    set_color("b\n", serv_green);
    cout << "-to exit program enter ";
    set_color("e\n\n", serv_green);
}

/*                                                                     СТРУКТУРА МЕНЮ
 *
 *                                         0----------------------выбор файла для открытия--------------------------------0
 *                                         |                         (menu_choose_file)                                   |
 *                                         |                                                                              |
 *   "создать файл"--------------файл корреспонденции                                                           файл адрессов--------------"создать файл"
 *                             (menu_correspondence_file)                                                     (menu_adresses_file)
 *                                         |                                                                              |
 *                                         |                                                                              |
 *                                         |                                                                              |
 *                            выбор способа открытия файла                                               выбор способа открытия файла
 *                             (menu_format_of_open_cor)                                                  (menu_format_of_open_add)
 *             0---------------------------0-----------------------0                             0------------------------0----------------------0
 *             |                           |                       |                             |                        |                      |
 *             |                           |                       |                             |                        |                      |
 *             |                           |                       |                             |                        |                      |
 *             |                           |                       |                             |                        |                      |
 *  поиск по полному имени       выбор из списка       поиск по части имени          поиск по полному имени       выбор из списка       поиск по части имени
 * (menu_enter_filename_cor)    (menu_list_cor_file)  (menu_search_filename_cor)     (menu_enter_filename_adr)    (menu_list_adr_file)  (menu_search_filename_adr)
 *             |                           |                       |                             |                        |                       |
 *              \                          |                      /                               \                       |                      /
 *               \                         |                     /                                 \                      |                     /
 *                \------------------------0--------------------/                                   \---------------------0--------------------/
 *                                         |                                                                              |
 *                                 "открыть файл"                                                                   "открыть файл"
 */