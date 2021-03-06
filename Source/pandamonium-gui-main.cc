/*
** Copyright (c) Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from pandamonium without specific prior written permission.
**
** pandamonium IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** pandamonium, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QApplication>
#ifdef Q_OS_MAC
#if QT_VERSION < 0x050000
#include <QMacStyle>
#endif
#endif
#include <QSettings>

#include <iostream>

#include "pandamonium-common.h"
#include "pandamonium-gui.h"

int main(int argc, char *argv[])
{
#ifdef Q_OS_MAC
#if QT_VERSION < 0x050000
  QMacStyle *style = new (std::nothrow) QMacStyle();

  if(style)
    QApplication::setStyle(style);
#endif
#endif
#if QT_VERSION >= 0x050000
#ifdef Q_OS_WIN32
  QApplication::addLibraryPath("plugins");
  QApplication::setStyle("fusion");
#endif
#endif

  QApplication qapplication(argc, argv);

#ifdef Q_OS_MAC
#if QT_VERSION >= 0x050000
  /*
  ** Eliminate pool errors on OS X.
  */

  CocoaInitializer ci;
#endif
#endif
  QApplication::setApplicationName("pandamonium");
  QApplication::setOrganizationName("pandamonium");
  QApplication::setOrganizationDomain("pandamonium");
  QApplication::setApplicationVersion(pandamonium_VERSION_STR);
  QSettings::setPath(QSettings::IniFormat, QSettings::UserScope,
                     pandamonium_common::homePath());
  QSettings::setDefaultFormat(QSettings::IniFormat);

  pandamonium_gui *p = 0;

  try
    {
      p = new pandamonium_gui();
      return qapplication.exec();
    }
  catch(const std::bad_alloc &exception)
    {
      std::cerr << QObject::tr("Memory allocation error at line ").
	toStdString()
		<< __LINE__
		<< QObject::tr(", file ").toStdString()
		<< __FILE__ << "." << std::endl;
      exit(EXIT_FAILURE);
    }

  if(p)
    p->deleteLater();

  return EXIT_SUCCESS;
}
