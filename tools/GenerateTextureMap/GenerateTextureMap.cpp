#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <windows.h>

constexpr int MapWidth = 2048;
constexpr int MapHeight = 2048;

struct TEntry
{
    std::string Path;
    int Width;
    int Height;
};
sf::Image ImageMap;
std::vector<TEntry> Assets;
std::map<std::string, std::vector<TEntry>> Maps;
std::string TextureImageFileNameBase;
std::string CurrentMapType;

class TFile // obiekt typu RAII -> Rescource Aquisition Is Initialization
{
public:
    TFile() {}
    ~TFile()
    {
        Close();
    }
    void Open(std::string TextureImageFileName = "TextureMap.txt")
    {
        Close();
        std::lock_guard<std::mutex> lock(mu);
        file.open(TextureImageFileName, std::ios::out | std::ios::trunc);
    }
    void Close()
    {
        std::lock_guard<std::mutex> lock(mu);
        if (file.is_open())
        {
            file.close();
        }
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


void CreateMainTextureMaps(const std::string& Directory);
void ProcessDirectory(const std::string& Directory, const std::string& Indent);
void DrawOnImage(const sf::Image& Src, sf::Image& Dest, int DestX, int DestY);
void JoinAssets(std::string CurrentMapType);

int main(int argc, char** argv[])
{
    std::string Directory("assets");

    std::cout << "Executing GenerateTextureMap, current working directory is: " << std::filesystem::current_path() << std::endl;

    CreateMainTextureMaps(Directory);

    TextureImageFileNameBase = "TextureMap";
    for (auto it = Maps.begin(); it != Maps.end(); ++it)
    {
        JoinAssets((*it).first);
    }

    return 0;
}


void CreateMainTextureMaps(const std::string& Directory)
{
    std::vector<std::string> MainDirectories;
    MainDirectories.clear();
    for (const auto& entry : std::filesystem::directory_iterator(Directory))
    {
        if (entry.is_directory())
        {
            if (entry.path().string() != Directory + "\\monsters" && entry.path().string() != Directory + "\\sets")
            {
                MainDirectories.push_back(entry.path().string());
            }
        }
    }

    // inicjalizacja map
    Maps["Main"] = Assets;
    Maps["Monsters"] = Assets;
    Maps["Character"] = Assets;

    std::string Indent;
    // Glowna mapa
    CurrentMapType = "Main";
    for (size_t i = 0; i < MainDirectories.size(); ++i)
    {
        ProcessDirectory(MainDirectories[i], Indent);
    }

    // Mapa potworow
    Indent = "";
    CurrentMapType = "Monsters";
    ProcessDirectory(Directory + "\\monsters", Indent);

    // Mapa bohatera
    Indent = "";
    CurrentMapType = "Character";
    ProcessDirectory(Directory + "\\sets", Indent);
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
                Maps[CurrentMapType].push_back(Item);
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

void JoinAssets(std::string CurrentMapType)
{
    sf::Vector2u MapSize;
    int DestX = 0;
    int DestY = 0;
    int MaxLineHeight = 0;
    int Counter = 0;
    std::vector<TEntry>& Assets = Maps[CurrentMapType];
    TFile DataFile;

    std::string Fname = TextureImageFileNameBase + CurrentMapType;
    if (Counter > 0)
    {
        Fname += std::to_string(Counter);
    }
    DataFile.Open("assets\\" + Fname + ".txt");

    ImageMap.create(MapWidth, MapHeight, sf::Color(255, 255, 255, 0));
    MapSize = ImageMap.getSize();
    std::sort(Assets.begin(), Assets.end(), [](const TEntry& a, const TEntry& b) { return a.Width < b.Width; });
    for (size_t i = 0; i < Assets.size(); ++i)
    {
        if (DestX + Assets[i].Width >= MapSize.x)
        {
            DestY += MaxLineHeight;
            MaxLineHeight = 0;
            DestX = 0;
            int NewLineMaxHeight = 0;
            for (size_t j = i + 1; j < Assets.size(); ++j)
            {
                int x = DestX;
                if (x + Assets[j].Width >= MapSize.x)
                {
                    break;
                }
                if (NewLineMaxHeight < Assets[j].Height)
                {
                    NewLineMaxHeight = Assets[j].Height;
                }
                x += Assets[j].Width;
            }
            if (DestY + NewLineMaxHeight >= MapSize.y)
            {
                Fname = TextureImageFileNameBase + CurrentMapType;
                if (Counter > 0)
                {
                    Fname += std::to_string(Counter);
                }
                ImageMap.saveToFile("assets\\" + Fname + ".png");
                DataFile.Close();

                Counter++;
                Fname = TextureImageFileNameBase + CurrentMapType + std::to_string(Counter);
                DataFile.Open("assets\\" + Fname + ".txt");
                ImageMap.create(MapWidth, MapHeight, sf::Color(255, 255, 255, 0));
                MapSize = ImageMap.getSize();
                DestY = 0;
            }
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
    ImageMap.saveToFile("assets\\" + Fname + ".png");
}
