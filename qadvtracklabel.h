#ifndef QTRACKLABEL_H
#define QTRACKLABEL_H

/// Advanced track label

/// Для определения области нажатия мыши, используем
/// нормализованные координаты: width, height -> 1

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>

#include "tracklblcell.h"

class QAdvTrackLabel : public QLabel
{
    Q_OBJECT

public:
    QAdvTrackLabel(QWidget *parent = 0);
    ~QAdvTrackLabel();

    int heightForWidth(int w) const;

    TrackLblCell *getSelectedCell();

    void updateArray(int w, int h);

    void setGradientPoint(int num, QPoint pt);
    bool fillGradient();

private:
    void createCellArray();
    void deleteCellArray();

    void createGrid();

    void calculateCursorSize();

    TrackLblCell *findCell(QPoint pt_idx);



private:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *ev);
    void paintEvent(QPaintEvent *ev);

public:
    inline void setGridVisible(bool value) {m_isGridVisible = value;}

private:
    QPainter m_pntr;

    QPixmap *m_bkgnd;
    QImage *m_grid_img;

    QSize cursor_sz;

    QVector<TrackLblCell *> m_cells;

    bool m_isGridVisible;
    int m_grid_x, m_grid_y;   /// число элементов в сетке

    QPair<QPoint, QPoint> pts_grad; /// точки градиента

    TrackLblCell *cell_grd1, *cell_grd2; /// ячейки для градиента


signals:
    void changeMousePos(QPoint pos);
    void mouseClick(Qt::MouseButtons buttons, QPoint pos);
    void cellClick(TrackLblCell* cell);

    //void mouseClickFragment();
};

#endif // QTRACKLABEL_H
