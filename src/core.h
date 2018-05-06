#ifndef Core_H
#define Core_H

class GameData {
    int points;
public:
    GameData();
    void AddPoints(int newPoints);
    int GetPoints();
};

class Vector2 {
    public:
        float x, y;
        Vector2(int x, int y) {
            this->x = x;
            this->y = y;
        }

        float Length();
        Vector2* Normalize();
        Vector2* Invert();
};

#endif