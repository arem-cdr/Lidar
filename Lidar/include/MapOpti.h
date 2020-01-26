#pragma once

class MapOpti
{
public:
    MapOpti(int taille)
    {
        map = new char[taille / 8]; // multiple de 8
    }
    ~MapOpti()
    {
        delete[] map;
    }
    void setMap(int i, bool b)
    {
        int id = i / 8;
        int r = i % 8;
        if (b)
        {
            map[id] = map[id] | create_char_for_map(r, b);
            printf(" if %d\n", map[id]);
        }
        else
        {
            //map[id] = map[id] & create_char_for_map(r, b);
            //printf("else %d\n", map[id]);
        }
    }
    bool getMap(int i)
    {
        int id = i / 8;
        int r = i % 8;
        char c = create_char_for_map(r, true);
        //printf("map : %d & %d\n", map[id], c);
        if ((map[id] & c) > 0)
            return true;
        else
            return false;
    }

private:
    char *map;

    char create_char_for_map(int r, bool b)
    {
        char c = 0;
        switch (r)
        {
        case 0:
            if (b)
                c = 0b00000001;
            else
                c = 0b11111110;
            break;
        case 1:
            if (b)
                c = 0b00000010;
            else
                c = 0b11111101;
            break;
        case 2:
            if (b)
                c = 0b00000100;
            else
                c = 0b11111011;
            break;
        case 3:
            if (b)
                c = 0b00001000;
            else
                c = 0b11110111;
            break;
        case 4:
            if (b)
                c = 0b00010000;
            else
                c = 0b11101111;
            break;
        case 5:
            if (b)
                c = 0b00100000;
            else
                c = 0b11011111;
            break;
        case 6:
            if (b)
                c = 0b01000000;
            else
                c = 0b10111111;
            break;
        case 7:
            if (b)
                c = 0b10000000;
            else
                c = 0b11111111;
            break;

        default:
            if (b)
                c = 0b00000000;
            else
                c = 0b11111111;
            break;
        }
        return c;
    }
};