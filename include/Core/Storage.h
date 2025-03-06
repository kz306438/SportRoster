#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <string>
#include <vector>

namespace core
{
    // Alias for a vector of strings representing file content
    using File—ontent = std::vector<std::string>;

    /**
     * @brief A class for managing file storage operations in a specified directory.
     *
     * The class allows for creating files, adding or overwriting their content,
     * retrieving content, and listing files in the directory.
     */
    class Storage final
    {
    public:
        /**
         * @brief Constructs a Storage object with a specified directory path.
         *
         * @param dir The directory path where files will be stored.
         */
        explicit Storage(const std::string& dir);

        /**
         * @brief Creates a new file in the specified directory.
         *
         * @param filename The name of the file to create.
         * 
         * @throws std::runtime_error If the file could not be created
         */
        void createFile(const std::string& filename);

        /**
         * @brief Adds content to an existing file.
         *
         * @param filename The name of the file to add content to.
         * @param fileContent The content to add to the file.
         * 
         * @throws std::runtime_error If the file could not be opened for writing
         */
        void addContent(const std::string& filename, const File—ontent& fileContent);

        /**
         * @brief Overwrites the content of an existing file.
         *
         * @param filename The name of the file to overwrite.
         * @param fileContent The content to write to the file.
         * 
         * @throws std::runtime_error If the file could not be opened for overwriting
         */
        void overwriteContent(const std::string& filename, const File—ontent& fileContent);

        /**
         * @brief Retrieves the content of a specified file.
         *
         * @param filename The name of the file to retrieve content from.
         * @return File—ontent The content of the file.
         * 
         * @throws std::runtime_error If file could mot be opened for read
         */
        [[nodiscard]] File—ontent getContent(const std::string& filename) const;

        /**
         * @brief Retrieves the directory where files are stored.
         *
         * @return std::string The directory path.
         */
        std::string getDirectory() const;

        /**
         * @brief Retrieves a list of filenames in the storage directory.
         *
         * @return std::vector<std::string> A list of filenames.
         */
        [[nodiscard]] std::vector<std::string> getFiles() const;

    private:
        /**
         * @brief Initializes the storage by loading existing files and their content.
         */
        void init();

        /**
         * @brief Loads the files from the storage directory.
         */
        void load();

    private:
        std::string m_directory; ///< The directory path where files are stored
        std::vector<std::string> m_files; ///< A list of filenames in the storage directory
    };

} // namespace core

#endif // STORAGE_H
