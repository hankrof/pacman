#ifndef GAMEMAP
#define GAMEMAP
#include <QString>
#include <QFile>
#include <QTextStream>
typedef unsigned int MapInteger;
typedef enum
{
    MU_NONE         = 0,
    MU_PATH         = 1,
    MU_BLOCK        = 2,
    MU_WALL         = 4,
    MU_GHOST_DOOR   = 8,
    MU_Player       = 16,
    MU_Computer     = 32,
    MU_SCORE_DOT    = 64,
    MU_ENHANCED_DOT = 128
}MapUnit;
/*
 * 0 = Path
 * 1 = Block
 * 2 = Path + Dot
 * 3 = Ghost Door
 *
 *
*/
class CPacMap
{
public:
    CPacMap(int rows = 0,int columns = 0);
    ~CPacMap();
    int rows() const;
    int cols() const;
    const MapInteger* operator[](int row) const;
    MapInteger& at(const QPoint &p);
    MapInteger& at(int row,int col);
    bool        eatDot(const QPoint &p);
    MapInteger* operator[](int row);
    bool open(QString filename);
    bool allocate(int rows,int columns);
    void free();
private:
    MapInteger **m_map;
    int m_rows,m_cols;
};
#endif // GAMEMAP
