#ifndef CONFIG_H
#define CONFIG_H

#include <Windows.h>
#include <unordered_set>

#define TEXT_BRIGHT_CYAN     (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_RED      (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_GREEN    (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_YELLOW   (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_BLUE     (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_MAGENTA  (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_WHITE    (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_LIME     (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define TEXT_BRIGHT_SKYBLUE  (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define TEXT_CYAN      (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define TEXT_WHITE     (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define TEXT_RED             (FOREGROUND_RED)
#define TEXT_GREEN           (FOREGROUND_GREEN)
#define TEXT_BLUE            (FOREGROUND_BLUE)
#define TEXT_MAGENTA         (FOREGROUND_RED | FOREGROUND_BLUE)
#define TEXT_YELLOW          (FOREGROUND_RED | FOREGROUND_GREEN)

constexpr WORD FOOD_COLOR = TEXT_BRIGHT_WHITE;
constexpr WORD TITLE_COLOR = TEXT_BRIGHT_CYAN;
constexpr WORD MAP_COLOR = TEXT_GREEN;
constexpr WORD END_TEXT_COLOR = TEXT_BRIGHT_WHITE;

constexpr int COLS = 60;
constexpr int ROWS = 30;
constexpr int SNAKE_ARRAYS_SIZE = 100;
constexpr int NUM_OF_PLAYERS = 4;

constexpr char SNAKE_CHAR = static_cast<char>(219);
constexpr char FOOD_CHAR = static_cast<char>(254);

constexpr char CORNER1 = static_cast<char>(218);	// ┌
constexpr char CORNER2 = static_cast<char>(191);	// ┐
constexpr char CORNER3 = static_cast<char>(192);	// └
constexpr char CORNER4 = static_cast<char>(217);	// ┘
constexpr char DASH = static_cast<char>(196);		// ─
constexpr char BAR = static_cast<char>(179);		// │
constexpr char DOT = static_cast<char>(250);		// ·

//hash functions for set of COORDs
struct COORDHash {
    std::size_t operator()(const COORD& c) const {
        return std::hash<SHORT>()(c.X) ^ (std::hash<SHORT>()(c.Y) << 1);
    }
};
struct COORDEqual {
    bool operator()(const COORD& a, const COORD& b) const {
        return a.X == b.X && a.Y == b.Y;
    }
};
//for player input keys
struct PlayerKeys {
    int up, down, left, right;
    bool usesArrowKeys;
};

#endif
