#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() 
{
    string way;
    cout << "Enter the path to your downloads folder: ";
    cin >> way;
    string downloads = way;
    for (const auto& file : fs::directory_iterator(downloads)) 
    {
        string ext = file.path().extension().string();
        if (ext == ".jpg" || ext == ".png" || ext == ".gif" || ext == ".svg")
        {
            fs::create_directory(downloads + "/Images");
            fs::rename(file.path(), downloads + "/Images/" + file.path().filename().string());
        } else if (ext == ".mp4" || ext == ".mov" || ext == ".webm")
        {
            fs::create_directory(downloads + "/Videos");
            fs::rename(file.path(), downloads + "/Videos/" + file.path().filename().string());
        } else if (ext == ".pdf" || ext == ".docx" || ext == ".doc" || ext == ".txt" || ext == ".xlsx" || ext == ".xls" || ext == ".pptx" || ext == ".ppt"  )
        {
            fs::create_directory(downloads + "/Documents");
            fs::rename(file.path(), downloads + "/Documents/" + file.path().filename().string());     
        } else if (ext == ".zip" || ext == ".rar" || ext == ".7z") 
        {
            fs::create_directory(downloads + "/Archives");
            fs::rename(file.path(), downloads + "/Archives/" + file.path().filename().string());
        } else if (ext == ".exe" || ext == ".msi") 
        {
            fs::create_directory(downloads + "/Programs");
            fs::rename(file.path(), downloads + "/Programs/" + file.path().filename().string());
        } else if (ext == ".mp3" || ext == ".wav") 
        {
            fs::create_directory(downloads + "/Music");
            fs::rename(file.path(), downloads + "/Music/" + file.path().filename().string());
        } else if (ext == ".py" || ext == ".js" || ext == ".ts" || ext == ".java" || ext == ".cs" || ext == ".cpp" || ext == ".h" || ext == ".html" || ext == ".css") 
        {
            fs::create_directory(downloads + "/Code");
            fs::rename(file.path(), downloads + "/Code/" + file.path().filename().string());
        } else if (ext == ".iso" || ext == ".dmg") 
        {
            fs::create_directory(downloads + "/Disk Images");
            fs::rename(file.path(), downloads + "/Disk Images/" + file.path().filename().string());
        } else if (ext == ".torrent") 
        {
            fs::create_directory(downloads + "/Torrents");
            fs::rename(file.path(), downloads + "/Torrents/" + file.path().filename().string());
        } else if (ext == ".otf" || ext == ".ttf") 
        {
            fs::create_directory(downloads + "/Fonts");
            fs::rename(file.path(), downloads + "/Fonts/" + file.path().filename().string());
        }
    }
} 
