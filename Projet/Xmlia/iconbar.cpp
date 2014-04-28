#include "iconbar.h"

IconBar::IconBar(QWidget *parent) :
    QWidget(parent)
{
    this->layout = new QHBoxLayout();
    this->layout->setMargin(0);
    this->layout->setSpacing(5);
    this->layout->setAlignment(Qt::AlignLeft);

    this->open = createButton("document-open");
    this->open->setToolTip("Open");
    this->layout->addWidget(open);

    this->save = createButton("document-save");
    this->save->setToolTip("Save");
    this->layout->addWidget(save);

    this->saveAs = createButton("document-save-as");
    this->saveAs->setToolTip("Save as");
    this->layout->addWidget(saveAs);

    this->indent = createButton("format-indent-more");
    this->indent->setToolTip("Indent");
    this->layout->addWidget(indent);

    this->build = createButton("emblem-default");
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

void IconBar::connectSaveAs(QObject * o)
{
    connect(saveAs, SIGNAL(clicked()), o, SLOT(saveXmlAs()));
}

void IconBar::connectIndent(QObject *o)
{
    connect(indent, SIGNAL(clicked()), o, SLOT(indent()));
}

void IconBar::connectBuild(QObject *o, QObject *o1)
{
    connect(build, SIGNAL(clicked()), o, SLOT(validateAndRefreshTree()));
    connect(build, SIGNAL(clicked()), o1, SLOT(save()));
}

QPushButton *IconBar::createButton(QString name) const
{
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon::fromTheme(name, QIcon("../assets/"+name)));
    button->setIconSize(QSize(25,25));
    button->setFixedSize(32, 32);
    return button;
}
