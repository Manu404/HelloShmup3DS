#include "core.h"
#include <tgmath.h>

GameData::GameData() {
    this->Reset();
}

void GameData::AddPoints(int newPoints) {
    this->points += newPoints;
}

int GameData::GetPoints() {
    return this->points;
}

void GameData::Reset() {
    this->points = 0;
    this->life = 3;
}


int GameData::GetLife() {
    return this->life;
}

void GameData::SetLife(int life) {
    this->life = life;
}

// Returns the length of the vector
float Vector2::Length() {
    return sqrt(x * x + y * y);
}

// Normalizes the vector
Vector2* Vector2::Normalize() {
    Vector2* vector = new Vector2(0, 0);
    float length = this->Length();

    if (length != 0) {
        vector->x = x / length;
        vector->y = y / length;
    }

    return vector;
}