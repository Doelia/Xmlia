#include "iconbar.h"

IconBar::IconBar(QWidget *parent) :
    QWidget(parent)
{
    this->layout = new QHBoxLayout();
    this->layout->setMargin(0);
    this->layout->setSpacing(5);
    this->layout->setAlignment(Qt::AlignLeft);

    this->open = createButton("../assets/open.png");
    this->open->setToolTip("Open");
    this->layout->addWidget(open);

    this->save = createButton("../assets/save.png");
    this->save->setToolTip("Save");
    this->layout->addWidget(save);

    this->indent = createButton("../assets/indent.png");
    this->indent->setToolTip("Indent");
    this->layout->addWidget(indent);

    this->build = createButton("../assets/build.png");
    this->build->setToolTip("Build");
    this->layout->addWidget(build);

    this->setLayout(layout);
}

void IconBar::connectOpen(QObject* o)
{
    connect(open, SIGNAL(clicked()), o, SLOT(open()));
}

void IconBar::connectSave(QObject * o)
{
    connect(save, SIGNAL(clicked()), o, SLOT(save()));
}

void IconBar::connectIndent(QObject *o)
{
    connect(indent, SIGNAL(clicked()), o, SLOT(indent()));
}

void IconBar::connectBuild(QObject *o)
{
    connect(build, SIGNAL(clicked()), o, SLOT(onRefreshRequest()));
}

QPushButton *IconBar::createButton(QString path) const
{
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(path));
    button->setIconSize(QSize(32,32));
    button->setFixedSize(32, 32);
    return button;
}
