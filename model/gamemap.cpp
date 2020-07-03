#include "gamemap.h"
#include <QDebug>
#include <QPoint>

CPacMap::CPacMap(int rows,int cols)
{
    this->m_rows = rows;
    this->m_cols = cols;
    this->m_map  = nullptr;
    allocate(rows,cols);
}

CPacMap::~CPacMap()
{
    free();
}

int CPacMap::rows() const
{
    return m_rows;
}

int CPacMap::cols() const
{
    return m_cols;
}

const MapInteger* CPacMap::operator[](int row) const
{
    return *(m_map + row);
}

MapInteger& CPacMap::at(const QPoint &p)
{
    return m_map[p.x()][p.y()];
}

MapInteger& CPacMap::at(int row,int col)
{
    return m_map[row][col];
}

bool CPacMap::eatDot(const QPoint &p)
{
    MapInteger& integer = m_map[p.x()][p.y()];
    if((integer & MU_SCORE_DOT) == MU_SCORE_DOT)
    {
        m_map[p.x()][p.y()] = MU_PATH;
        return true;
    }
    return false;
}

MapInteger* CPacMap::operator[](int row)
{
    return *(m_map + row);
}

bool CPacMap::open(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    qint32 r,c,n;
    in >> r;
    in >> c;
    allocate(r,c);
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            in >> n;
            if(n == 0)
                m_map[j][i] = MU_PATH;
            else if (n == 1)
                m_map[j][i] = MU_BLOCK;
            else if(n == 2)
                m_map[j][i] = MU_PATH | MU_SCORE_DOT;
            else if(n == 3)
                m_map[j][i] = MU_BLOCK | MU_GHOST_DOOR;
        }
    }
    return true;
}

bool CPacMap::allocate(int rows,int columns)
{
    if(m_map)
        free();
    if(rows <= 0 || columns <= 0) //bad allocation
        return false;
    m_rows = rows;
    m_cols = columns;
    m_map = new MapInteger*[m_rows]();
    for(int i=0;i<m_cols;i++)
    {
        m_map[i] = new MapInteger[m_cols]();
        for(int j=0;j<m_cols;j++)
            m_map[i][j] = MU_PATH;
    }
    return true;
}

void CPacMap::free()
{
    if(!m_map)
        return;
    for(int i=0;i<m_cols;i++)
        delete[] m_map[i];
    delete[] m_map;
    m_map = nullptr;
}

