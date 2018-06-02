#include "qadvtracklabel.h"

/*#include <QThread>
#include <QCoreApplication>*/
#include <qmath.h>
//#include <QDebug>

QAdvTrackLabel::QAdvTrackLabel(QWidget *parent) : QLabel(parent),
    m_isGridVisible(true), m_grid_x(8), m_grid_y(8)
{
    setMouseTracking(true);

    m_bkgnd = new QPixmap(this->size());
    m_bkgnd->fill(QColor(Qt::blue));
    setPixmap(*m_bkgnd);

    m_grid_img = new QImage(this->size(), QImage::Format_ARGB32);
    m_grid_img->fill(Qt::red);

    createCellArray();
}

QAdvTrackLabel::~QAdvTrackLabel()
{
    delete m_grid_img;
    deleteCellArray();
}

int QAdvTrackLabel::heightForWidth(int w) const
{
    return w;
}

TrackLblCell *QAdvTrackLabel::getSelectedCell()
{
    foreach (TrackLblCell *cell, m_cells) {

        if ( cell->selected() )
            return cell;
    }

    return NULL;
}

void QAdvTrackLabel::updateArray(int w, int h)
{
    deleteCellArray();
    m_grid_x = w;
    m_grid_y = h;

    createCellArray();
}

void QAdvTrackLabel::setGradientPoint(int num, QPoint pt)
{
    if (num == 1)
        pts_grad.first = pt;
    else if (num == 2)
        pts_grad.second = pt;

}

bool QAdvTrackLabel::fillGradient()
{
    QPoint pt1, pt2;
    cell_grd1->indices(pt1);
    cell_grd2->indices(pt2);

    QColor col1 = cell_grd1->color();
    QColor col2 = cell_grd2->color();

    bool res = true;

    QPoint dpt = pt2 - pt1; /// разница в индексах
    if ((dpt.x()!=0) && (dpt.y()!=0))
        res = false;

    else if ( (dpt.x()<0) || (dpt.y()<0) )
        res = false;

    else {

        QColor curCol = col1;
        int numSteps;
        int j=1;
        if (dpt.x())
        {
            numSteps = abs(dpt.x());
            int dR = (col2.red() - col1.red())/numSteps;
            int dG = (col2.green() - col1.green())/numSteps;
            int dB = (col2.blue() - col1.blue())/numSteps;

            for (int i=pt1.x()+1; i<pt2.x(); i++) {

                curCol = QColor(col1.red()+dR*j,
                                col1.green()+dG*j,
                                col1.blue()+dB*j
                                );

                QPoint new_idx(i, pt1.y());
                TrackLblCell *cell = findCell(new_idx);
                cell->setColor(curCol);
                j++;
               /* QThread::msleep(200);
                QCoreApplication::processEvents();*/
            }
        }
        else
        {
            numSteps = abs(dpt.y());
            int dR = (col2.red() - col1.red())/numSteps;
            int dG = (col2.green() - col1.green())/numSteps;
            int dB = (col2.blue() - col1.blue())/numSteps;

            for (int i=pt1.y()+1; i<pt2.y(); i++) {

                curCol = QColor(col1.red()+dR*j,
                                col1.green()+dG*j,
                                col1.blue()+dB*j
                                );

                QPoint new_idx(pt1.x(), i);
                TrackLblCell *cell = findCell(new_idx);
                cell->setColor(curCol);
                j++;
               /* QThread::msleep(200);
                QCoreApplication::processEvents();*/
            }
        }
    }

    return res;
}

void QAdvTrackLabel::createCellArray()
{
    for(int i=0; i<m_grid_y; i++) {

        for (int j=0; j<m_grid_x; j++) {

            TrackLblCell *cell = new TrackLblCell (
                (float)j/(float)m_grid_x, (float)i/(float)m_grid_y,  1.0f/m_grid_x
            );
            cell->setIndices(j,i);

            m_cells.append(cell);
        }
    }
    return;
}

void QAdvTrackLabel::deleteCellArray()
{
    foreach(TrackLblCell *cell, m_cells) {
        delete cell;
    }
    m_cells.clear();
}

void QAdvTrackLabel::createGrid()
{
    int wdt = this->width();
    int hgt = this->height();

    delete m_grid_img;
    m_grid_img = new QImage(wdt, hgt, QImage::Format_ARGB32);
   // m_grid_img->fill(Qt::yellow);

    float dx = (float)wdt/(float)m_grid_x;
    float dy = (float)hgt/(float)m_grid_y;

    m_pntr.begin(m_grid_img);
    for (float i=0; i<wdt; i+=dx) {
        m_pntr.setPen(QColor(Qt::white));
        m_pntr.drawLine(QPointF(i, 0), QPointF(i, hgt));
    }

    for (float i=0; i<hgt; i+=dy) {
        m_pntr.setPen(QColor(Qt::white));
        m_pntr.drawLine(QPointF(0, i), QPointF(wdt, i));
    }
    m_pntr.end();
}

