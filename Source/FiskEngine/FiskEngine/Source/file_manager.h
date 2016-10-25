#pragma once
class FileManager
{
public:
	FileManager();

	// Let's try and make this platform agnostic
	bool fileExists(const char *fileName);
	const char *GetGamePath() { return m_gamePath; }

private:
	const char* m_gamePath;
};
