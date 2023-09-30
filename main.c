#include <ncurses.h>
#include <unistd.h>

void Collision() {
    initscr();  // Initialize ncurses screen
    cbreak();   // Disable line buffering
    noecho();   // Disable printing user input

    WINDOW *collisionWin = newwin(10, 30, 0, 0); // Create a new window
    box(collisionWin, 0, 0); // Draw a box around the window
    wrefresh(collisionWin); // Update the window

    int ch;
    while (1) { // Add a while loop to print "Has Collided" continuously
        mvwprintw(collisionWin, 1, 1, "Has Collided"); // Print "Has Collided" in the window
        wrefresh(collisionWin); // Update the window
        napms(100); // Add a small delay to prevent the loop from running too fast
        if ((ch = getch()) == 'g') { // Exit the loop if 'g' key is pressed
            break;
        }
    }

    delwin(collisionWin); // Delete the window

    endwin();  // Cleanup ncurses screen
}

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // Print initial message
    mvprintw(0, 0, "Move the mouse to make the word follow it!");

    int one = -1;
    int two = 1; // Assign a value to the variable `one`
    while (1) {
        MEVENT event;
        int ch = getch();
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
            clear();
            mvprintw(event.y, event.x, "*");
            refresh();
            if (event.y == 12) {
                mvprintw(12, 1, " ");
                mvprintw(12, 1, "*");
                Collision(); // Call Collision() when collision occurs
                mvprintw(12, 1, " ");
                break; // Add a break statement to exit the loop after calling Collision()
            }
        }
    }

    // End ncurses
    endwin();
