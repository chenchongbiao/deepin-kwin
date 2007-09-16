//////////////////////////////////////////////////////////////////////////////
// oxygenbutton.cpp
// -------------------
// Oxygen window decoration for KDE. Buttons.
// -------------------
// Copyright (c) 2006, 2007 Riccardo Iaconelli <ruphy@fsfe.org>
// Copyright (c) 2006, 2007 Casper Boemann <cbr@boemann.dk>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <QPainterPath>
#include <QPainter>
#include <QBitmap>

#include <kdecoration.h>

#include "oxygenclient.h"
#include "oxygenbutton.h"
#include "oxygen.h"
#include "definitions.cpp"
#include "lib/helper.h"

namespace Oxygen
{
K_GLOBAL_STATIC_WITH_ARGS(OxygenHelper, globalHelper, ("OxygenDeco"))

// class OxygenClient;
/*
extern int BUTTONSIZE;
extern int DECOSIZE;*/

// static const int BUTTONSIZE      = 18;
// static const int DECOSIZE        = 8;
//////////////////////////////////////////////////////////////////////////////
// OxygenButton Class                                                      //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// OxygenButton()
// ---------------
// Constructor

OxygenButton::OxygenButton(OxygenClient *parent,
                             const QString& tip, ButtonType type,
                             const unsigned char *bitmap)
    : QAbstractButton(parent->widget()), client_(parent), type_(type),
      lastmouse_(0)
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent, false);
    setFixedSize(BUTTONSIZE, BUTTONSIZE);
    setCursor(Qt::ArrowCursor);
    setToolTip(tip);
}

OxygenButton::~OxygenButton()
{
}

//////////////////////////////////////////////////////////////////////////////
// sizeHint()
// ----------
// Return size hint

QSize OxygenButton::sizeHint() const
{
    return QSize(BUTTONSIZE, BUTTONSIZE);
}

//////////////////////////////////////////////////////////////////////////////
// enterEvent()
// ------------
// Mouse has entered the button

void OxygenButton::enterEvent(QEvent *e)
{
    // if we wanted to do mouseovers, we would keep track of it here
    if (status_ != Oxygen::Pressed) {
        status_ = Oxygen::Hovered;
    }
    QAbstractButton::enterEvent(e);
}

//////////////////////////////////////////////////////////////////////////////
// leaveEvent()
// ------------
// Mouse has left the button

void OxygenButton::leaveEvent(QEvent *e)
{
    // if we wanted to do mouseovers, we would keep track of it here
    status_ = Oxygen::Normal;
    QAbstractButton::leaveEvent(e);
}

//////////////////////////////////////////////////////////////////////////////
// pressSlot()
// ------------
// Mouse has pressed the button

void OxygenButton::pressSlot()
{
    kDebug() << "Pressed ";
    status_ = Oxygen::Pressed;
    update();
}
//////////////////////////////////////////////////////////////////////////////
// drawButton()
// ------------
// Draw the button

void OxygenButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (type_ == ButtonMenu) {
        // we paint the mini icon (which is 16 pixels high)
        int dx = (width() - 16) / 2;
        int dy = (height() - 16) / 2;
        painter.drawPixmap(dx, dy, client_->icon().pixmap(16));
        return;
    }

    QColor bg = globalHelper->backgroundTopColor(palette().window());
    painter.drawPixmap(0, 0, globalHelper->windecoButton(palette().button(), BUTTONSIZE));

    painter.setRenderHints(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);
    QLinearGradient lg(0, 6, 0, 12);
    lg.setColorAt(0.45, QColor(0,0,0,150));
    lg.setColorAt(0.80, QColor(0,0,0,80));
    painter.setPen(QPen(lg,2));
    switch(type_)
    {
        case ButtonSticky:
        case ButtonHelp:
            break;
        case ButtonMin:
            painter.drawLine(6,8,9,11);
            painter.drawLine(9,11,12,8);
            break;
        case ButtonMax:
            painter.drawLine(9,8,12,11);
            painter.drawLine(6,11,9,8);
            break;
        case ButtonClose:
            painter.drawLine(6,6,12,12);
            painter.drawLine(12,6,6,12);
            break;
    }
}








} //namespace Oxygen
