#pragma one

#include <iostream>
#include <filesystem>
#include <conio.h>
#include <fstream>
#include <map>

void create_report(std::string path_cor, std::string path_adr);

std::string delete_extraspace_string(std::string);
std::string make_date();
std::string all_letters_down (std::string);
std::string get_path_to_report();
void key_word_search (std::string path_cor, std::string path_adr, std::string key_word, std::string pos_key);