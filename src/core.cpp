#include "core.h"
#include <tgmath.h>

GameData::GameData()
{
    this->points = 0;
}

void GameData::AddPoints(int newPoints)
{
    this->points += newPoints;
}

int GameData::GetPoints()
{
    return this->points;
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

Vector2* Vector2::Invert()
{
    return new Vector2(-x, -y);
}

