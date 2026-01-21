#include "utility.h"

#include <iostream>
#include <map>

void showStats(const std::vector<Glyph>& glyphs) {
    std::cout << "\n--- Stats ---\n";

    if (glyphs.empty()) {
        std::cout << "No glyphs stored.\n";
        return;
    }

    double totalSize = 0.0;
    std::map<std::string, int> byType;
    std::map<std::string, int> byTag;

    for (const auto& g : glyphs) {
        totalSize += g.sizeMB;
        byType[glyphTypeToString(g.type)]++;
        byTag[toLower(trim(g.tag))]++;
    }

    std::cout << "Count: " << glyphs.size() << "\n";
    std::cout << "Total size (MB): " << totalSize << "\n";

    std::cout << "\nBy type:\n";
    for (const auto& [k, v] : byType) {
        std::cout << "  " << k << ": " << v << "\n";
    }

    std::cout << "\nTop tags:\n";
    for (const auto& [k, v] : byTag) {
        std::cout << "  " << (k.empty() ? "(empty)" : k) << ": " << v << "\n";
    }
}