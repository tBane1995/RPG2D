#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <windows.h>

constexpr int MapWidth = 8192;
constexpr int MapHeight = 4096;

struct TEntry
{
    std::string Path;
    int Width;
    int Height;
};
sf::Image ImageMap;
std::vector<TEntry> Assets;
std::string TextureImageFileName;

class TFile // obiekt typu RAII -> Rescource Aquisition Is Initialization
{
public:
    TFile()
    {
        std::lock_guard<std::mutex> lock(mu);
        file.open(TextureImageFileName + ".txt", std::ios::out | std::ios::trunc);
    }
    ~TFile()
    {
        std::lock_guard<std::mutex> lock(mu);
        file.close();
    }
    std::ofstream& operator<<(std::string Str)
    {
        file << Str;
        return file;
    }
private:
    std::mutex mu;
    std::ofstream file;
};


void ProcessDirectory(const std::string& Directory, const std::string& Indent);
void DrawOnImage(const sf::Image& Src, sf::Image& Dest, int DestX, int DestY);
void JoinAssets();

int main(int argc, char** argv[])
{
    std::string Directory("assets");
    std::string Indent;
    TextureImageFileName = Directory + "/TextureMap.png";

    std::cout << "Executing GenerateTextureMap, current working directory is: " << std::filesystem::current_path() << std::endl;

    ImageMap.create(MapWidth, MapHeight, sf::Color(255, 255, 255, 0));
    if (std::filesystem::exists(Directory + "/TextureMap.png"))
    {
        DeleteFile((Directory + "/TextureMap.png").c_str());
    }
    ProcessDirectory(Directory, Indent);

    JoinAssets();
    ImageMap.saveToFile(TextureImageFileName);

    return 0;
}


void ProcessDirectory(const std::string& Directory, const std::string& Indent)
{
    int AddedFilesCount = 0;
    std::cout << Indent << "Processing directory: " << Directory << std::endl;
    // First iterate looking for subdirectories
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(Directory))
        {
            if (entry.is_directory())
            {
                ProcessDirectory(entry.path().string(), Indent + "    ");
            }
        }
    }
    catch (std::exception ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }


    try
    {
        sf::Image Im;
        for (const auto& entry : std::filesystem::directory_iterator(Directory))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".png")
            {
                std::cout << Indent << "  Adding file: " << entry.path().string() << std::endl;
                Im.loadFromFile(entry.path().string());
                TEntry Item;
                Item.Path = entry.path().string();
                Item.Width = Im.getSize().x;
                Item.Height = Im.getSize().y;
                Assets.push_back(Item);
            }
        }
    }
    catch (std::exception ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void DrawOnImage(const sf::Image& Src, sf::Image& Dest, int DestX, int DestY)
{
    sf::Vector2u SrcSize = Src.getSize();
    const sf::Uint8* SrcPixels = Src.getPixelsPtr();

    for (int y = 0; y < SrcSize.y; ++y)
    {
        for (int x = 0; x < SrcSize.x; ++x)
        {
            int Start = y * SrcSize.y + x*4;
            //Dest.setPixel(DestX + x, DestY + y, sf::Color(SrcPixels[Start], SrcPixels[Start + 1], SrcPixels[Start + 2], SrcPixels[Start + 3]));
            Dest.setPixel(DestX + x, DestY + y, Src.getPixel(x, y));
        }
    }
}

void JoinAssets()
{
    TFile DataFile;
    sf::Vector2u MapSize = ImageMap.getSize();
    int DestX = 0;
    int DestY = 0;
    int MaxLineHeight = 0;
    std::sort(Assets.begin(), Assets.end(), [](const TEntry& a, const TEntry& b) { return a.Width < b.Width; });
    for (size_t i = 0; i < Assets.size(); ++i)
    {
        if (DestX + Assets[i].Width >= MapSize.x)
        {
            DestY += MaxLineHeight;
            MaxLineHeight = 0;
            DestX = 0;
        }
        //std::cout << Assets[i].Path << ": " << Assets[i].Width << std::endl;
        if (DestX + Assets[i].Width < MapSize.x)
        {
            if (DestY + Assets[i].Height < MapSize.y)
            {
                if (MaxLineHeight < Assets[i].Height)
                {
                    MaxLineHeight = Assets[i].Height;
                }
                sf::Image Im;
                Im.loadFromFile(Assets[i].Path);
                DrawOnImage(Im, ImageMap, DestX, DestY);
                std::string Path = Assets[i].Path;
                for (size_t i = 0; i < Path.length(); ++i)
                {
                    if (Path[i] == '\\') Path[i] = '/';
                }
                DataFile << Path << ":" << std::to_string(DestX) << "," << std::to_string(DestY) << ","
                    << std::to_string(Assets[i].Width) << "," << std::to_string(Assets[i].Height) << std::endl;
                DestX += Assets[i].Width;
            }
        }
    }
}
