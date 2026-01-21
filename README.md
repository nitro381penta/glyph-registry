# GLYPH — Command-Line Asset Registry (C++)

Glyph is a lightweight command-line utility written in modern C++ for the structured registration, organization, and analysis of digital assets.

The tool provides a simple, engine-agnostic registry layer that allows users to catalog assets such as models, textures, audio files, scripts, shaders or documents **without modifying or relocating the original files**.

Glyph is designed for small to medium-scale projects, research workflows, prototyping environments, and educational contexts where transparency, simplicity, and control are preferred over heavy asset management systems.


## Project Description

In many technical and creative workflows, digital assets accumulate across projects, directories, and iterations. Over time, this leads to reduced visibility, duplicated resources, and inefficient reuse.

Glyph addresses this problem by introducing a minimal, file-independent registry that stores metadata about assets while leaving the underlying file system untouched. The registry can be queried, filtered, and analyzed through a safe, menu-driven command-line interface.

The project emphasizes clarity of design, robustness of input handling, and modular software architecture.


## Core Functionality

- Register assets with structured metadata
- List all registered assets
- Search and filter assets by name, type, or tag
- Remove or update existing registry entries
- Display aggregate statistics about the asset collection
- Persist registry data to disk and reload it across sessions
- Validate all user input to prevent invalid states


## Data Model

Each asset entry (“Glyph”) consists of:
- Unique identifier
- Human-readable name
- Asset type (e.g. model, texture, audio, script)
- File system path
- File size (in megabytes)
- Optional semantic tag

Assets are referenced by path only; Glyph does not copy, move, or alter files.


## Project Structure

glyph/
- main.cpp
- registry.cpp
- search.cpp
- storage.cpp
- stats.cpp
- text_processor.cpp
- utility.h


## Usage

Compile the project:
(bash)
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o glyph

Run the project:
(bash)
./glyph

The interface is menu-based and interactive. 
At any input prompt, the user may enter q to cancel the current operation or exit safely.


## Requirements

- C++17 compatible compiler (g++ or clang++)
- Standard Library only


## License

MIT License:
Feel free to use, modify and extend.


## Author

Created by nitro381penta.


