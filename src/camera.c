#include <stddef.h>

#include "camera.h"

#define JOURNEY_TILE_WIDTH  10.0f
#define JOURNEY_TILE_HEIGHT 10.0f

#define JOURNEY_VIEW_WIDTH  320.0f
#define JOURNEY_VIEW_HEIGHT 180.0f

void journey_camera_init(
    JourneyCamera *camera,
    const JourneyPlayer *player
)
{
    if (camera == NULL || player == NULL)
    {
        return;
    }

    /*
     * Center the camera on the player's tile.
     */
    camera->x =
        (float)player->x * JOURNEY_TILE_WIDTH +
        JOURNEY_TILE_WIDTH / 2.0f -
        JOURNEY_VIEW_WIDTH / 2.0f;

    camera->y =
        (float)player->y * JOURNEY_TILE_HEIGHT +
        JOURNEY_TILE_HEIGHT / 2.0f -
        JOURNEY_VIEW_HEIGHT / 2.0f;

    if (camera->x < 0.0f)
    {
        camera->x = 0.0f;
    }

    if (camera->y < 0.0f)
    {
        camera->y = 0.0f;
    }
}

void journey_camera_follow(
    JourneyCamera *camera,
    const JourneyPlayer *player,
    int map_width,
    int map_height
)
{
    if (camera == NULL ||
        player == NULL ||
        map_width <= 0 ||
        map_height <= 0)
    {
        return;
    }

    /*
     * Center the camera on the player.
     */
    camera->x =
        (float)player->x * JOURNEY_TILE_WIDTH +
        JOURNEY_TILE_WIDTH / 2.0f -
        JOURNEY_VIEW_WIDTH / 2.0f;

    camera->y =
        (float)player->y * JOURNEY_TILE_HEIGHT +
        JOURNEY_TILE_HEIGHT / 2.0f -
        JOURNEY_VIEW_HEIGHT / 2.0f;

    /*
     * Calculate the size of the current world
     * in logical pixels.
     */
    const float map_pixel_width =
        (float)map_width * JOURNEY_TILE_WIDTH;

    const float map_pixel_height =
        (float)map_height * JOURNEY_TILE_HEIGHT;

    /*
     * Keep the camera inside the current world.
     */
    const float max_camera_x =
        map_pixel_width - JOURNEY_VIEW_WIDTH;

    const float max_camera_y =
        map_pixel_height - JOURNEY_VIEW_HEIGHT;

    if (camera->x < 0.0f)
    {
        camera->x = 0.0f;
    }

    if (camera->y < 0.0f)
    {
        camera->y = 0.0f;
    }

    if (camera->x > max_camera_x)
    {
        camera->x = max_camera_x > 0.0f
            ? max_camera_x
            : 0.0f;
    }

    if (camera->y > max_camera_y)
    {
        camera->y = max_camera_y > 0.0f
            ? max_camera_y
            : 0.0f;
    }
}

