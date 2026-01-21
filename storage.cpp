#include "utility.h"

#include <fstream>
#include <iostream>
#include <iomanip>   // std::quoted

// Simple, robust format: one glyph per line:
// id "name" "type" "path" sizeMB "tag"
bool saveGlyphs(const std::vector<Glyph>& glyphs, const std::string& filename) {
    try {
        std::ofstream out(filename);
        if (!out) return false;

        for (const auto& g : glyphs) {
            out << g.id << " "
                << std::quoted(g.name) << " "
                << std::quoted(glyphTypeToString(g.type)) << " "
                << std::quoted(g.path) << " "
                << g.sizeMB << " "
                << std::quoted(g.tag)
                << "\n";
        }
        return true;
    } catch (...) {
        return false;
    }
}

bool loadGlyphs(std::vector<Glyph>& glyphs, const std::string& filename) {
    try {
        std::ifstream in(filename);
        if (!in) return false;

        std::vector<Glyph> loaded;
        while (true) {
            Glyph g;
            std::string typeStr;

            if (!(in >> g.id)) break;
            if (!(in >> std::quoted(g.name))) return false;
            if (!(in >> std::quoted(typeStr))) return false;
            if (!(in >> std::quoted(g.path))) return false;
            if (!(in >> g.sizeMB)) return false;
            if (!(in >> std::quoted(g.tag))) return false;

            auto typeOpt = parseGlyphType(typeStr);
            g.type = typeOpt.value_or(GlyphType::Other);

            loaded.push_back(g);
        }

        glyphs = std::move(loaded);
        return true;
    } catch (...) {
        return false;
    }
}