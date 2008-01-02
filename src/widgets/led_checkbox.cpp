#ifndef SINGLE_SOURCE_COMPILE

/*
 * led_checkbox.cpp - class ledCheckBox, an improved QCheckBox
 *
 * Copyright (c) 2005-2007 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#include "led_checkbox.h"

#include <QtGui/QFontMetrics>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include "embed.h"
#include "gui_templates.h"


static const QString names[ledCheckBox::TOTAL_COLORS] =
{
	"led_yellow", "led_green"
} ;



ledCheckBox::ledCheckBox( const QString & _text, QWidget * _parent,
				const QString & _name, ledColors _color ) :
	automatableButton( _parent, _name ),
	m_text( _text )
{
	setCheckable( TRUE );

	if( _color >= TOTAL_COLORS || _color < YELLOW )
	{
		_color = YELLOW;
	}
	m_ledOnPixmap = new QPixmap( embed::getIconPixmap(
					names[_color].toAscii().constData() ) );
	m_ledOffPixmap = new QPixmap( embed::getIconPixmap( "led_off" ) );

	setFont( pointSize<7>( font() ) );
	setFixedSize( m_ledOffPixmap->width() + 4 +
					QFontMetrics( font() ).width( text() ),
			m_ledOffPixmap->height() );
}




ledCheckBox::~ledCheckBox()
{
	delete m_ledOnPixmap;
	delete m_ledOffPixmap;
}




void ledCheckBox::paintEvent( QPaintEvent * )
{
	QPainter p( this );
	p.setFont( pointSize<7>( font() ) );

	if( model()->value() == TRUE )
	{
		p.drawPixmap( 0, 0, *m_ledOnPixmap );
	}
	else
	{
		p.drawPixmap( 0, 0, *m_ledOffPixmap );
	}

	p.setPen( QColor( 64, 64, 64 ) );
	p.drawText( m_ledOffPixmap->width() + 3, 10, text() );
	p.setPen( QColor( 255, 255, 255 ) );
	p.drawText( m_ledOffPixmap->width() + 2, 9, text() );
}



#include "led_checkbox.moc"

#endif
