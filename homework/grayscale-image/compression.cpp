#include <iostream>
#include <algorithm>
#include "compression.hpp"

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, width>, height>& image)
{
    std::vector<std::pair<uint8_t, uint8_t>> result;
    std::vector<uint8_t> tmp;
    result.reserve(width * height);
    const auto size_of_image = image.size();

    std::for_each(image.cbegin(), image.cend(), [&tmp](auto &row)
    {
        std::copy(row.begin(), row.end(), std::back_inserter(tmp));
    });

    result.push_back(std::make_pair(tmp.at(0), (uint8_t)1));
    std::for_each(tmp.cbegin(), tmp.cend(), [&result](auto &x)
    {
        if (result.back().first == x)
        {
            result.back().second++;
        }
        else
        {
            result.push_back(std::make_pair(x, 1));
        }
    });

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
