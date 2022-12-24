#include "beatmapPlayer.h"

void DragMouseTo(const Point& target, float duration) {
	POINT current;
	GetCursorPos(&current);
	const int totalX = target.x - current.x;
	const int totalY = target.y - current.y;
	float elapsedTime = 0;
	clock_t currentTime = clock();

	float percentageToMove;

	float dt, dx, dy;

	while (elapsedTime < duration) {
		dt = (float)clock() - currentTime;
		if (dt == 0) continue;
		elapsedTime += dt;

		percentageToMove = min(elapsedTime / duration, 1);
		dx = totalX * percentageToMove;
		dy = totalY * percentageToMove;

		SetCursorPos(current.x + dx, current.y + dy);
		currentTime = (float)clock();
	}
}

void Spin(const Point& origin, int duration) {
	float elapsedTime = 0;
	clock_t currentTime = clock();
	float i = 0; // for sin, cos

	float dt, dx, dy;

	while (elapsedTime < duration) {
		dt = (float)clock() - currentTime;
		if (dt == 0) continue;
		elapsedTime += dt;

		dx = sin(i) * Spinner::spinRadius;
		dy = cos(i) * Spinner::spinRadius;

		SetCursorPos(origin.x + dx, origin.y + dy);
		currentTime = (float)clock();

		i += Spinner::spinStep;
	}
}