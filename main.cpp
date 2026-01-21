#include <iostream>
#include <vector>
#include <string>
#include "utility.h"

static void displayMenu() {
    std::cout << "\n=== GLYPH : Asset Registry Utility ===\n";
    std::cout << "Type 'q' at any prompt to quit.\n\n";
    std::cout << "1) Add glyph\n";
    std::cout << "2) List glyphs\n";
    std::cout << "3) Search / Filter\n";
    std::cout << "4) Remove glyph (by id)\n";
    std::cout << "5) Update glyph (by id)\n";
    std::cout << "6) Save glyphs\n";
    std::cout << "7) Load glyphs\n";
    std::cout << "8) Show stats\n";
    std::cout << "0) Exit\n";
}

static void printGlyphList(const std::vector<Glyph>& results) {
    if (results.empty()) {
        std::cout << "No results.\n";
        return;
    }

    std::cout << "\n--- Results (" << results.size() << ") ---\n";
    for (const auto& g : results) {
        std::cout << "[" << g.id << "] "
                  << g.name << " | "
                  << glyphTypeToString(g.type) << " | "
                  << g.path << " | "
                  << g.sizeMB << " MB | "
                  << g.tag << "\n";
    }
}

static void searchMenu(const std::vector<Glyph>& glyphs) {
    if (glyphs.empty()) {
        std::cout << "No glyphs stored yet.\n";
        return;
    }

    std::cout << "\nSearch / Filter\n";
    std::cout << "Type 'q' to go back.\n";
    std::cout << "1) Search by name (contains)\n";
    std::cout << "2) Filter by type\n";
    std::cout << "3) Filter by tag (case-insensitive)\n";
    std::cout << "0) Back\n";

    auto modeOpt = readIntInRangeOrQ("Choose (0-3): ", 0, 3);
    if (!modeOpt) return;
    int mode = *modeOpt;
    if (mode == 0) return;

    if (mode == 1) {
        auto keyOpt = readNonEmptyLineOrQ("Keyword: ");
        if (!keyOpt) return;
        printGlyphList(searchByName(glyphs, *keyOpt));
        return;
    }

    if (mode == 2) {
        auto typeStrOpt = readNonEmptyLineOrQ(
            "Type (model/texture/audio/script/shader/material/animation/other): "
        );
        if (!typeStrOpt) return;

        auto t = parseGlyphType(*typeStrOpt);
        if (!t) {
            std::cout << "Unknown type.\n";
            return;
        }
        printGlyphList(filterByType(glyphs, *t));
        return;
    }

    if (mode == 3) {
        auto tagOpt = readNonEmptyLineOrQ("Tag: ");
        if (!tagOpt) return;
        printGlyphList(filterByTag(glyphs, *tagOpt));
        return;
    }
}

int main() {
    std::vector<Glyph> glyphs;
    const std::string dbFile = "glyphs.db";

    std::cout << "Welcome to GLYPH.\n";

    bool running = true;
    while (running) {
        displayMenu();

        auto choiceOpt = readIntInRangeOrQ("Select an option (0-8 or q): ", 0, 8);
        if (!choiceOpt) {
            std::cout << "Goodbye.\n";
            break;
        }

        switch (*choiceOpt) {
            case 0:
                running = false;
                std::cout << "Goodbye.\n";
                break;

            case 1:
                addGlyph(glyphs);
                break;

            case 2:
                listGlyphs(glyphs);
                break;

            case 3:
                searchMenu(glyphs);
                break;

            case 4: {
                std::cout << "Type 'q' to go back.\n";
                auto idOpt = readIntOrQ("Enter glyph id to remove: ");
                if (!idOpt) break;
                if (!removeGlyph(glyphs, *idOpt)) std::cout << "Glyph not found.\n";
                break;
            }

            case 5: {
                std::cout << "Type 'q' to go back.\n";
                auto idOpt = readIntOrQ("Enter glyph id to update: ");
                if (!idOpt) break;
                if (!updateGlyph(glyphs, *idOpt)) std::cout << "Glyph not found (or cancelled).\n";
                break;
            }

            case 6:
                if (saveGlyphs(glyphs, dbFile)) std::cout << "Saved.\n";
                else std::cout << "Save failed.\n";
                break;

            case 7:
                if (loadGlyphs(glyphs, dbFile)) std::cout << "Loaded.\n";
                else std::cout << "Load failed.\n";
                break;

            case 8:
                showStats(glyphs);
                break;
        }
    }

    return 0;
}