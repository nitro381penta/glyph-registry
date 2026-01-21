#include "utility.h"

#include <algorithm>

std::vector<Glyph> searchByName(const std::vector<Glyph>& glyphs, const std::string& keyword) {
    std::vector<Glyph> out;
    std::string key = toLower(trim(keyword));

    for (const auto& g : glyphs) {
        if (toLower(g.name).find(key) != std::string::npos) {
            out.push_back(g);
        }
    }
    return out;
}

std::vector<Glyph> filterByType(const std::vector<Glyph>& glyphs, GlyphType type) {
    std::vector<Glyph> out;
    for (const auto& g : glyphs) {
        if (g.type == type) out.push_back(g);
    }
    return out;
}

std::vector<Glyph> filterByTag(const std::vector<Glyph>& glyphs, const std::string& tag) {
    std::vector<Glyph> out;
    std::string t = toLower(trim(tag));

    for (const auto& g : glyphs) {
        if (toLower(trim(g.tag)) == t) out.push_back(g);
    }
    return out;
}