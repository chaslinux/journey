#ifndef JOURNEY_CAMERA_H
#define JOURNEY_CAMERA_H

#include "map.h"
#include "player.h"

typedef struct
{
    float x;
    float y;
} JourneyCamera;

void journey_camera_init(
    JourneyCamera *camera,
    const JourneyPlayer *player
);

void journey_camera_follow(
    JourneyCamera *camera,
    const JourneyPlayer *player,
    const JourneyMap *map
);

#endif

