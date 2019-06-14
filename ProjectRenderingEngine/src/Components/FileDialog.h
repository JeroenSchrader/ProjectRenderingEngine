#pragma once

#include <string>

class FileDialog {
public:
	FileDialog() = default;
	~FileDialog() = default;

	unsigned int Open();

	inline std::string& GetErrorMessage() { return m_Error; }
	inline std::string& GetFullFilePath() { return m_FilePath; }
	inline std::string& GetFileName() { return m_FileName; }
private:
	std::string m_Error;
	std::string m_FilePath;
	std::string m_FileName;
};