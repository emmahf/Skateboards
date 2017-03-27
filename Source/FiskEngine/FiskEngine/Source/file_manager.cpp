#include "file_manager.h"

FileManager::FileManager()
{
	// TODO - Set the game path here!
}

bool FileManager::fileExists(const char *fileName)
{	
	// - This won't work if the file doesn't have read permissions
	// - Can cause race conditions in very special circumstances 
	// - I necessary to solve it, wait for c++ 14 or use external library. Don't reinvent the wheel. 
	if (std::ifstream(fileName))
		return true;
	else
		return false;
}


bool  FileManager::createFile(std::string fileName, std::fstream &file) {

	if (FileManager::fileExists(fileName.c_str()))
		return false; //file already exist, should give some message
	else
	{
		// Note -> The part that isnt platform agnostic here is all the formatting stuff for the path/fileName.
		file.open(fileName, std::ios::out);
		return true;
	}
}

bool  FileManager::openFile(std::string fileName, std::fstream &file) {

	if (!FileManager::fileExists(fileName.c_str()))
		return false; // file doesnt exist, should give some message
	else 
	{
		// Note -> The part that isnät platform agnostic here is all the formatting stuff for the path/fileName.
		file.open(fileName);
		return true;
	}
}


bool  FileManager::closeFile( std::fstream &file) {

	if (file.is_open()) 
	{
		file.close();
	}

	return true;
}