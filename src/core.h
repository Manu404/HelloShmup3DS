#ifndef Core_H
#define Core_H

class GameData {
    int points;
    int life;
public:
    GameData();
    void Reset();
    void AddPoints(int newPoints);
    int GetPoints();
    void SetLife(int life);
    int GetLife();
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
};

#endif