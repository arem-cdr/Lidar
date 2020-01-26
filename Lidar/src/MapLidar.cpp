#include "MapLidar.h"

MapLidar::MapLidar()
{
    for (int i = 0; i < 180; i++)
    {

        cos_p[i] = cos(i * 3.1416 / 180.0);
        sin_p[i] = sin(i * 3.1416 / 180.0);
    }
    for (int i = 0; i < 180; i++)
    {
        cos_p[i + 180] = cos((i + 180 - 360) * 3.1416 / 180.0);
        sin_p[i + 180] = sin((i + 180 - 360) * 3.1416 / 180.0);
    }
    for (int i = 0; i < 201; i++)
    {
        for (int j = 0; j < 301; j++)
        {
            map[i][j] = 0;
        }
    }
}

MapLidar::~MapLidar()
{
}

void MapLidar::updateMap(Vector2i p, int d, int a)
{
    vector<int *>::iterator it;
    /*for (it = v.begin(); it != v.end(); ++it)
    {
        if (map[*it[0]][*it[1]] > 0)
            map[*it[0]][*it[1]]--;
        else
        {
            v.erase(it);
        }
    }*/
    int x_detected = (d * cos_p[a] + p.getX() * 10) + 0.5; // mm
    int y_detected = (d * sin_p[a] + p.getY() * 10) + 0.5;
    x_detected = (x_detected + 5) / 10; //cm
    y_detected = (y_detected + 5) / 10;
    if (d > 300 && d < 1500)
    {
        if (x_detected < 201 && y_detected < 301 && x_detected >= 0 && y_detected >= 0)
        {
            Vector2i pos_detected(x_detected, y_detected);

            //int i = posToId(pos_detected);
            //printf("i: %d", i);
            map[x_detected][y_detected] = 5;
            int tmptab[2] = {0, 0};
            tmptab[0] = x_detected;
            tmptab[1] = y_detected;
            //v.push_back(tmptab);
        }
    }
}

int MapLidar::posToId(Vector2i p)
{
    return 200 * p.getY() + p.getX();
}
