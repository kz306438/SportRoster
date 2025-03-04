#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <string>
#include <vector>

namespace core
{
	using FileŅontent = std::vector<std::string>;

	class Storage final
	{
	public:
		explicit Storage(const std::string& dir);

		void createFile(const std::string& filename);
		void addContent(const std::string& filename, const FileŅontent& fileContent);
		[[nodiscard]] FileŅontent getContent(const std::string& filename) const;

		std::string getDirectory() const;
		[[nodiscard]] std::vector<std::string> getFiles() const;

	private:
		void init();
		void load();

	private:
		std::string m_directory;
		std::vector<std::string> m_files;
	};

} // namespace core

#endif // STORAGE_H
