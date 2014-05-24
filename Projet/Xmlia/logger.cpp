/*===============================================
 * nom : logger.cpp         projet : xmlia
 *=============================================*/

#include "logger.h"

Logger::Logger()
{
    logArea = new QTextEdit();
    logArea->setFixedHeight(100);
    logArea->setReadOnly(true);
    logArea->hide();

    cursorInfo = new QTextEdit();
    cursorInfo->setFixedHeight(18);
    cursorInfo->setReadOnly(true);
    cursorInfo->setFontPointSize(8);
    cursorInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    fixedScroll = 3;

    openIcon = QIcon(QIcon::fromTheme("up"));
    closeIcon = QIcon(QIcon::fromTheme("down"));

    toggleButton = new QPushButton();
    toggleButton->setFixedSize(16, 16);
    toggleButton->setIcon(openIcon);
    toggleButton->setIconSize(QSize(10, 10));

    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    hLayout = new QHBoxLayout();
    hLayout->setSpacing(5);
    hLayout->setContentsMargins(QMargins(0, 0, 5, 0));

    container = new QWidget();
    container->setFixedHeight(18);

    container->setStyleSheet("* { background-color: rgb(150, 150, 150); border-color: gray; border-style: outset; border-width: 2px;}");
    hLayout->setAlignment(Qt::AlignRight);
    hLayout->addWidget(cursorInfo);
    hLayout->addWidget(toggleButton);
    container->setLayout(hLayout);

    layout->addWidget(container);
    layout->addWidget(logArea);
    this->setLayout(layout);

    connect(toggleButton, SIGNAL(clicked()), this, SLOT(toggle()));
    connect(cursorInfo->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(disableScroll()));
}

void Logger::log(QString s, QColor c)
{
    logArea->setTextColor(QColor("gray"));
    QDateTime t = QDateTime::currentDateTimeUtc();
    logArea->append(QString("[").append(t.toString()).append("] "));

    logArea->setTextColor(c);
    QTextCursor cursor = logArea->textCursor();
    cursor.insertText(s);

    logArea->setTextCursor(cursor);
    show();
}

void Logger::toggle() const
{
    if(logArea->isVisible())
    {
        hide();
    }
    else
    {
        show();
    }
}

void Logger::setCursorInfo(int line, int column)
{
    cursorInfo->setText(QString("L : ").append(QString(QString::number(line))).append(" C : ").append(QString(QString::number(column))));
}

void Logger::disableScroll()
{
    cursorInfo->verticalScrollBar()->setValue(fixedScroll);
}

void Logger::hide() const
{
    logArea->hide();
    toggleButton->setIcon(openIcon);
}

void Logger::show() const
{
    logArea->show();
    toggleButton->setIcon(closeIcon);
}
