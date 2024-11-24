#include <filesystem>
#include <fstream>
#include <iostream>
#include <system_error>
#include <vector>
#include <string>
#include <sstream>

namespace fs = std::filesystem;

class FileSystemHelper {
public:
    // Create a directory and any necessary parent directories
    static bool createDirectory(const fs::path& path) {
        std::error_code ec;
        if (fs::exists(path)) {
            return fs::is_directory(path);
        }
        
        bool success = fs::create_directories(path, ec);
        if (ec) {
            std::cerr << "Error creating directory: " << ec.message() << std::endl;
            return false;
        }
        return success;
    }

    // Create a file if it doesn't exist
    static bool createFile(const fs::path& path) {
        if (fs::exists(path)) {
            return fs::is_regular_file(path);
        }

        // Create parent directories if they don't exist
        auto parentPath = path.parent_path();
        if (!parentPath.empty() && !createDirectory(parentPath)) {
            return false;
        }

        try {
            std::ofstream file(path);
            return file.good();
        } catch (const std::exception& e) {
            std::cerr << "Error creating file: " << e.what() << std::endl;
            return false;
        }
    }

    // Create file with content
    static bool createFileWithContent(const fs::path& path, const std::string& content) {
        try {
            // Create parent directories if needed
            auto parentPath = path.parent_path();
            if (!parentPath.empty() && !createDirectory(parentPath)) {
                return false;
            }

            std::ofstream file(path);
            if (!file) {
                return false;
            }
            file << content;
            return file.good();
        } catch (const std::exception& e) {
            std::cerr << "Error creating file with content: " << e.what() << std::endl;
            return false;
        }
    }

    // Read entire file into string
    static std::string readFile(const fs::path& path) {
        if (!fs::exists(path) || !fs::is_regular_file(path)) {
            throw std::runtime_error("File does not exist or is not a regular file: " + path.string());
        }

        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Could not open file: " + path.string());
        }

        return std::string(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        );
    }

    // Read file lines into vector
    static std::vector<std::string> readLines(const fs::path& path) {
        if (!fs::exists(path) || !fs::is_regular_file(path)) {
            throw std::runtime_error("File does not exist or is not a regular file: " + path.string());
        }

        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Could not open file: " + path.string());
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        return lines;
    }
};

int main() {
    try {
        // Create a directory
        fs::path dirPath = fs::path("test_directory") / "nested" / "path";
        if (FileSystemHelper::createDirectory(dirPath)) {
            std::cout << "Directory created successfully: " << dirPath << std::endl;
        }

        // Create a file with multiple lines of content
        fs::path filePath = dirPath / "test.txt";
        std::string content = "First line\nSecond line\nThird line\n";
        if (FileSystemHelper::createFileWithContent(filePath, content)) {
            std::cout << "File created with content: " << filePath << std::endl;
        }

        // Read entire file
        std::cout << "\nReading entire file at once:" << std::endl;
        std::string fileContent = FileSystemHelper::readFile(filePath);
        std::cout << fileContent;

        // Read file line by line
        std::cout << "\nReading file line by line:" << std::endl;
        std::vector<std::string> lines = FileSystemHelper::readLines(filePath);
        for (size_t i = 0; i < lines.size(); ++i) {
            std::cout << "Line " << (i + 1) << ": " << lines[i] << std::endl;
        }

        // Check what we've created
        std::cout << "\nDirectory contents:" << std::endl;
        for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
            std::cout << entry.path() << std::endl;
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
