#include "logger.h"

Logger::Logger()
{
    logArea = new QTextEdit();
    logArea->setFixedHeight(100);
    logArea->setReadOnly(true);
    logArea->hide();

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
    hLayout->addWidget(toggleButton);
    container->setLayout(hLayout);

    layout->addWidget(container);
    layout->addWidget(logArea);
    this->setLayout(layout);

    connect(toggleButton, SIGNAL(clicked()), this, SLOT(toggle()));
}

void Logger::log(QString s, QColor c)
{
    logArea->setTextColor(c);
    logArea->append(s);
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
