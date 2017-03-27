
#include <iostream>
#include <fstream>
#include <sstream>

#pragma once

class FileManager
{
public:
	FileManager();

	// TODO:  Let's try and make this platform agnostic
	static bool fileExists(const char *fileName); 
	const char *GetGamePath() { return m_gamePath; }


	/*
	*	Note: I made some functions static now because I dont currently see a good reason why basic functionality such as
	*	opening a file/stream should be limited to a specific file-manager. To be discussed. 
	*	(There may be cases where we want different file managers for different domains but still opening, closing files should be static imo)
	*/

	// Open already existing file
	static bool openFile(std::string fileName, std::fstream &file); // write/read file
	//bool openFile(std::string fileName, std::ifstream &file); //read file
	//bool openFile(std::string fileName, std::ostream &file); //write file

	// Create a new file if not existing
	static bool createFile(std::string fileName, std::fstream &file); // write/read file

	// Close existing file
	static bool closeFile(std::fstream &file); // write/read file

private:
	const char* m_gamePath;
};
