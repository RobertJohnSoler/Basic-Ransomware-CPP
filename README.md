# Overview
This repo simulates a very basic Ransomware attack on a dummy directory (in the repo). The ransomware is written in C++. The code is only built for Windows systems. 

Note that this repo should be used for educational purposes only. <strong>Using this code for illegal purposes is punishable by law.</strong>

## Requirements
* Make sure the environment for C/C++ development is already set up on your machine. The C/C++ code in this repo is build for Windows machines, so if that's the OS you are using, follow the guide [here](https://code.visualstudio.com/docs/cpp/config-mingw?fbclid=IwY2xjawG6AfdleHRuA2FlbQIxMAABHSO4WPA2xtDaTKrFsBsA-wPPEC2UcH2cfyFbi2WN0b8scKeCweYNZqBKvw_aem_VmqdFcg02qeJubMOo6dONQ).
* Download OpenSSL from this [link](https://slproweb.com/products/Win32OpenSSL.html). 


## Ransomware Simulation

All the code for the ransomware simulation is located in `/ransomware_sim`. In there, the directory `/dummy_directory_1` is the target directory that the ransomware will encrypt. It's hard coded into the C++ code, so if you want to change the target directory's name or use the ransomware on a different folder, you'll have to change the code in this line: `std::string target_dir = "dummy_directory_1";`. Here's the different kinds of executable code vital for the simulation: </br>
* `basic_ransomware.cpp` - A very simple piece of ransomware that showcases how ransomware works. It recursively visits all files in a directory and overwrites them with their encrypted data. 
* `actual_ransomeware.cpp` - The closest I could get to legitimate, real-world ransomware behavior. It runs silently in the background without notifying the user, and when it's done, it leaves a ransom note and then deletes itself to make investigations harder.
* `undo_ransom.cpp` - Your only way of effectively undoing the ransomware's actions. It uses the same encryption key and algorithm as the ransomwares, so if you change they keys in the ransomware, change it in this code too.


## Important Commands
* To compile `basic_ransomware.cpp`, run this command: `g++ basic_ransomware.cpp -o <output_filename> -lssl -lcrypto`
* To compile `actual_ransomware.cpp`, run this command: `g++ actual_ransomware.cpp -o <output_filename> -lcrypto -mwindows`
* To compile `undo.cpp`, run this command: `g++ undo.cpp -o <output_filename> -lssl -lcrypto`

## Other Directories
* `/encryption tests (deprecated)` - Folder used for testing encryption and decryption of files. The code in this folder uses `<openssl/aes.h>`, however, that's deprecated already, so we're not using that for the actual simulation.
* `/encryption tests` - Another folder used for testing encryption and decryption of files. This time, it uses `<openssl/evp.h>`, which is not deprecated, so that is what we use in the actual simulation.
* `/dummy_directories` - This folder holds the original copies of your dummy directories. If you somehow mess up and encrypt the dummy directory in `/ransomware_sim` so bad that it can't be reversed anymore, you can simply delete that and copy the original one from `/dummy_directories`. Don't mess up with the original copies!
