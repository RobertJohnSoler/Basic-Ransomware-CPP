# Basic-Ransomware-CPP
This repo simulates a very basic Ransomware attack on a dummy directory (in the repo). The ransomware is written in C++.

## Ransomware Simulation

All the code for the ransomware simulation is located in `/ransomware_sim`. In there, the directory `/dummy_directory_1` is the target directory that the ransomware will encrypt. It's hard coded into the C++ code, so if you want to change the target directory's name or use the ransomware on a different folder, you'll have to chanch the code. </br>

To compile `basic_ransomware.cpp`, run this command: `g++ basic_ransomware.cpp -o <output_filename> -lssl -lcrypto` </br>
To comple `actual_ransomware.cpp`, run this command: `g++ actual_ransomware.cpp -o <output_filename> -lcrypto -mwindows` </br>
 </br>
The undo_ransom is your only way of effectively undoing the ransomware's actions.  </br>
To compile `undo.cpp`, run this command: `g++ undo.cpp -o <output_filename> -lssl -lcrypto`

[comment]: <> (Talk about prerequisites next, and the purpose of each folder. Prerequisites are C++ and g++ and OpenSSL.)
