#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <map>
#include <conio.h>

using namespace std;

namespace global // блок глобальных переменных
{
    extern bool program_exit; // необходимость выхода из программы
    extern string user_input;  // переменная пользовательского ввода программы
    extern string menu_position; // переменная отвечающая за положение пользователя в меню
    extern string path_to_files; // путь до папки Files
};

enum serv_colors
{
    serv_green = 2, serv_blue = 11, serv_red = 12, serv_yellow = 14
};

struct TCorrespondence
{
    string type;
    string date;
    string organisation_name = "";
}; //структура данных по корреспонденции

struct TAdresses
{
    string organisation_name;
    string adress;
    string surname_chief = "";
}; // структура данных по адресам организаций

// служебные функции
bool service_command(); // стандартная команда выхода из программы
string delete_extraspace_string(string);
string make_date();
void set_color(string, int);

// логические функции
bool is_leap(int); // является ли год високосным
bool date_correct(string); // является ли строка корректной датой
bool word_correct(string); // строка не должна содержать цифр и спец.символов
bool number_correct(string); // должна содержать только цифры
bool noun_correct(string); // строка не должна содержать цифр и спец.символов кроме пробелов
bool without_special_symbols(string); // строка не содержит спец символов кроме пробелов

// функции работы с файлами
void work_correspondence_file(const string&, bool); //  в строке передается путь к файлу, по умолчанию создание нового файла, в bool передается необходимость дозаписи (1)
void work_adresses_file(const string&, bool); //  в строке передается путь к файлу, по умолчанию создание нового файла, в bool передается необходимость дозаписи (1)

// блок рабочих функций
void enter_filename(bool); // в данном блоке булева переменная в качестве аргумента: для выбора файла true для файла корреспонденции, false для файла адрессов
void list_files(bool);
void search_list_filename(bool);
void choose_list_filename(bool, bool, int, map<int,int>, vector<filesystem::path>); // 2-я bool переменная (необх выхода) int - колво доступных строк, массив всех выбранных путей

// блок функций отвечающих за передвижение по меню программы
void menu_manager(); // материнская функция меню, менеджер передвижений по меню программы
void menu_choose_file();
void menu_correspondence_file();
void menu_adresses_file();
void menu_format_of_open_cor();
void menu_format_of_open_add();
void menu_enter_filename_cor();
void menu_enter_filename_add();
void menu_list_correspondence_file();
void menu_list_adresses_file();
void menu_search_filename_cor();
void menu_search_filename_add();
void short_list_message();