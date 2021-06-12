#include <iostream>
#include "compression.hpp"

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, width>, height>& image)
{
    std::vector<std::pair<uint8_t, uint8_t>> result{};
    result.reserve(width * height);
    const auto size_of_image = image.size();

    for (size_t i = 0; i < size_of_image; ++i)
    {
        result.push_back(std::make_pair(image[i][0], 1));
        const auto size_of_pair = image.at(i).size();

        for (size_t j = 1;j < size_of_pair; ++j)
        {
            if (image[i][j] == result.back().first)
            {
                result.back().second++;
            }
            else
            {
                result.push_back(std::make_pair(image[i][j], 1));
            }
        }
        
    }
    return result;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& compressed_image)
{
    std::array<std::array<uint8_t, width>, height> decompressed_image{};
    size_t n = 0;
    size_t m = 0;

    for (auto& row : compressed_image)
    {
        for (size_t j = 0; j < row.second; ++j)
        {
            if (m >= width)
            {
                n++;
                m = 0;
            }

            if (n >= height)
            {
                break;
            }
            
            decompressed_image.at(n).at(m) = row.first;
            m++;
        }
    }
    return decompressed_image;
}

void printMap(const std::array<std::array<uint8_t, width>, height>& map)
{
    for (auto& row : map)
    {
        for (auto& col : row)
        {
            std::cout << col << ' ';
        }
        std::cout << '\n';
    }
}
