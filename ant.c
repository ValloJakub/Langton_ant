#include "world.h"
#include "ant.h"

#include <pthread.h>
#include <unistd.h>

void *antThread(void *arg) {
    Ant *ant = (Ant *)arg;
    World *world = ant[0].world;

    pthread_mutex_lock(ant->mutex);
    while (world->stepLimit > 0) {
        world->stepLimit--;

        pthread_mutex_unlock(ant->mutex);
        if (ant->isDeleted == 1) {
            return NULL;
        }
        usleep(100000);

        moveAnt(ant, ant->world);

        pthread_mutex_lock(ant->mutex);

        displayWorld(world);
    }
    pthread_mutex_unlock(ant->mutex);

    return NULL;
}
