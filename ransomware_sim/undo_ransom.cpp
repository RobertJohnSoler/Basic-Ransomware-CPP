#include <openssl/evp.h>
#include <cstring>
#include <filesystem>

#define AES_BLOCK_SIZE 16

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

void decryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename);

int main(){

    std::string target_dir = "dummy_directory_1";
    std::filesystem::path myPath = target_dir;
    std::string file;

    unsigned char key_chars[] = "Hard-coded key here.";
    unsigned char iv[] = "some random IV value";

    for (const auto& dirEntry : recursive_directory_iterator(myPath)){

        if (!dirEntry.is_directory()){

            file = dirEntry.path().generic_string();
            printf("decrypting %s... \n", file.c_str());
            decryptFile(key_chars, iv, file.c_str());

            std::filesystem::path oldName = file;
            std::filesystem::path newName = oldName;
            newName.replace_extension("");
            std::filesystem::rename(oldName, newName);
        }
    }
    return 0;
}

void decryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    FILE* file_ptr = fopen(filename, "r+b");
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, key_chars, iv);

    while(1){
        long pos = ftell(file_ptr);
        bytes_read = fread(input_buffer, 1, AES_BLOCK_SIZE, file_ptr);
        int status = EVP_DecryptUpdate(ctx, output_buffer, &len, input_buffer, bytes_read);
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

