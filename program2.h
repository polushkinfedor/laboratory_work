#pragma one

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <conio.h>

using namespace std;

namespace global // блок глобальных переменных
{
    extern string user_input;  // переменная пользовательского ввода программы\
    extern string path_to_files; // путь до папки Files
};

enum serv_colors
{
    serv_green = 2, serv_blue = 11, serv_red = 12, serv_yellow = 14
};

void set_color(string, int);
string get_path_to_files();

void open_program();
void error_with_quanity_files(bool);
void menu_manager();
string report_message();
string type_of_key_word (string, string);
string what_to_do(string, string);
string choose_file(bool);