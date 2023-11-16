#include "work_files.h"

void create_report(std::string path_cor, std::string path_adr) {
    std::string path_to_report = get_path_to_report() + "Report_File_" + make_date();
    std::map<int, bool> empty_strings;
    int string_cor_file_num;
    int length_cor_file = 0;
    std::string cur_adress_line;
    std::string cur_corresp_line;

    std::ifstream correspondence_file(path_cor);
    std::ifstream adresses_file(path_adr);

    std::ofstream report_files(path_to_report);

    while (correspondence_file) { // получаем количество строк в файле
        std::getline(correspondence_file, cur_corresp_line);
        length_cor_file ++;
    }
    correspondence_file.clear(); // возвращаем коретку
    correspondence_file.seekg(0);
    for (int i=0; i<length_cor_file; i++) { // заполняем словарь строк которые не использовались
        empty_strings[i] = true;
    }

    while (adresses_file) {
        cur_adress_line = "";
        cur_corresp_line = "";

        std::getline(adresses_file, cur_adress_line);
        if (cur_adress_line == "") continue;

        int word_number = 0; // счетчик для нахождения нужного слова в строке
        std::string key_word_adr = "";
        for (int i=0; i<cur_adress_line.length(); i++) { // очищаем строку от служебных символов и получаем ключевое слово
            if (cur_adress_line[i] == '!')  {
                cur_adress_line[i] = ' ';
                word_number += 1;
            }
            if (word_number == 0) key_word_adr += cur_adress_line[i];
        }
        report_files << cur_adress_line << "\n"; // отправляем общую строчку для корреспонденций

        int number_of_line = 0;
        string_cor_file_num = 0;
        bool was_info = false;
        while (correspondence_file) {
            std::getline(correspondence_file, cur_corresp_line);
            word_number = 0; // счетчик для нахождения нужного слова в строке
            std::string key_word_cor = "";
            for (int i=0; i<cur_corresp_line.length(); i++) { // очищаем строку от служебных символов и получаем ключевое слово
                if (word_number == 2) key_word_cor += cur_corresp_line[i];
                if (cur_corresp_line[i] == '!')  {
                    cur_corresp_line[i] = ' ';
                    word_number += 1;
                }
            }

            if (all_letters_down(key_word_cor) == all_letters_down(key_word_adr)) {
                number_of_line ++;
                was_info = true;
                cur_corresp_line.erase(cur_corresp_line.find(key_word_cor), key_word_cor.length());
                report_files << number_of_line << ". " << cur_corresp_line << std::endl;
                empty_strings[string_cor_file_num] = false; // если эта строка использовалась отображаем это в словаре
            }

            string_cor_file_num ++;
        }
        if (not(was_info)) {
            report_files << "\\\\we haven't information about correspondence this organisation" << std::endl;
        }

        report_files << "----------------------------------------------------------------" << std::endl;
        correspondence_file.clear();
        correspondence_file.seekg(0);
    }

    bool was_emty = false;
    int counter = 1;
    string_cor_file_num = 0;
    while (correspondence_file) {
        std::getline(correspondence_file, cur_corresp_line);
        if (empty_strings[string_cor_file_num]) {
            if (not(was_emty)) {
                was_emty = true;
                report_files << "correspondence without information about organisation" << std::endl;
            }
            for (auto & letter : cur_corresp_line) {
                if (letter == '!') letter = ' ';
            }
            if (cur_corresp_line == "") continue;
            report_files << counter << ". " << cur_corresp_line << std::endl;
            counter++;
        }
        string_cor_file_num ++;
    }

    correspondence_file.close();
    adresses_file.close();
    report_files.close();
}

