#include "vector2.h"
#include <math.h>

Vector2 Vector2_Create(float x, float y) {
	return (Vector2) { x, y };
}

float Vector2_Magnitude(const Vector2* vector) {
	return sqrtf((vector->x * vector->x) + (vector->y * vector->y));
}

Vector2 Vector2_Normalize(const Vector2* vector) {
	Vector2 result;
	float magnitude = Vector2_Magnitude(vector);
	if (magnitude == 0) {
		result.x = 0;
		result.y = 0;
		return result;
	}
	result.x = vector->x / magnitude;
	result.y = vector->y / magnitude;
	return result;
}

Vector2 Vector2_GetDistances(const Vector2* vectorA, const Vector2* vectorB) {
	Vector2 diffVector = { vectorB->x - vectorA->x, vectorB->y - vectorA->y };
	return diffVector;
}