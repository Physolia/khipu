/*************************************************************************************
 *  Copyright (C) 2010 by Percy Camilo T. Aucahuasi <percy.camilo.ta@gmail.com>      *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/


#ifndef GPLACS_BUTTON_H
#define GPLACS_BUTTON_H


#include <QtGui/QToolButton>



class QPaintEvent;
class QFocusEvent ;
#include "../keomathexport.h"
namespace Keomath {


class KEOMATH_EXPORT Button : public QToolButton
{
    Q_OBJECT

    public:
        Button(QWidget *parent = 0);

    signals:
        void mouseHovered();
        void mouseLeft();

    protected:
        void paintEvent(QPaintEvent *event);
        void enterEvent(QEvent *event);
        void leaveEvent(QEvent *event);

    private:
        bool m_onHover;
};


} 

#endif 