void key_word_search (std::string path_cor, std::string path_adr, std::string key_word, std::string pos_key) {
    bool was_keyword = false;
    bool had_two = false;
    std::ifstream correspondence_file(path_cor);
    std::ifstream adresses_file(path_adr);
    std::string cur_corresp_line;
    std::string cur_adresses_line;
    int word_number;
    system("cls");

    std::cout << key_word << ":\n\n";

    if (pos_key == "type_cor" or pos_key == "date_cor" or pos_key == "name_org") {
        while (correspondence_file) {
            cur_corresp_line = "";
            cur_adresses_line = "";
            std::getline(correspondence_file, cur_corresp_line);
            if (cur_corresp_line == "") continue;

            std::string send_string = "";
            std::string key_word_cor = ""; // ключевое слово связи с файлом адрессов
            std::string current_key_word = ""; // ключевое слово по которому производится поиск
            word_number = 0; // счетчик для нахождения нужного слова в строке

            for (int i=0; i<cur_corresp_line.length(); i++) { // очищаем строку от служебных символов и получаем ключевое слово
                if (word_number == 2) key_word_cor += cur_corresp_line[i];

                if (cur_corresp_line[i] == '!')  {
                    cur_corresp_line[i] = ' ';
                    word_number += 1;
                }

                if (cur_corresp_line[i]!= ' ') {
                    if (pos_key == "type_cor" and word_number == 0) current_key_word += cur_corresp_line[i];
                    else if (pos_key == "date_cor" and word_number == 1) current_key_word += cur_corresp_line[i];
                    else if (pos_key == "name_org" and word_number == 2) current_key_word = key_word_cor;

                    if (pos_key == "type_cor" and word_number != 0) send_string += cur_corresp_line[i];
                    else if (pos_key == "date_cor" and word_number != 1) send_string += cur_corresp_line[i];
                }
            }
            if (send_string.find(key_word_cor) != -1) send_string.erase(send_string.find(key_word_cor), key_word_cor.length());

            //std::cout << "\n\n\n\n" << current_key_word << "&" << key_word;

            if (all_letters_down(current_key_word) == all_letters_down(key_word)) {
                was_keyword = true;
                cur_corresp_line.erase(cur_corresp_line.find(current_key_word), current_key_word.length());
                while (adresses_file) {
                    std::getline(adresses_file, cur_adresses_line);
                    if (cur_adresses_line == "") continue;
                    word_number = 0; // счетчик для нахождения нужного слова в строке
                    std::string key_word_adr = "";
                    for (int i = 0; i <
                                    cur_adresses_line.length(); i++) { // очищаем строку от служебных символов и получаем ключевое слово
                        if (cur_adresses_line[i] == '!') {
                            cur_adresses_line[i] = ' ';
                            word_number += 1;
                        }
                        if (word_number == 0) key_word_adr += cur_adresses_line[i];

                    }
                    if (all_letters_down(key_word_cor) == all_letters_down(key_word_adr)) {
                        if (pos_key == "name_org") {
                            send_string = cur_corresp_line;
                            if (cur_adresses_line.find(key_word_cor) != -1) cur_adresses_line.erase(cur_adresses_line.find(key_word_cor), key_word_cor.length());
                        }

                        send_string = delete_extraspace_string(send_string);
                        cur_adresses_line = delete_extraspace_string(cur_adresses_line);
                        send_string += " ";

                        had_two = true;
                        std::cout << send_string << cur_adresses_line << std::endl;
                    }
                }
                adresses_file.clear();
                adresses_file.seekg(0);
                if (had_two == false) {
                    std::cout << send_string << " " << key_word_cor << std::endl;
                }
                else had_two = false;

            }
        }
    }

    else if (pos_key == "org_adress" or pos_key == "org_surname") {
        while (adresses_file) {
            cur_corresp_line = "";
            cur_adresses_line = "";
            std::getline(adresses_file, cur_adresses_line);
            if (cur_adresses_line == "") continue;

            std::string send_string = "";
            std::string key_word_adr = ""; // ключевое слово связи с файлом адрессов
            std::string current_key_word = ""; // ключевое слово по которому производится поиск
            word_number = 0; // счетчик для нахождения нужного слова в строке

            for (int i=0; i<cur_adresses_line.length(); i++) { // очищаем строку от служебных символов и получаем ключевое слово
                if (cur_adresses_line[i] == '!')  { //  избавление от служебных символов
                    cur_adresses_line[i] = ' ';
                    word_number += 1;
                }

                if (word_number == 0) key_word_adr += cur_adresses_line[i]; // нахождение слова для сопряжения с файлом корреспонденции

                // блок выделения слова для поиска
                if (word_number == 1 and pos_key == "org_adress") current_key_word += cur_adresses_line[i];
                if (word_number == 2 and pos_key == "org_surname") current_key_word += cur_adresses_line[i];

                if (cur_corresp_line[i]!= ' ') {
                    if (pos_key == "org_adress" and word_number != 1) send_string += cur_adresses_line[i];
                    if (pos_key == "org_surname" and word_number != 2) send_string += cur_adresses_line[i];
                }
            }
            current_key_word = delete_extraspace_string(current_key_word);

            if (all_letters_down(current_key_word) == all_letters_down(key_word)) {
                //if (pos_key == "org_adress") cur_adresses_line.erase(cur_adresses_line.find(key_word), key_word.length()+1);
                //if (pos_key == "org_surname") cur_adresses_line.erase(cur_adresses_line.find(key_word), key_word.length());

                cur_adresses_line = delete_extraspace_string(cur_adresses_line);
                was_keyword = true;

                while (correspondence_file) {
                    std::getline(correspondence_file, cur_corresp_line);
                    word_number = 0; // счетчик для нахождения нужного слова в строке
                    std::string key_word_cor = "";
                    for (int i=0; i<cur_corresp_line.length(); i++) { // очищаем строку от служебных символов и получаем ключевое слово
                        if (word_number == 2) key_word_cor += cur_corresp_line[i];
                        if (cur_corresp_line[i] == '!')  {
                            cur_corresp_line[i] = ' ';
                            word_number += 1;
                        }
                    }
                    if (all_letters_down(key_word_cor) == all_letters_down(key_word_adr)) {
                        cur_corresp_line.erase(cur_corresp_line.find(key_word_cor), key_word_cor.length());
                        std::cout << send_string << " " << cur_corresp_line << std::endl;
                        had_two = true;
                    }
                }
                if (had_two == false) {
                    std::cout << send_string << " " << key_word_adr << std::endl;
                }
                else had_two = false;
                correspondence_file.clear();
                correspondence_file.seekg(0);
            }
        }
    }

    correspondence_file.close();
    adresses_file.close();

    if (not(was_keyword)) {
        std::cout << "\nSorry, we can't find any information about " << key_word << ".\n";
        std::cout << "enter any key to continue";
        cur_corresp_line = getch();
    }
    else
    {
        std::cout << "\nenter any key to continue";
        cur_corresp_line = getch();
    }
}

