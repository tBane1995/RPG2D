#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "ShapeOutline.h"

bool HasImageTransparentFrame(sf::Image& Im);
void ProcessImage(const sf::Image& Src, std::string InputFilename);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Syntax: " << argv[0] << " filename.[png|jpg]" << std::endl;
        return -1;
    }

    sf::Image Im, Process;
    if (!Im.loadFromFile(argv[1]))
    {
        std::cerr << "ERROR: Cannot load file " << argv[1] << std::endl;
        std::cerr << "Syntax: " << argv[0] << " filename.[png|jpg]" << std::endl;
        return -2;
    }

    if (!HasImageTransparentFrame(Im))
    {
        Process.create(Im.getSize().x + 2, Im.getSize().y + 2, sf::Color::Transparent);
        Process.copy(Im, 1, 1);
        ProcessImage(Process, argv[1]);
    }
    else
    {
        ProcessImage(Im, argv[1]);
    }

    return 0;
}

bool HasImageTransparentFrame(sf::Image& Im)
{
    for (int x = 0; x < Im.getSize().x; ++x)
    {
        int h = Im.getSize().y;
        if (Im.getPixel(x, 0).a > 0) return false;
        if (Im.getPixel(x, h - 1).a > 0) return false;
    }
    for (int y = 0; y < Im.getSize().y; ++y)
    {
        int w = Im.getSize().x;
        if (Im.getPixel(0, y).a > 0) return false;
        if (Im.getPixel(w - 1, y).a > 0) return false;
    }
    return true;
}


void ProcessImage(const sf::Image& Src, std::string InputFilename)
{
    sf::Vector2u SrcSize = Src.getSize();
    const sf::Uint8* SrcPixels = Src.getPixelsPtr();
    std::filesystem::path Path{ InputFilename };
    TShape Shape(SrcSize.x, SrcSize.y, 1);

    for (int y = 0; y < SrcSize.y; ++y)
    {
        for (int x = 0; x < SrcSize.x; ++x)
        {
            int Start = y * (SrcSize.x * 4) + x * 4;
            if (SrcPixels[Start + 3] > 0)
            {
                Shape.m_Cells[y * SrcSize.x + x].m_Exists = true;
            }
            else
            {
                Shape.m_Cells[y * SrcSize.x + x].m_Exists = false;
            }
        }
    }

    Shape.ConvertTileMapToPolyMap(0, 0, SrcSize.x, SrcSize.y, 1.0f, SrcSize.x);
    sf::Image OutputImage;
    OutputImage.create(SrcSize.x, SrcSize.y, sf::Color::Transparent);
    for (int y = 0; y < SrcSize.y; ++y)
    {
        for (int x = 0; x < SrcSize.x; ++x)
        {
            int i = y * SrcSize.x + x;
            if (Shape.m_Cells[i].m_Exists &&
                (Shape.m_Cells[i].m_EdgeExists[0] || Shape.m_Cells[i].m_EdgeExists[1] || Shape.m_Cells[i].m_EdgeExists[2] || Shape.m_Cells[i].m_EdgeExists[3])
            )
            {
                OutputImage.setPixel(x, y, sf::Color::Black);
            }
            else
            {
                OutputImage.setPixel(x, y, sf::Color::White);
            }
        }
    }

    std::cout << Path.stem().string() + ".outline.png" << std::endl;
    OutputImage.saveToFile(Path.stem().string() + ".outline.png");
}
