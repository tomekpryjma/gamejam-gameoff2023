#pragma once

typedef struct Vector2 {
	float x, y;
} Vector2;

Vector2 Vector2_Create(float x, float y);
float Vector2_Magnitude(const Vector2* vector);
float Vector2_MagnitudeF(float x1, float y1, float x2, float y2);
Vector2 Vector2_Normalize(const Vector2* vector);
Vector2 Vector2_GetDistances(const Vector2* vectorA, const Vector2* vectorB);