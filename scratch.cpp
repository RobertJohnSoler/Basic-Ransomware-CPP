#include <filesystem>
#include <iostream>
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main(){

    std::filesystem::path myPath = "dummy_directory";
    std::string file;

    for (const auto& dirEntry : recursive_directory_iterator(myPath)){
        file = dirEntry.path().generic_string();
        printf("%s \n", file.c_str());
    }
}
