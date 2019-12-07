#include "BitmapFont.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <pplinterface.h>
#include <sstream>

/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name: Text programming
Course name: CS230
Term: Spring Year(2019)
------------------------------------------------------------------------*/

namespace CS230
{
    bool BitmapFont::LoadFromFile(const std::filesystem::path& filename)
    {
      //  Texture _texture;
        std::wstring _string;

        CanParseFile(filename);

        for (int i = 0; i < details.pagesCount; i++) {
            _string = filename.parent_path().append(details.pageNames[i]);
           // _texture.LoadFromPNG(_string);

       //     pageTextures.push_back(std::move(_texture));
        }
        return true;
    }

   // bool BitmapFont::LoadDefinition(const std::wstring& font_definition, std::vector<Texture> page_textures)
   // {
   //     std::wistringstream stream(font_definition);
   //     if (!CanParseStream(stream))
   //         return false;
   // //    pageTextures = std::move(page_textures);
   ////     return pageTextures.size() == details.pagesCount;
   // }

    const BitmapFont::information& BitmapFont::GetInformation() const noexcept
    {
        return details;
    }

    BitmapFont::character BitmapFont::GetCharacter(wchar_t character_id) const noexcept
    {
        if (characters.find(character_id) == characters.end())
        {
            return character{};
        }
        else
        {
            return characters.at(character_id);
        }
    }
    unsigned short BitmapFont::GetLineHeight() const noexcept
    {
        return details.lineHeight;
    }

 /*   const Texture& BitmapFont::GetTexture(int page_index) const noexcept
    {
        assert(!pageTextures.empty());
        assert(page_index >= 0 && page_index <= pageTextures.size());

        return pageTextures.at(page_index);
    }*/

    bool BitmapFont::HasCharacter(wchar_t character_id) const noexcept
    {
        if (characters.find(character_id) != characters.end())
        {
            return true;
        }
        return false;
    }

    bool BitmapFont::CanParseFile(const std::filesystem::path& filename)
    {
        std::wifstream pathValue;
        pathValue.open(filename.c_str());

        return CanParseStream(pathValue);
    }

    bool BitmapFont::CanParseStream(std::wistream& stream)
    {
        std::wstring Line;
        std::wstring Read, Key, Value;
        std::size_t  i;
        std::size_t  totalSize;

        while (!stream.eof())
        {
            std::wstringstream LineStream;
            std::getline(stream, Line);
            LineStream << Line;

            LineStream >> Read;

            if (Read == L"info")
            {
                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);

                    Converter << Value;

                    if (Key == L"face")
                    {
                        LineStream >> Read;
                        while (!LineStream.eof())
                        {
                            if (!Read.find('"'))
                            {
                                Value = Read;
                                Converter << " " << Value;
                                LineStream >> Read;
                            }
                            else
                            {
                                Value = Read;
                                Converter << " " << Value;
                                break;
                            }
                        }
                        Converter >> details.fontName;
                    }
                    if (Key == L"size")
                    {
                        Converter >> details.fontSize;
                    }
                }
            }
            else if (Read == L"page")
            {
                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    totalSize = Read.size();
                    Value = Read.substr(i + 2, totalSize - 7);

                    Converter << Value;

                    if (Key == L"file")
                    {
                        details.pageNames.push_back(Value);
                    }
                }
            }
            else if (Read == L"common")
            {
                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);

                    Converter << Value;
                    if (Key == L"lineHeight")
                        Converter >> details.lineHeight;
                    else if (Key == L"scaleW")
                        Converter >> details.imageWidth;
                    else if (Key == L"scaleH")
                        Converter >> details.imageHeight;
                    else if (Key == L"pages")
                        Converter >> details.pagesCount;
                }
            }
            else if (Read == L"char")
            {
                character chars;

                while (!LineStream.eof())
                {
                    std::wstringstream Converter;
                    LineStream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);

                    Converter << Value;
                    if (Key == L"id")
                        Converter >> reinterpret_cast<unsigned short&>(chars.id);
                    else if (Key == L"x")
                        Converter >> characters[chars.id].x;
                    else if (Key == L"y")
                        Converter >> characters[chars.id].y;
                    else if (Key == L"width")
                        Converter >> characters[chars.id].width;
                    else if (Key == L"height")
                        Converter >> characters[chars.id].height;
                    else if (Key == L"xoffset")
                        Converter >> characters[chars.id].xOffset;
                    else if (Key == L"yoffset")
                        Converter >> characters[chars.id].yOffset;
                    else if (Key == L"xadvance")
                        Converter >> characters[chars.id].xAdvance;
                    else if (Key == L"page")
                        Converter >> reinterpret_cast<unsigned short&>(characters[chars.id].page);
                }
            }
        }
        return true;
    }
}