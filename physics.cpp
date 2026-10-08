#include <graphics.h>
#include <math.h>
#include <cmath>

int gd = DETECT, gm;
double w = M_PI / 6, t = 0, x, y;

int main()
{
    initwindow(1280, 720, "Dao dong dieu hoa");
    while (1)
    {
        cleardevice();
        circle(640, 360, 250);
        line(390, 360, 890, 360);
        line(640, 610, 640, 110);
        x = 250 * cos(w * t) + 640;
        y = -250 * sin(w * t) + 360;
        circle(x, 360, 10);
        circle(x, y, 10);
        line(x, 360, x, y);
        t += M_PI / 90;
        delay(10);
    }
    getch();
    closegraph();
    return 0;
}