#include "maingui.h"

#include <qlayout.h>
#include <QSizePolicy>


MainGUI::MainGUI(QWidget *parent) : QWidget(parent), output_img(NULL)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    createGuiWindow();

    cellColor_lbl->setObjectName("cellColorLbl");

    /// ------------- Настройка стилей ---------------
    QFile file(":/guistyle.css");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    this->setStyleSheet(strCSS);
    /// ----------------------------------------------

    sel_cell = NULL;
}

MainGUI::~MainGUI()
{

}

void MainGUI::createGuiWindow()
{
    //QPixmap bkgnd(512,512);
   // bkgnd.fill(QColor(Qt::blue));

    render_lbl = new QAdvTrackLabel(this);
    //render_lbl->setScaledContents(true);
    render_lbl->resize(256, 256);
    render_lbl->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    //render_lbl->setFixedSize(512,512);
    //render_lbl->setPixmap(bkgnd);

    /*QPixmap *pxm = (QPixmap *)render_lbl->pixmap();

    QPainter pntr;
    pntr.begin(pxm);
    pntr.setPen(QColor(Qt::white));
    //pntr.drawImage(0,0, *m_grid_img);
    pntr.drawLine(0,0, 20, 20);
    pntr.end();*/


    /// --------------- Задать размеры изображения --------------
    QGroupBox *size_grp = new QGroupBox("Размеры");
    size_grp->setMaximumWidth(130);

    QVBoxLayout *size_grp_layer = new QVBoxLayout();

    cellSz_ed = new QLineEdit();
    cellSz_ed->setText(QString::number(8));

    cellNumX_ed = new QLineEdit();
    cellNumX_ed->setText(QString::number(16));
    cellNumY_ed = new QLineEdit();
    cellNumY_ed->setText(QString::number(16));

    update_bn = new QPushButton("Обновить");

    gridOn_chb = new QCheckBox("Показать сетку");
    gridOn_chb->setChecked(true);

    size_grp_layer->addWidget(new QLabel("Размер ячейки, пикс:"));
    size_grp_layer->addWidget(cellSz_ed);
    size_grp_layer->addWidget(new QLabel("Ячеек по Х:"));
    size_grp_layer->addWidget(cellNumX_ed);
    size_grp_layer->addWidget(new QLabel("Ячеек по Y:"));
    size_grp_layer->addWidget(cellNumY_ed);

    size_grp_layer->addWidget(update_bn);
    size_grp_layer->addWidget(gridOn_chb);
    size_grp_layer->addStretch(1);

    size_grp->setLayout(size_grp_layer);

    /// --------------- По ячейке --------------
    QGroupBox *cell_grp = new QGroupBox("Данные ячейки");
    cell_grp->setMaximumWidth(200);

    QLabel *lbl1 = new QLabel("Цвет:");
    lbl1->setAlignment(Qt::AlignTop);

    cellColor_lbl = new QLabel("#000000");
    cellColor_lbl->setFixedHeight(22);
    cellColor_lbl->setAlignment(Qt::AlignTop);

    selColor_bn = new QPushButton("Выбрать цвет...");

    QVBoxLayout *cell_grp_layer = new QVBoxLayout();
    cell_grp_layer->addWidget(lbl1);
    cell_grp_layer->addWidget(cellColor_lbl);
    cell_grp_layer->addWidget(selColor_bn);
    cell_grp_layer->addStretch(1);

    cell_grp->setLayout(cell_grp_layer);
    /// --------------------------------------------

    /// ---------------- Градиент -----------------------
    selGradPt1_bn = new QPushButton("Точка №1");
    selGradPt2_bn = new QPushButton("Точка №2");
    clearGradPts_bn = new QPushButton("Очистить точки");
    makeGrad_bn = new QPushButton("Создать градиент");

    QVBoxLayout *grad_grp_layer = new QVBoxLayout();
    grad_grp_layer->addWidget(selGradPt1_bn);
    grad_grp_layer->addWidget(selGradPt2_bn);
    grad_grp_layer->addWidget(clearGradPts_bn);
    grad_grp_layer->addWidget(makeGrad_bn);

    QGroupBox *grad_grp = new QGroupBox("Градиент");

    grad_grp->setLayout(grad_grp_layer);
    /// -------------------------------------------------

    /// ------------ Кнопка Сохранить -----------------
    QPushButton *bnSave = new QPushButton("Сохранить");




    QVBoxLayout *ctrl_layer = new QVBoxLayout(); /// слой для всей управлялки
    ctrl_layer->addWidget(size_grp);
    ctrl_layer->addWidget(cell_grp);
    ctrl_layer->addWidget(grad_grp);
    ctrl_layer->addWidget(bnSave);
    ctrl_layer->setSizeConstraint(QLayout::SetMinimumSize);

    QHBoxLayout *h_layer = new QHBoxLayout();
    h_layer->addWidget(render_lbl);
    h_layer->addLayout(ctrl_layer);

    sbar = new QStatusBar();

    /// ---- самый верхний слой ----
    QVBoxLayout *top_layer = new QVBoxLayout(); /// слой для всей управлялки
    top_layer->addLayout(h_layer);
    top_layer->addWidget(sbar);

    this->setLayout(top_layer);

    sbar->showMessage("Приветствую, мастер!", 2000);

    connect(gridOn_chb, SIGNAL(clicked(bool)), this, SLOT(onCBVisibleClicked(bool)));
    connect(selColor_bn, SIGNAL(clicked(bool)), this, SLOT(selectCellColor()));
    connect(render_lbl, SIGNAL(cellClick(TrackLblCell*)), this, SLOT(onCellClickEvent(TrackLblCell*)));
    connect(update_bn, SIGNAL(pressed()), this, SLOT(onBnUpdateClicked()));
    connect(selGradPt1_bn, SIGNAL(pressed()), this, SLOT(onSelGradPt1btn()));
    connect(selGradPt2_bn, SIGNAL(pressed()), this, SLOT(onSelGradPt2btn()));
    connect(makeGrad_bn, SIGNAL(pressed()), this, SLOT(onGradBnClicked()));
    connect(bnSave, SIGNAL(clicked(bool)), this, SLOT(onSaveBnClicked()));
}

