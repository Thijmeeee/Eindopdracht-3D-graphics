#include "FileWriter.h"

FileWriter::FileWriter() {
   
}

void FileWriter::reset() {
    std::ofstream file(FILEPATH, std::ios::trunc);
    file.close();
}

void FileWriter::writeTextToFile(std::string text) {
    std::ofstream file;

    file.open(FILEPATH, std::ios_base::app);

    file << text << "\n\n";

    file.flush();
    file.close();
}
