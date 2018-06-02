#include "tracklblcell.h"

#include <qmath.h>
#include <QTime>

TrackLblCell::TrackLblCell(float x0, float y0, float sz):
    m_x(x0), m_y(y0), m_sz(sz), m_selected(false)
{
    m_rect.setTopLeft(QPointF(x0, y0));
    m_rect.setBottomRight(QPointF(x0+m_sz, y0+m_sz));

    int r = (qrand() % 256);
    int g = (qrand() % 256);
    int b = (qrand() % 256);

    m_main_col = QColor(r, g, b/*Qt::blue*/);
}

bool TrackLblCell::isInside(QPointF pt)
{
    return m_rect.contains(pt);
}
