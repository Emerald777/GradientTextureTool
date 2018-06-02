#ifndef TRACKLBLCELL_H
#define TRACKLBLCELL_H

#include <QColor>
#include <QRect>

class TrackLblCell
{

public:
    TrackLblCell(float x0, float y0, float sz);

    inline void setColor(QColor col) {m_main_col = col;}
    inline QColor color() {return m_main_col;}

    inline void setSelected(bool value) {m_selected = value;}
    inline bool selected() {return m_selected;}

    inline float getX0() {return m_rect.left();}
    inline float getY0() {return m_rect.top();}

    inline QPointF getCenter() {return m_rect.center();}

    inline float width() {return m_rect.width();}
    inline float height() {return m_rect.height();}

    bool isInside(QPointF pt);

    inline void setIndices(int iX, int iY) {idx_x = iX; idx_y = iY;}

    inline void indices(int &iX, int &iY) { iX = idx_x; iY = idx_y;}
    inline void indices(QPoint &i_pt) { i_pt = QPoint(idx_x, idx_y);}

private:
    QColor m_main_col;

    float m_x, m_y; /// координаты верхнего левого угла
    float m_sz;     /// размер (для квадратной ячейки)

    bool m_selected;

    QRectF m_rect;

    int idx_x, idx_y;  /// индексы в целых числах
};

#endif // TRACKLBLCELL_H
