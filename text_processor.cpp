#include "utility.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <limits>
#include <stdexcept>

// ---------- String helpers ----------

std::string trim(const std::string& s) {
    auto isNotSpace = [](unsigned char ch) { return !std::isspace(ch); };

    size_t start = 0;
    while (start < s.size() && !isNotSpace(static_cast<unsigned char>(s[start]))) start++;

    if (start == s.size()) return "";

    size_t end = s.size() - 1;
    while (end > start && !isNotSpace(static_cast<unsigned char>(s[end]))) end--;

    return s.substr(start, end - start + 1);
}

std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

// ---------- Enum conversion ----------

std::string glyphTypeToString(GlyphType type) {
    switch (type) {
        case GlyphType::Model: return "model";
        case GlyphType::Texture: return "texture";
        case GlyphType::Audio: return "audio";
        case GlyphType::Script: return "script";
        case GlyphType::Shader: return "shader";
        case GlyphType::Material: return "material";
        case GlyphType::Animation: return "animation";
        default: return "other";
    }
}

std::optional<GlyphType> parseGlyphType(const std::string& input) {
    std::string s = toLower(trim(input));

    if (s == "model") return GlyphType::Model;
    if (s == "texture") return GlyphType::Texture;
    if (s == "audio") return GlyphType::Audio;
    if (s == "script") return GlyphType::Script;
    if (s == "shader") return GlyphType::Shader;
    if (s == "material") return GlyphType::Material;
    if (s == "animation") return GlyphType::Animation;
    if (s == "other") return GlyphType::Other;

    return std::nullopt;
}

// ---------- Validation helpers ----------

bool fileExists(const std::string& path) {
    std::error_code ec;
    return std::filesystem::exists(path, ec);
}

bool pathAlreadyUsed(const std::vector<Glyph>& glyphs, const std::string& path) {
    const std::string p = toLower(trim(path));
    for (const auto& g : glyphs) {
        if (toLower(trim(g.path)) == p) return true;
    }
    return false;
}

// ---------- Safe input helpers (getline-based) ----------

static bool isQuitToken(const std::string& s) {
    std::string t = toLower(trim(s));
    return t == "q" || t == "quit" || t == "exit";
}

std::optional<std::string> readLineOrQ(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        // EOF or stream failure => treat as quit
        return std::nullopt;
    }
    if (isQuitToken(line)) return std::nullopt;
    return trim(line);
}

std::optional<std::string> readNonEmptyLineOrQ(const std::string& prompt) {
    while (true) {
        auto lineOpt = readLineOrQ(prompt);
        if (!lineOpt) return std::nullopt;

        if (!lineOpt->empty()) return lineOpt;
        std::cout << "Please enter a non-empty value (or 'q').\n";
    }
}

std::optional<int> readIntOrQ(const std::string& prompt) {
    while (true) {
        auto lineOpt = readLineOrQ(prompt);
        if (!lineOpt) return std::nullopt;

        try {
            size_t pos = 0;
            int value = std::stoi(*lineOpt, &pos);
            if (pos == lineOpt->size()) return value;
        } catch (...) {
            // fall through
        }

        std::cout << "Please enter a whole number (or 'q').\n";
    }
}

std::optional<int> readIntInRangeOrQ(const std::string& prompt, int minVal, int maxVal) {
    while (true) {
        auto vOpt = readIntOrQ(prompt);
        if (!vOpt) return std::nullopt;

        if (*vOpt >= minVal && *vOpt <= maxVal) return vOpt;
        std::cout << "Please enter a number between " << minVal
                  << " and " << maxVal << " (or 'q').\n";
    }
}

std::optional<double> readDoubleMinOrQ(const std::string& prompt, double minVal) {
    while (true) {
        auto lineOpt = readLineOrQ(prompt);
        if (!lineOpt) return std::nullopt;

        try {
            size_t pos = 0;
            double value = std::stod(*lineOpt, &pos);
            if (pos == lineOpt->size() && value >= minVal) return value;
        } catch (...) {
            // fall through
        }

        std::cout << "Please enter a number >= " << minVal << " (or 'q').\n";
    }
}