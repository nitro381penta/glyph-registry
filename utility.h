#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <optional>

// =============================
// Data model
// =============================

enum class GlyphType {
    Model,
    Texture,
    Audio,
    Script,
    Shader,
    Material,
    Animation,
    Other
};

struct Glyph {
    int id = -1;
    std::string name;
    GlyphType type = GlyphType::Other;
    std::string path;
    double sizeMB = 0.0;
    std::string tag;
};

// =============================
// Registry (registry.cpp)
// =============================

void addGlyph(std::vector<Glyph>& glyphs);
bool updateGlyph(std::vector<Glyph>& glyphs, int id);
bool removeGlyph(std::vector<Glyph>& glyphs, int id);
void listGlyphs(const std::vector<Glyph>& glyphs);

std::optional<size_t> findGlyphById(const std::vector<Glyph>& glyphs, int id);

// =============================
// Search & filtering (search.cpp)
// =============================

std::vector<Glyph> searchByName(const std::vector<Glyph>& glyphs, const std::string& keyword);
std::vector<Glyph> filterByType(const std::vector<Glyph>& glyphs, GlyphType type);
std::vector<Glyph> filterByTag(const std::vector<Glyph>& glyphs, const std::string& tag);

// =============================
// Storage (storage.cpp)
// =============================

bool saveGlyphs(const std::vector<Glyph>& glyphs, const std::string& filename);
bool loadGlyphs(std::vector<Glyph>& glyphs, const std::string& filename);

// =============================
// Stats (stats.cpp)
// =============================

void showStats(const std::vector<Glyph>& glyphs);

// =============================
// Helpers (text_processor.cpp)
// =============================

// String helpers
std::string trim(const std::string& s);
std::string toLower(std::string s);

// Enum conversion
std::string glyphTypeToString(GlyphType type);
std::optional<GlyphType> parseGlyphType(const std::string& input);

// Validation helpers
bool fileExists(const std::string& path);
bool pathAlreadyUsed(const std::vector<Glyph>& glyphs, const std::string& path);

// Safe input (q = back/quit depending on caller)
std::optional<std::string> readLineOrQ(const std::string& prompt);        // returns nullopt on q/quit/exit
std::optional<std::string> readNonEmptyLineOrQ(const std::string& prompt);// nullopt on q
std::optional<int> readIntOrQ(const std::string& prompt);                // nullopt on q
std::optional<int> readIntInRangeOrQ(const std::string& prompt, int minVal, int maxVal);
std::optional<double> readDoubleMinOrQ(const std::string& prompt, double minVal);

#endif // UTILITY_H