void MainGUI::onBnUpdateClicked()
{
    int nx = cellNumX_ed->text().toInt();
    int ny = cellNumY_ed->text().toInt();
    render_lbl->updateArray(nx, ny);
}

void MainGUI::onCBVisibleClicked(bool checked)
{
    render_lbl->setGridVisible(checked);
}

void MainGUI::selectCellColor()
{
    QColorDialog dlg;
    QColor col = dlg.getColor();
    TrackLblCell *cell = render_lbl->getSelectedCell();
    if (cell) {
        cell->setColor(col);
        cellColor_lbl->setText(col.name());
    }
}

void MainGUI::onCellClickEvent(TrackLblCell* cell)
{
    cellColor_lbl->setText(cell->color().name());
    sel_cell = cell;
}

void MainGUI::onSelGradPt1btn()
{
    int x,y;
    sel_cell->indices(x,y);
    QPoint pt(x,y);
    render_lbl->setGradientPoint(1, pt);
}

void MainGUI::onSelGradPt2btn()
{
    int x,y;
    sel_cell->indices(x,y);
    QPoint pt(x,y);
    render_lbl->setGradientPoint(2, pt);
}

void MainGUI::onGradBnClicked()
{
    QString str;
    if (render_lbl->fillGradient())
        str = QString("Градиент построен!");
    else
        str = QString("Не удалось построить градиент!");
    sbar->showMessage(str, 2000);
}

void MainGUI::onSaveBnClicked()
{
    QFileDialog dlg;

}
