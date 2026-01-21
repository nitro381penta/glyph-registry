#include "utility.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

std::optional<size_t> findGlyphById(const std::vector<Glyph>& glyphs, int id) {
    for (size_t i = 0; i < glyphs.size(); ++i) {
        if (glyphs[i].id == id) return i;
    }
    return std::nullopt;
}

static int nextId(const std::vector<Glyph>& glyphs) {
    int maxId = 0;
    for (const auto& g : glyphs) maxId = std::max(maxId, g.id);
    return maxId + 1;
}

void addGlyph(std::vector<Glyph>& glyphs) {
    std::cout << "\nAdd Glyph\nType 'q' to go back.\n";

    Glyph g;
    g.id = nextId(glyphs);

    auto nameOpt = readNonEmptyLineOrQ("Name: ");
    if (!nameOpt) return;
    g.name = *nameOpt;

    auto typeStrOpt = readNonEmptyLineOrQ("Type (model/texture/audio/script/shader/material/animation/other): ");
    if (!typeStrOpt) return;

    auto typeOpt = parseGlyphType(*typeStrOpt);
    if (!typeOpt) {
        std::cout << "Unknown type. Cancelled.\n";
        return;
    }
    g.type = *typeOpt;

    auto pathOpt = readNonEmptyLineOrQ("Path: ");
    if (!pathOpt) return;
    g.path = *pathOpt;

    if (pathAlreadyUsed(glyphs, g.path)) {
        std::cout << "That path is already used by another glyph. Cancelled.\n";
        return;
    }

    auto sizeOpt = readDoubleMinOrQ("Size (MB, >= 0): ", 0.0);
    if (!sizeOpt) return;
    g.sizeMB = *sizeOpt;

    auto tagOpt = readNonEmptyLineOrQ("Tag: ");
    if (!tagOpt) return;
    g.tag = *tagOpt;

    glyphs.push_back(g);
    std::cout << "Added glyph with id " << g.id << ".\n";
}

bool removeGlyph(std::vector<Glyph>& glyphs, int id) {
    auto idxOpt = findGlyphById(glyphs, id);
    if (!idxOpt) return false;

    glyphs.erase(glyphs.begin() + static_cast<long>(*idxOpt));
    std::cout << "Removed.\n";
    return true;
}

bool updateGlyph(std::vector<Glyph>& glyphs, int id) {
    auto idxOpt = findGlyphById(glyphs, id);
    if (!idxOpt) return false;

    Glyph& g = glyphs[*idxOpt];

    std::cout << "\nUpdate Glyph [" << g.id << "]\n";
    std::cout << "Type 'q' to cancel.\n";

    std::cout << "Current name: " << g.name << "\n";
    auto nameOpt = readNonEmptyLineOrQ("New name: ");
    if (!nameOpt) return false;
    g.name = *nameOpt;

    std::cout << "Current type: " << glyphTypeToString(g.type) << "\n";
    auto typeStrOpt = readNonEmptyLineOrQ("New type: ");
    if (!typeStrOpt) return false;
    auto typeOpt = parseGlyphType(*typeStrOpt);
    if (!typeOpt) {
        std::cout << "Unknown type. Cancelled.\n";
        return false;
    }
    g.type = *typeOpt;

    std::cout << "Current path: " << g.path << "\n";
    auto pathOpt = readNonEmptyLineOrQ("New path: ");
    if (!pathOpt) return false;

    if (toLower(trim(*pathOpt)) != toLower(trim(g.path)) && pathAlreadyUsed(glyphs, *pathOpt)) {
        std::cout << "That path is already used. Cancelled.\n";
        return false;
    }
    g.path = *pathOpt;

    std::cout << "Current sizeMB: " << g.sizeMB << "\n";
    auto sizeOpt = readDoubleMinOrQ("New sizeMB (>=0): ", 0.0);
    if (!sizeOpt) return false;
    g.sizeMB = *sizeOpt;

    std::cout << "Current tag: " << g.tag << "\n";
    auto tagOpt = readNonEmptyLineOrQ("New tag: ");
    if (!tagOpt) return false;
    g.tag = *tagOpt;

    std::cout << "Updated.\n";
    return true;
}

void listGlyphs(const std::vector<Glyph>& glyphs) {
    if (glyphs.empty()) {
        std::cout << "No glyphs stored.\n";
        return;
    }

    std::cout << "\n--- Glyphs (" << glyphs.size() << ") ---\n";
    for (const auto& g : glyphs) {
        std::cout << "[" << g.id << "] "
                  << g.name << " | "
                  << glyphTypeToString(g.type) << " | "
                  << g.path << " | "
                  << g.sizeMB << " MB | "
                  << g.tag << "\n";
    }
}