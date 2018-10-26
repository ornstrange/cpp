#include <ncurses.h>
#include <string>
using namespace std;


int main() {
    int cols, rows;
    bool counter = false;

    initscr();
    getmaxyx(stdscr, rows, cols);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    raw();
    keypad(stdscr, TRUE);
    noecho();
    getch();
    endwin();

    return 0;
}
