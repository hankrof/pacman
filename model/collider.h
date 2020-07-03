#ifndef M_COLLIDER_H
#define M_COLLIDER_H
#include "character.h"
#include "gamemap.h"
class CPacCollider
{
public:
    CPacCollider(CPacMap *map = nullptr);
    void setMap(CPacMap *map);
    /*
     * parameters:
     *      c: Determined character
     *      futurePos: A future position
     * return nullptr means no collision.
    */
    MapUnit* collide(int blockSize,QPoint futurePos) const;
private:
    CPacMap *map;
};
#endif // COLLIDER_H

