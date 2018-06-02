#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets>
#include <QSizePolicy>
#include "qadvtracklabel.h"


class MainGUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainGUI(QWidget *parent = 0);
    ~MainGUI();

private:

    void createGuiWindow();

private:
    /// ------------ GUI --------------
    QAdvTrackLabel *render_lbl;   /// основной виджет-экран
    QLabel *cellColor_lbl;      /// строка цвета
    QPushButton *selColor_bn;  /// выбрать цвет
    QPushButton *selGradPt1_bn;   /// установить точку град-та №1
    QPushButton *selGradPt2_bn;   /// установить точку град-та №2
    QPushButton *clearGradPts_bn; /// Очистить точки град-та
    QPushButton *makeGrad_bn;     /// Создать град-т м/у точками

    QLineEdit *cellSz_ed;      /// размер ячейки
    QLineEdit *cellNumX_ed;    /// кол-во ячеек по Х
    QLineEdit *cellNumY_ed;    /// кол-во ячеек по У
    QPushButton *update_bn;    /// обновить размеры
    QCheckBox *gridOn_chb;     /// показать сетку

    QStatusBar *sbar;       /// статус бар

    QImage *output_img;

private:
    QPoint m_pt1Idx, m_pt2Idx;
    TrackLblCell *sel_cell; /// выбранная ячейка

public slots:
    void onBnUpdateClicked();
    void onCBVisibleClicked(bool checked);
    void selectCellColor();
    void onCellClickEvent(TrackLblCell *cell);

    void onSelGradPt1btn();
    void onSelGradPt2btn();
    void onGradBnClicked();

    void onSaveBnClicked();
};

#endif // MAINGUI_H
