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

#ifndef _pandamonium_gui_h_
#define _pandamonium_gui_h_

#include <QFuture>
#include <QMainWindow>
#include <QTimer>

#include "ui_pandamonium.h"
#include "ui_pandamonium_broken_links.h"
#include "ui_pandamonium_export_definition.h"
#include "ui_pandamonium_statistics.h"
#include "ui_pandamonium_statusbar.h"

class pandamonium_gui: public QMainWindow
{
  Q_OBJECT

 public:
  pandamonium_gui(void);
  ~pandamonium_gui();

 private:
  QFuture<void> m_future;
  QMainWindow *m_brokenLinksWindow;
  QMainWindow *m_exportMainWindow;
  QMainWindow *m_statisticsMainWindow;
  QString m_iconName;
  QTimer m_highlightTimer;
  QTimer m_kernelDatabaseTimer;
  QTimer m_tableListTimer;
  QWidget *m_sbWidget;
  Ui_pandamonium_broken_links m_uiBrokenLinks;
  Ui_pandamonium_export m_uiExport;
  Ui_pandamonium_mainwindow m_ui;
  Ui_pandamonium_statistics m_uiStatistics;
  Ui_pandamonium_statusbar m_sb;
  uint m_parsedLinksLastDateTime;
  bool areYouSure(const QString &text, QWidget *parent);
  void center(QWidget *child, QWidget *parent);
  void closeEvent(QCloseEvent *event);
  void gatherStatistics(void);
  void populateBroken(void);
  void populateParsed(void);
  void processExportDatabase(const QString &path);
  void saveKernelPath(const QString &path);
  void setIcons(void);

 private slots:
  void slotAbout(void);
  void slotActivateKernel(void);
  void slotAddSearchUrl(void);
  void slotCopySelectedURL(void);
  void slotCustomContextMenuRequested(const QPoint &point);
  void slotDeactivateKernel(void);
  void slotDeleteExportedUrlsCheckBoxClicked(bool state);
  void slotDepthChanged(const QString &text);
  void slotExport(void);
  void slotExportCheckBoxClicked(bool state);
  void slotExportDefinition(void);
  void slotExportTableSelected(void);
  void slotHighlightTimeout(void);
  void slotKernelDatabaseTimeout(void);
  void slotKernelToolButtonClicked(void);
  void slotListParsedUrls(void);
  void slotListSearchUrls(void);
  void slotLoadIntervalChanged(const QString &text);
  void slotMetaDataOnly(bool state);
  void slotMonitorKernel(bool state);
  void slotPageChanged(int index);
  void slotPause(bool state);
  void slotProxyInformationToggled(bool state);
  void slotQuit(void);
  void slotRefreshBrokenUrls(void);
  void slotRemoveAllBrokenUrls(void);
  void slotRemoveAllParsedUrls(void);
  void slotRemoveSelectedBrokenUrls(void);
  void slotRemoveSelectedParsedUrls(void);
  void slotRemoveSelectedSearchUrls(void);
  void slotRemoveUnvisitedVisitedUrls(void);
  void slotSaveExportDefinition(void);
  void slotSaveKernelPath(void);
  void slotSavePageLimit(const QString &text);
  void slotSavePeriodic(bool state);
  void slotSaveProxyInformation(void);
  void slotSelectExportDatabase(void);
  void slotSelectKernelPath(void);
  void slotSetIcons(void);
  void slotShowBrokenLinksWindow(void);
  void slotShowStatisticsWindow(void);
  void slotStatisticsReady(const QList<QVariant> &statistics);
  void slotTabIndexChanged(int index);
  void slotTableListTimeout(void);
  void slotToggleParsed(void);

 signals:
  void statisticsReady(const QList<QVariant> &statistics);
};

#endif
