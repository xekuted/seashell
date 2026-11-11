#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "looks.h"


#define LOGO_COLS   22                  // terminal columns used by the shell
#define LOGO_ROWS   8                   // terminal rows used by the shell
#define LOGO_HEIGHT (LOGO_ROWS * 4)     // dot rows: 4 per character

#define WORD_COLS   44                  // terminal columns used by the title
#define WORD_ROWS   4                   // terminal rows used by the title
#define WORD_HEIGHT (WORD_ROWS * 4)
#define WORD_SPLIT  19                  // columns before this are "Sea" (green)

// Everything below is drawn with Braille characters. Each character is a cell
// of 2 dots across and 4 dots down, so the art is much finer than plain text.
//   '#' = lit dot (outline)    ':' = faint texture dot    '.' = empty

// The shell.
static const char *logo[LOGO_HEIGHT] = {
    "............................................",
    "................#############...............",
    "...............###....#....###..............",
    "...........######.....#.....######..........",
    ".........####..##...:.#.:...##..####........",
    ".........##....##....:#..:..##....##........",
    "........###....###:...#....###:...###.......",
    "......####......##.:..#....##..:...####.....",
    ".....###.##.....##..:.#....##.....##.###....",
    "....###...##.....##..:#...##.....##...###...",
    "....##.....##.:..##...#...##....##.....##...",
    "....##......##.:..##..#..##....##......##...",
    "....##.......##...##..#..##...##.......##...",
    "....####......##..###.#.###..##......####...",
    "......####.....##..##.#.##..##.....####.....",
    ".........####...##.##.#.##.##...####........",
    "...........####..##.#####.##..####..........",
    ".............####.#########.####............",
    "................#############...............",
    "..................#########.................",
    "....................#####...................",
    "............................................",
    "..................#########.................",
    ".............#######.....#######............",
    "............###...#########...###...........",
    "...........###..####.....####..###..........",
    "...........###..####.....####..###..........",
    "............###...#########...###...........",
    ".............#######.....#######............",
    "..................#########.................",
    "............................................",
    "............................................"
};

// Waves drawn as text on top of the shell ('=' prints as the wave glyph).
static const char *waves[LOGO_ROWS] = {
    "                      ",
    "                      ",
    "                      ",
    "                      ",
    "                      ",
    " ==               ==  ",
    "~~=                =~~",
    "                      "
};

// The "SeaShell" title.
static const char *word[WORD_HEIGHT] = {
    "...####..................................#####......###.......................###....###",
    ".########...............................#######.....###.......................###....###",
    ".########..............................########.....###.......................###....###",
    "###....##..............................###....#.....###.......................###....###",
    "###............#####.......######......##...........###.####.......#####......###....###",
    "###...........#######.....########.....###..........########......#######.....###....###",
    "######........###.####....##...###.....#####........#########....####.###.....###....###",
    ".#######.....###...###..........##.....########.....####..###....###...###....###....###",
    "..#######....###...###.......######.....#######.....###...###....###...###....###....###",
    "....#####....##########....########.......######....###...###....#########....###....###",
    "......###....#########....#########..........###....###...###....#########....###....###",
    "......###....###..........###...###..........###....###...###....###..........###....###",
    "##....###....###..........###..####....#.....###....###...###....###..........###....###",
    "#########.....####.###....###.#####....#########....###...###....####..###....###....###",
    "#########.....########....#########....########.....###...###.....########....###....###",
    "..#####.........#####......###..##......######......###...###......######.....###....###"
};

// Braille dot bits, indexed [row within cell][column within cell].
static const int dot_bit[4][2] = {
    {0x01, 0x08}, {0x02, 0x10}, {0x04, 0x20}, {0x40, 0x80}
};

// Work out the Braille bits for one character cell of an art grid.
// Sets *outline to 1 if the cell contains any '#' dot.
static int cell_bits(const char **art, int row, int cx, int *outline)
{
    int bits = 0;
    *outline = 0;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            char p = art[row * 4 + j][cx * 2 + i];
            if (p == '#' || p == ':')
                bits |= dot_bit[j][i];
            if (p == '#')
                *outline = 1;
        }
    }
    return bits;
}

// Print one Braille character (a space if the cell is empty).
static void print_braille(int bits, const char *color)
{
    if (bits == 0)
        printf(" ");
    else
        printf("%s\xE2%c%c" RESET, color, 0xA0 | (bits >> 6), 0x80 | (bits & 0x3F));
}

// Print one terminal row of the shell (no newline).
static void print_logo_row(int row)
{
    for (int cx = 0; cx < LOGO_COLS; cx++) {
        char w = waves[row][cx];
        if (w != ' ') {
            printf(TURQUOISE "%s" RESET, w == '=' ? "≈" : "~");
            continue;
        }

        int outline;
        int bits = cell_bits(logo, row, cx, &outline);
        print_braille(bits, outline ? CREAM : "\033[38;2;105;105;100m");
    }
}

// Print one terminal row of the title (no newline): "Sea" green, "Shell" orange.
static void print_word_row(int row)
{
    for (int cx = 0; cx < WORD_COLS; cx++) {
        int outline;
        int bits = cell_bits(word, row, cx, &outline);
        print_braille(bits, cx < WORD_SPLIT ? GREEN : ORANGE);
    }
}

// Print SeaShell startup banner: shell on the left, title and text on the right.
void print_banner(void)
{
    // Right-hand side, top to bottom: 4 title rows, version line, tagline.
    int side_rows = WORD_ROWS + 2;
    int start = (LOGO_ROWS - side_rows) / 2;    // center the text beside the shell

    printf("\n");

    for (int r = 0; r < LOGO_ROWS; r++) {
        print_logo_row(r);
        printf("   ");                          // gap between shell and text

        int i = r - start;
        if (i >= 0 && i < WORD_ROWS)
            print_word_row(i);
        else if (i == WORD_ROWS)
            printf(CREAM "────────────────── v0.1.0 ──────────────────" RESET);
        else if (i == WORD_ROWS + 1)
            printf(ITALIC CREAM "            A shell of your own" RESET);

        printf("\n");
    }

    printf("\n");
    printf("  " TURQUOISE "≈≈" RESET " Welcome to " BOLD ORANGE "SeaShell " RESET TURQUOISE "≈≈" RESET "\n");
    printf("  " RESET "Type 'help' to see available commands.\n");
    printf("\n");
}

// Display the interactive shell prompt.
void display_prompt(void)
{
    char *username = getenv("USER");
    char hostname[256];
    char cwd[1024];
    char *home = getenv("HOME");

    if (username == NULL)
        username = "user";

    if (gethostname(hostname, sizeof(hostname)) == -1)
        strcpy(hostname, "localhost");

    hostname[sizeof(hostname) - 1] = '\0';

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        strcpy(cwd, "?");

    printf("~ %s%s@%s%s\n", GREEN, username, hostname, RESET);

    if (home != NULL &&
        strncmp(cwd, home, strlen(home)) == 0 &&
        (cwd[strlen(home)] == '/' || cwd[strlen(home)] == '\0'))
    {
        printf("%s~%s%s %s❯ %s",
               CREAM, cwd + strlen(home), RESET, GREEN, RESET);
    }
    else
    {
        printf("%s%s%s %s❯ %s",
               CREAM, cwd, RESET, GREEN, RESET);
    }

    fflush(stdout);
}
