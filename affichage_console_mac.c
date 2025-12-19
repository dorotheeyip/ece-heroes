#include "affichage_console_mac.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

static int current_fg = COLOR_WHITE;
static int current_bg = COLOR_BLACK;

void init_console() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, current_fg, current_bg);
}

void end_console() {
    endwin();
}

// Effacer la console
// void clrscr() {
//     clear();
//     refresh();
// }

// Déplacer le curseur à la position x, y
void gotoxy(int x, int y) {
    // Ne déplacer le curseur que si stdout est un terminal
    if (isatty(STDOUT_FILENO)) {
        printf("\033[%d;%dH", y + 1, x + 1); // Les codes ANSI sont basés sur 1
        fflush(stdout);                      // Vider pour s'assurer que le curseur se déplace immédiatement
    }
}

// Effacer la suite de la ligne
void delete_line() {
    printf("\033[K"); // Clear from cursor to end of line
    fflush(stdout);
}

// Récupérer la position horizontale du curseur
int wherex() {
    int y, x;
    getyx(stdscr, y, x);
    return x;
}

// Récupérer la position verticale du curseur
int wherey() {
    int y, x;
    getyx(stdscr, y, x);
    return y;
}

static int ansi_fg(int color) {
    static const int map[16] = {
        30, // 0 black
        31, // 1 blue
        32, // 2 green
        33, // 3 cyan
        34, // 4 red
        35, // 5 magenta
        36, // 6 brown/yellow
        37, // 7 light gray
        90, // 8 dark gray
        91, // 9 bright blue
        92, // 10 bright green
        93, // 11 bright cyan
        94, // 12 bright red
        95, // 13 bright magenta
        96, // 14 yellow
        97  // 15 white
    };
    return map[color & 0x0F];
}

static int ansi_bg(int color) {
    static const int map[16] = {
        40, // 0 black
        44, // 1 blue
        42, // 2 green
        46, // 3 cyan
        41, // 4 red
        45, // 5 magenta
        43, // 6 brown/yellow
        47, // 7 light gray
        100, // 8 dark gray
        104, // 9 bright blue
        102, // 10 bright green
        106, // 11 bright cyan
        101, // 12 bright red
        105, // 13 bright magenta
        103, // 14 yellow
        107  // 15 white
    };
    return map[color & 0x0F];
}

// Changer la couleur du texte
void text_color(int color) {
    printf("\033[%dm", ansi_fg(color));
    fflush(stdout);
}

// Changer la couleur de fond
void bg_color(int color) {
    printf("\033[%dm", ansi_bg(color));
    fflush(stdout);
}

// Changer la couleur du texte et du fond
void set_color(int colorT, int colorBg) {
    printf("\033[%d;%dm", ansi_fg(colorT), ansi_bg(colorBg));
    fflush(stdout);
}


// Cacher le curseur
void hide_cursor() {
    curs_set(0);
}

// Montrer le curseur
void show_cursor() {
    curs_set(1);
}

void Sleep(int milliseconds) {
    napms(milliseconds);
}
