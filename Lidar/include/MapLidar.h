#pragma once

#include "Vector2i.h"
#include "math.h"
#include "MapOpti.h"
#include "mbed.h"
#include <vector>

#define RESOLUTION_MAP 200 * 300

class MapLidar
{
public:
    MapLidar();
    ~MapLidar();

    void updateMap(Vector2i p, int d, int a);

    int posToId(Vector2i p);
    void affiche_map_lidar(Serial &pc)
    {
        pc.printf("S");
        for (int i = 0; i < 201; i++)
        {
            for (int j = 0; j < 301; j++)
            {
                if (map[i][j])
                    pc.printf("O");
                else
                    pc.printf("X");
            }
        }
    }

private:
    //MapOpti *map;
    char map[201][301];
    float cos_p[360];
    float sin_p[360];
    vector<int *> v;
};
