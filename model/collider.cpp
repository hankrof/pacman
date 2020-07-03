#include "collider.h"
CPacCollider::CPacCollider(CPacMap *map)
{
    this->map = map;
}

void CPacCollider::setMap(CPacMap *map)
{
    this->map = map;
}

MapUnit* CPacCollider::collide(int blockSize,QPoint futureOffset) const
{
    static MapUnit unit;
    int x = futureOffset.x();
    int y = futureOffset.y();
    int rows = map->rows();
    int cols = map->cols();
    QRect rect = QRect(x,y,blockSize,blockSize);
    QRect cmpRect;


    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if((map->at(i,j) & MU_BLOCK) == MU_BLOCK)
            {
                cmpRect = QRect(i*blockSize,j*blockSize,
                                blockSize,blockSize);
                if(rect.bottom() <= cmpRect.top() )
                    continue;
                if(rect.top() >= cmpRect.bottom())
                    continue;
                if(rect.right() <= cmpRect.left())
                    continue;
                if(rect.left() >= cmpRect.right())
                    continue;
                unit = MU_BLOCK;
                return &unit;
            }
        }
    }
    return nullptr;
}