std::string get_path_to_report() {
    std::string path = std::filesystem::current_path().string();
    int index = 0;
    for (int i = path.length()-1; i>0; i--) {
        if (path[i] == '\\') {
            index = i;
            break;
        }
    }
    path.erase(index);
    path += "\\OutputFolder";
    std::filesystem::create_directories(path);
    return path+"\\";
}

std::string all_letters_down (std::string str) {
    int delta = int ('A' - 'a');
    for (auto & letter : str) {
        if (letter <= 'Z' and letter >= 'A') letter -= delta;
    }
    return str;
}

std::string make_date() { // возвращает время системы
    time_t curr_time = time(nullptr);
    tm* time_info = localtime(&curr_time);
    std::string year = std::to_string(time_info->tm_year + 1900);
    std::string mounth = std::to_string(time_info->tm_mon + 1);
    std::string day = std::to_string(time_info->tm_mday);
    std::string time_hms = std::to_string(time_info->tm_hour) + "-" + std::to_string(time_info->tm_min) + "-" + std::to_string(time_info->tm_sec);
    return (day + "_" + mounth + "_" + year + "_" + time_hms);
}

std::string delete_extraspace_string (std::string str) {
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

/*void create_report(std::string path_cor, std::string path_adr) {
    std::string path_to_report = get_path_to_report() + "Report_File_" + make_date();
    std::map<unsigned int, std::string> file1;

    std::ifstream correspondence_file(path_cor);
    std::ifstream adresses_file(path_adr);
}

void key_word_search (std::string path_cor, std::string path_adr, std::string key_word, std::string pos_key) {

}*/