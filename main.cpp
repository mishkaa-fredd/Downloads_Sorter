#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

static std::string ToLower(std::string value) {
    for (char& ch : value) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return value;
}

static std::string GetCategoryByExtension(const std::string& extension) {
    static const std::unordered_map<std::string, std::string> categories = {
        {".jpg", "Images"},    {".jpeg", "Images"},  {".png", "Images"},
        {".gif", "Images"},    {".bmp", "Images"},   {".webp", "Images"},
        {".pdf", "Documents"}, {".doc", "Documents"}, {".docx", "Documents"},
        {".txt", "Documents"}, {".xls", "Documents"}, {".xlsx", "Documents"},
        {".ppt", "Documents"}, {".pptx", "Documents"},
        {".zip", "Archives"},  {".rar", "Archives"},  {".7z", "Archives"},
        {".tar", "Archives"},  {".gz", "Archives"},
        {".mp4", "Videos"},    {".mkv", "Videos"},    {".avi", "Videos"},
        {".mov", "Videos"},    {".wmv", "Videos"},
        {".mp3", "Audio"},     {".wav", "Audio"},     {".flac", "Audio"},
        {".ogg", "Audio"},
        {".exe", "Programs"},  {".msi", "Programs"},
    };

    const auto it = categories.find(ToLower(extension));
    if (it != categories.end()) {
        return it->second;
    }
    return "Other";
}

static fs::path BuildUniquePath(const fs::path& destinationDir, const fs::path& fileName) {
    fs::path candidate = destinationDir / fileName;
    if (!fs::exists(candidate)) {
        return candidate;
    }

    const std::string stem = fileName.stem().string();
    const std::string ext = fileName.extension().string();

    int counter = 1;
    while (true) {
        fs::path renamed = destinationDir / (stem + "_" + std::to_string(counter) + ext);
        if (!fs::exists(renamed)) {
            return renamed;
        }
        ++counter;
    }
}

int main() {
    std::cout << "Введите путь к папке с файлами: ";
    std::string inputPath;
    std::getline(std::cin, inputPath);

    if (inputPath.empty()) {
        std::cerr << "Ошибка: путь не может быть пустым.\n";
        return 1;
    }

    fs::path folderPath = fs::path(inputPath);
    std::error_code ec;

    if (!fs::exists(folderPath, ec) || !fs::is_directory(folderPath, ec)) {
        std::cerr << "Ошибка: указанная папка не существует или это не директория.\n";
        return 1;
    }

    std::size_t movedCount = 0;
    std::size_t skippedCount = 0;

    for (const auto& entry : fs::directory_iterator(folderPath, ec)) {
        if (ec) {
            std::cerr << "Ошибка при чтении папки: " << ec.message() << '\n';
            return 1;
        }

        if (!entry.is_regular_file()) {
            ++skippedCount;
            continue;
        }

        const fs::path sourcePath = entry.path();
        const std::string category = GetCategoryByExtension(sourcePath.extension().string());
        const fs::path destinationDir = folderPath / category;

        fs::create_directories(destinationDir, ec);
        if (ec) {
            std::cerr << "Не удалось создать папку \"" << destinationDir.string()
                      << "\": " << ec.message() << '\n';
            ec.clear();
            ++skippedCount;
            continue;
        }

        const fs::path destinationPath = BuildUniquePath(destinationDir, sourcePath.filename());
        fs::rename(sourcePath, destinationPath, ec);
        if (ec) {
            std::cerr << "Не удалось переместить файл \"" << sourcePath.filename().string()
                      << "\": " << ec.message() << '\n';
            ec.clear();
            ++skippedCount;
            continue;
        }

        ++movedCount;
    }

    std::cout << "Готово. Перемещено файлов: " << movedCount
              << ", пропущено: " << skippedCount << ".\n";
    return 0;
}
