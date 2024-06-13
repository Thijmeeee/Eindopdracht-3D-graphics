#pragma once
#include <list>
#include <iostream>
#include <fstream>
#include <string>

class FileWriter {
public:
	FileWriter();
	~FileWriter() = default;

	void writeTextToFile(std::string text);
	void reset();

	std::string FILEPATH = "C:\\Users\\thijm\\Github\\Eindopdracht-3D-graphics\\wk4_components\\files\\file.txt";
};
