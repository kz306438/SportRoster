#include "Core/Storage.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace core
{

	Storage::Storage(const std::string& dir)
		: m_directory(dir) 
	{
		init();
	}

	void Storage::createFile(const std::string& filename) {
		std::string filePath = m_directory + "/" + filename;
		std::ofstream file(filePath);
		if (!file) {
			throw std::runtime_error("Unable to create file: " + filePath);
		}
		m_files.push_back(filename);
	}

	void Storage::addContent(const std::string& filename, const File—ontent& fileContent) {
		std::string filePath = m_directory + "/" + filename;
		std::ofstream file(filePath, std::ios::app);
		if (!file) {
			throw std::runtime_error("Unable to open file for writing: " + filePath);
		}

		for (const auto& line : fileContent) {
			file << line << '\n';
		}
	}

	void Storage::overwriteContent(const std::string& filename, const File—ontent& fileContent) {
		std::string filePath = m_directory + "/" + filename;
		std::ofstream file(filePath, std::ios::trunc);
		if (!file) {
			throw std::runtime_error("Unable to open file for overwriting: " + filePath);
		}

		for (const auto& line : fileContent) {
			file << line << '\n';
		}
	}


	File—ontent Storage::getContent(const std::string& filename) const{
		std::string filePath = m_directory + "/" + filename;
		std::ifstream file(filePath);
		File—ontent content;
		std::string line;

		if (!file) {
			throw std::runtime_error("Unable to open file for reading: " + filePath);
		}

		while (std::getline(file, line)) {
			content.push_back(line);
		}

		return content;
	}

	std::string Storage::getDirectory() const {
		return m_directory;
	}

	std::vector<std::string> Storage::getFiles() const {
		return m_files;
	}

	void Storage::init()
	{
		if (!fs::exists(m_directory)) {
			fs::create_directories(m_directory);
		}
		load();
	}

	void Storage::load()
	{
		for (const auto& entry : fs::directory_iterator(m_directory)) {
			if (entry.is_regular_file()) {
				m_files.push_back(entry.path().filename().string());
			}
		}
	}

} // namespace core
