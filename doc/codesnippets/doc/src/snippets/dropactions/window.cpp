/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QLabel *textLabel = new QLabel(tr("Data:"), this);
    textBrowser = new QTextBrowser(this);

    QLabel *mimeTypeLabel = new QLabel(tr("MIME types:"), this);
    mimeTypeCombo = new QComboBox(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textLabel);
    layout->addWidget(textBrowser);
    layout->addWidget(mimeTypeLabel);
    layout->addWidget(mimeTypeCombo);
/*
    ...
    setAcceptDrops(true);
*/
    setAcceptDrops(true);
    setWindowTitle(tr("Drop Actions"));
}

void Window::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void Window::dropEvent(QDropEvent *event)
{
    QMenu actionMenu(this);
    QAction *copyAction = 0;
    QAction *moveAction = 0;
    QAction *linkAction = 0;
    QAction *ignoreAction = 0;
    if (event->possibleActions() & Qt::CopyAction)
        copyAction = actionMenu.addAction(tr("Copy"));
    if (event->possibleActions() & Qt::MoveAction)
        moveAction = actionMenu.addAction(tr("Move"));
    if (event->possibleActions() & Qt::LinkAction)
        linkAction = actionMenu.addAction(tr("Link"));
    if (event->possibleActions() & Qt::IgnoreAction)
        ignoreAction = actionMenu.addAction(tr("Ignore"));

    QAction *result = actionMenu.exec(QCursor::pos());

    if (copyAction && result == copyAction)
        event->setDropAction(Qt::CopyAction);
    else if (moveAction && result == moveAction)
        event->setDropAction(Qt::MoveAction);
    else if (linkAction && result == linkAction)
        event->setDropAction(Qt::LinkAction);
    else {
        event->setDropAction(Qt::IgnoreAction);
        return;
    }

    textBrowser->setPlainText(event->mimeData()->text());
    mimeTypeCombo->clear();
    mimeTypeCombo->addItems(event->mimeData()->formats());
}