void QAdvTrackLabel::calculateCursorSize()
{
    cursor_sz.setWidth(this->width()/m_grid_x);
    cursor_sz.setHeight(this->height()/m_grid_y);
}

TrackLblCell *QAdvTrackLabel::findCell(QPoint pt_idx)
{
    foreach (TrackLblCell *cell, m_cells)
    {
        QPoint pt;
        cell->indices(pt);
        if ( pt == pt_idx )
            return cell;

    }
    return NULL;
}

void QAdvTrackLabel::mouseMoveEvent(QMouseEvent *ev)
{
    emit changeMousePos(ev->pos());
}

void QAdvTrackLabel::mousePressEvent(QMouseEvent *ev)
{
    QPointF pt = QPointF(ev->pos());
    pt /= (float)width();

    foreach (TrackLblCell *cell, m_cells) {

        cell->setSelected(false);
    }

    foreach (TrackLblCell *cell, m_cells) {

        if ( cell->isInside(pt) )
        {
            cell->setSelected(true);
            emit cellClick(cell);
            break;
        }
    }

    emit mouseClick(ev->buttons(), ev->pos());
}

void QAdvTrackLabel::resizeEvent(QResizeEvent *ev)
{
    int sz = qMin(ev->size().width(), ev->size().height());
    this->resize(sz, sz);

    delete m_bkgnd;
    m_bkgnd = new QPixmap(this->size());
    m_bkgnd->fill(QColor(Qt::blue));
    setPixmap(*m_bkgnd);

    QLabel::resizeEvent(ev);
}

void QAdvTrackLabel::paintEvent(QPaintEvent *ev)
{
    setPixmap(*m_bkgnd);

    int wdt = width();

    QPixmap *pxm = (QPixmap *)this->pixmap();

    /// рисуем сами ячейки
    m_pntr.begin(pxm);
    foreach (TrackLblCell *cell, m_cells) {

        QPoint cur_idx_pt;
        cell->indices(cur_idx_pt);

        if (cur_idx_pt == pts_grad.first) {
            cell_grd1 = cell;
        }

        if (cur_idx_pt == pts_grad.second) {
            cell_grd2 = cell;
        }

        m_pntr.setPen( QPen(QBrush(cell->color()), 1));
        m_pntr.setBrush(QBrush(cell->color()));
        m_pntr.drawRect( cell->getX0()*wdt, cell->getY0()*wdt,
                        cell->width()*wdt, cell->height()*wdt );
    }
    m_pntr.end();

    /// рисуем сетку
    if (m_isGridVisible)
    {
        createGrid();
        m_pntr.begin(pxm);
        m_pntr.drawImage(0,0, *m_grid_img);
        m_pntr.end();
    }

    m_pntr.begin(pxm);
    foreach (TrackLblCell *cell, m_cells) {

        /// рисуем рамку ежели выделено
        if ( cell->selected() )
        {
            m_pntr.setPen( QPen(QBrush(Qt::red), 3));
            m_pntr.drawRect( cell->getX0()*wdt, cell->getY0()*wdt,
                            cell->width()*wdt, cell->height()*wdt );
            break;
        }
    }
    m_pntr.end();

    /// рисуем значочки градиента
    m_pntr.begin(pxm);
    m_pntr.setBrush(QBrush(Qt::black));
    m_pntr.setPen(QColor(Qt::white));
    m_pntr.drawEllipse(QPointF(cell_grd1->getCenter()*wdt), cell_grd1->width()*wdt/4, cell_grd1->height()*wdt/4);
    //m_pntr.setMatrix( );
    m_pntr.setFont(QFont("Arial", 10, 6));
    m_pntr.drawText(QPointF(cell_grd1->getX0()*wdt, cell_grd1->getY0()*wdt), QString("1"));
   /* m_pntr.drawRect( cell_grd1->getX0()*wdt, cell_grd1->getY0()*wdt,
                    cell_grd1->width()*wdt/4, cell_grd1->height()*wdt/4 );*/

    m_pntr.setBrush(QBrush(Qt::white));
    m_pntr.drawRect( cell_grd2->getX0()*wdt, cell_grd2->getY0()*wdt,
                    cell_grd2->width()*wdt/4, cell_grd2->height()*wdt/4 );
    m_pntr.end();

    QLabel::paintEvent(ev);
}

