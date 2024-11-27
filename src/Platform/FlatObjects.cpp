#include "FlatObjects.h"

std::vector < FlatObject* > flatObjects;

bool isPathOnPosition( float x, float y) {
	// TO-DO
	for (auto& path : flatObjects) {
		if (pointInEllipse(x, y, path->position.x, path->position.y, path->colliders[0]->width/2.0f, path->colliders[0]->length / 2.0f))
			return true;
	}

	return false;
}

#endif