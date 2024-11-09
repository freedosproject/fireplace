/* simulate a fire */

#include <stdio.h>
#include <stdlib.h>                    /* rand */
#include <time.h>                      /* time */

#include <conio.h>
#include <graph.h>                     /* for colors */

#include <i86.h>                       /* delay */

void flame(int col)
{
    char str[4];                /* 0, 1, 2, 3 */
    char flame[4] = { 0xb0, 0xb1, 0xb2, 0xdb };
    int i, n;

    /* fill with spaces + flame */

    n = rand() % 4;                    /* 0, 1, 2, 3 */

    for (i = 0; i < n; i++) {
        str[i] = ' ';
    }

    for (n = 0; i < 4; i++) {
        str[i] = flame[n++];
    }

    /* draw */

    if (rand() & 1) {
        _settextcolor(6);              /* orange */
    }
    else {
        _settextcolor(14);             /* br yellow */
    }

    _settextwindow(10, col, 14, col);  /* 0, 1, 2, 3, 4 (one more than str) */
    _settextposition(1, 1);            /* top left */
    _outmem(str, 4);
}

int main()
{
    int col;

    srand(time(NULL));

    if (_setvideomode(_TEXTC80) == 0) {
        puts("failed video mode");
        return 1;
    }

    _displaycursor(_GCURSOROFF);

    /* rug frame */

    _setbkcolor(2);                    /* green */
    _settextwindow(14, 29, 20, 50);
    _clearscreen(_GWINDOW);

    /* chimney frame */

    _setbkcolor(4);                    /* red */
    _settextwindow(1, 30, 14, 49);     /* 1 narrower than rug */
    _clearscreen(_GWINDOW);

    /* fireplace frame */

    _settextwindow(9, 28, 14, 51);     /* 1 wider than rug */
    _clearscreen(_GWINDOW);

    /* flame */

    _setbkcolor(0);                    /* black */

    do {
        for (col = 30; col < 50; col++) {
            flame(col);
        }
        delay(100);                    /* delay for 1/10 second */
    } while (kbhit() == 0);

    /* "eat" the key that was pressed */

    if (getch() == 0) {
        getch();
    }

    _setvideomode(_DEFAULTMODE);

    return 0;
}
