#include "work_files.h"

void create_report(std::string path_cor, std::string path_adr) {
    std::string path_to_report = get_path_to_report() + "Report_File_" + make_date();

    std::ifstream correspondence_file(path_cor);
    std::ifstream adresses_file(path_adr);

    std::ofstream report_files(path_to_report);

    while (adresses_file) {
        std::string cur_adress_line = "";
        std::string cur_corresp_line = "";

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
        report_files << cur_adress_line << ":\n"; // отправляем общую строчку для корреспонденций

        int number_of_line = 0;
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
            if (key_word_cor == key_word_adr) {
                number_of_line ++;
                report_files << number_of_line << ". " << cur_corresp_line << std::endl;
            }
        }
        correspondence_file.clear();
        correspondence_file.seekg(0);
    }
    correspondence_file.close();
    adresses_file.close();
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

std::string make_date() { // возвращает время системы
    time_t curr_time = time(nullptr);
    tm* time_info = localtime(&curr_time);
    std::string year = std::to_string(time_info->tm_year + 1900);
    std::string mounth = std::to_string(time_info->tm_mon + 1);
    std::string day = std::to_string(time_info->tm_mday);
    std::string time_hms = std::to_string(time_info->tm_hour) + "-" + std::to_string(time_info->tm_min) + "-" + std::to_string(time_info->tm_sec);
    return (day + "_" + mounth + "_" + year + "_" + time_hms);
}