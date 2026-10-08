#include <graphics.h>
#include <winuser.h>

int gd = DETECT, gm;
char c;

class Player {
public:
    int x1, y1, x2, y2;
    Player(int x1, int y1, int x2, int y2) {
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
    }
    void move(char c) {
        if (c == 'a') {
            x1 -= 10;
            x2 -= 10;
        }
        if (c == 'd') {
            x1 += 10;
            x2 += 10;
        }
        if (c == 's') {
            y1 += 10;
            y2 += 10;
        }
        if (c == 'w') {
            y1 -= 10;
            y2 -= 10;
        }
    }
};

class Ball {
public:
    int x1, y1, x2, y2;
    Ball(int x1, int y1, int x2, int y2) {
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
    }
    void collison(Player p) {
        if (p.x1 == x2 && p.y1 <= y1 && p.y2 >= y2) {
            x1 -= 10;
            x2 -= 10;
        }
        if (p.x2 == x1 && p.y1 <= y1 && p.y2 >= y2) {
            x1 += 10;
            x2 += 10;
        }
        if (p.y1 == y2 && p.x1 <= x1 && p.x2 >= x2) {
            y1 -= 10;
            y2 -= 10;
        }
        if (p.y2 == y1 && p.x1 <= x1 && p.x2 >= x2) {
            y1 += 10;
            y2 += 10;
        }
    }
};

void menu() {
    cleardevice();
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(getmaxx() / 2, getmaxy() / 2 - 100, "1: Resume");
    outtextxy(getmaxx() / 2, getmaxy() / 2, "2: Exit to Desktop");
    c = getch();
    if (c == '1') return;
    if (c == '2') exit(0);
}

int main() {
    initwindow(1280, 720, "The ball game");

    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
    setcolor(WHITE);
    outtextxy(getmaxx() / 2, getmaxy() / 2 - 100, "The ball game");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(getmaxx() / 2, getmaxy() / 2, "-Press any key-");
    outtextxy(getmaxx() / 2, 700, "-Made by Nguyen Huu Luan-");
    getch();

    Player p1(300, 300, 400, 400);
    Ball ball(700, 300, 730, 330);
    while (1) {
        cleardevice();
        setcolor(RED);
        rectangle(p1.x1, p1.y1, p1.x2, p1.y2);
        setcolor(WHITE);
        rectangle(ball.x1, ball.y1, ball.x2, ball.y2);
        c = getch();
        if (c == char(27)) menu(); // Nút Esc để mở menu
        p1.move(c);
        ball.collison(p1);
    }

    closegraph();
    return 0;
}