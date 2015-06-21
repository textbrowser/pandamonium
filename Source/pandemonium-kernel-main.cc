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
**    derived from pandemonium without specific prior written permission.
**
** PANDEMONIUM IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** PANDEMONIUM, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QCoreApplication>
#include <QSettings>

#include <iostream>

#include "pandemonium-common.h"
#include "pandemonium-database.h"
#include "pandemonium-kernel.h"

static qint64 s_kernel_process_id = 0;

static void signal_handler(int signal_number)
{
  static int fatal_error = 0;

  if(fatal_error)
    _Exit(signal_number);

  fatal_error = 1;
  pandemonium_database::recordKernelDeactivation(s_kernel_process_id);
  _Exit(signal_number);
}

int main(int argc, char *argv[])
{
  pandemonium_common::prepareSignalHandler(signal_handler);

  QCoreApplication qapplication(argc, argv);

  s_kernel_process_id = qapplication.applicationPid();

  if(pandemonium_database::isKernelActive())
    {
      qapplication.exit(EXIT_FAILURE);
      return EXIT_FAILURE;
    }

#ifdef Q_OS_MAC
#if QT_VERSION >= 0x050000
  /*
  ** Eliminate pool errors on OS X.
  */

  CocoaInitializer ci;
#endif
#endif
  QCoreApplication::setApplicationName("pandemonium");
  QCoreApplication::setOrganizationName("pandemonium");
  QCoreApplication::setOrganizationDomain("pandemonium");
  QCoreApplication::setApplicationVersion(PANDEMONIUM_VERSION_STR);
  QSettings::setPath(QSettings::IniFormat, QSettings::UserScope,
                     pandemonium_common::homePath());
  QSettings::setDefaultFormat(QSettings::IniFormat);

  pandemonium_kernel *p = 0;

  try
    {
      p = new pandemonium_kernel();
      return qapplication.exec();
    }
  catch(std::bad_alloc &exception)
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
