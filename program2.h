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
string delete_extraspace_string(string);

void create_output_file();
void show_info_in_console();

void menu_manager();
string what_to_do(string, string);
string choose_file(bool);