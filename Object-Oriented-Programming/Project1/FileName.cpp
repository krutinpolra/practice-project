#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

std::string decode(const std::string& message_file) {
   std::ifstream file(message_file);
   if (!file.is_open()) {
      std::cerr << "Error opening file." << std::endl;
      return "";
   }

   std::map<size_t, std::string> words_map;
   std::string line;
   while (std::getline(file, line)) {
      size_t pos = line.find(' ');
      if (pos == std::string::npos) {
         std::cerr << "Invalid format in file." << std::endl;
         return "";
      }
      size_t num = std::stoi(line.substr(0, pos));
      std::string word = line.substr(pos + 1);
      words_map[num] = word;
   }

   std::string decoded_message;
   size_t num = 1;
   size_t row_increment = 2;
   while (words_map.find(num) != words_map.end()) {
      decoded_message += words_map[num] + " ";
      num += row_increment;
      ++row_increment;
   }

   return decoded_message;
}

int main() {
   std::string message = decode("coding_qual_input.txt");
   std::cout << "Decoded message: " << message << std::endl;
   return 0;
}
