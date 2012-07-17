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


#include "gplacs.h"



#include "analitzaplot/plotsdictionarymodel.h"

#include <KDE/KApplication>


#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QPrinter>
#include <QtGui/QDockWidget>
#include <QtGui/QLayout>
#include <QtGui/QLabel>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsProxyWidget>
#include <QLineEdit>
#include <qstringlistmodel.h>
#include <qlistview.h>
#include <qtreeview.h>
#include <QDebug>
#include <KDE/KLocale>
#include <KDE/KLocalizedString>
#include <KDE/KStandardDirs>
#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KStandardAction>
#include <KDE/KStatusBar>
#include <KDE/KConfigDialog>
#include <KDE/KPageWidget>
#include <KDE/KPageModel>
#include <KDE/KPushButton>
#include <KDE/KFileDialog>
#include <KDE/KMessageBox>
#include <KIO/NetAccess>
#include <KDE/KMessageBox>
#include <KDE/KRecentFilesAction>
#include <KDE/KConfigDialog>
#include <KDE/KStandardDirs>
#include <KToolBar>
#include "functionsmodel.h"
#include "spacesmodel.h"
#include "widgets/gplacswidget.h"
#include <KAboutApplicationDialog>
#include <KMenuBar>
#include <kcategorizedview.h>
#include <kcategorydrawer.h>
#include "widgets/dashboard.h"


namespace GPLACS
{






//////////////

MainWindow::MainWindow()
    : KXmlGuiWindow()
{



    m_functionsModel = new Keomath::FunctionsModel(this);
    m_spacesModel = new Keomath::SpacesModel(this);

    m_gplacsWidget = new Dashboard(m_functionsModel, m_spacesModel, this);

    
    statusBar()->hide();
    setupActions();
    setupGUI();

   setCentralWidget(m_gplacsWidget); 
//     QTabWidget *tabs = new QTabWidget(this);
//     tabs->addTab(m_gplacsWidget, "ad");
//     
//     VisualItemsModel *model = m_functionsModel;
//     KCategorizedSortFilterProxyModel *proxyModel = new KCategorizedSortFilterProxyModel(this);
//     proxyModel->setCategorizedModel( true );
//     proxyModel->setSortCategoriesByNaturalComparison(true);
//     proxyModel->setSourceModel( model );
//     proxyModel->sort( 0 );
//     
// 
//         
//     KCategorizedView *categoryView = new KCategorizedView(this);
//     KCategoryDrawerV2 *categoryDrawer = new KCategoryDrawerV2();
//     categoryView->setSelectionMode( QAbstractItemView::SingleSelection );
// //     categoryView->setSpacing( KDialog::spacingHint() );
//     categoryView->setCategoryDrawer( categoryDrawer );
// //     categoryView->setViewMode( QListView::IconMode );
// //     categoryView->setMouseTracking( true );
// //     categoryView->viewport()->setAttribute( Qt::WA_Hover );
// //     categoryView->setFrameShape( QFrame::NoFrame );
//     categoryView->setModel( proxyModel );
//     categoryView->setGridSize(QSize(200,32));
// 
//     proxyModel->setCategorizedModel(false); //BEGIN NOTE IMPORTANT WARNING PRIMERO HACER UN LOCK
// 
//     
//     PlaneCurve *item = model->addPlaneCurve(Analitza::Expression("x->x*x"), "para", Qt::cyan);
//     model->addPlaneCurve(Analitza::Expression("q->q+2"), "polar simple", Qt::green);
//     model->addPlaneCurve(Analitza::Expression("t->vector{t*t+1, t+2}"), "vec", Qt::yellow);
//     PlaneCurve *item2 = model->addPlaneCurve(Analitza::Expression("5*(x**2+y**2)**3=15*(x*y*72)**2"), "impl", Qt::red);
//     model->addPlaneCurve(Analitza::Expression("x->2+x*x"), "otra simple", Qt::blue);
//     model->addPlaneCurve(Analitza::Expression("t->vector{t*t+1, 2*t+2}"), "vec", Qt::yellow);
//     model->addPlaneCurve(Analitza::Expression("t->vector{t*t+1, 3*t+2}"), "vec", Qt::yellow);
//     model->addPlaneCurve(Analitza::Expression("t->vector{t*t+1, 4*t+2}"), "vec", Qt::yellow);
//     model->addPlaneCurve(Analitza::Expression("t->vector{t*t+1, 4*t+2}"), "vec", Qt::yellow);
//     model->addPlaneCurve(Analitza::Expression("t->vector{t*t+1, 4*t+2}"), "vec", Qt::yellow);
//     model->addPlaneCurve(Analitza::Expression("t->vector{t*t+1, 4*t+2}"), "vec", Qt::yellow);
//     proxyModel->setCategorizedModel(true); //END NOTE IMPORTANT WARNING PRIMERO HACER UN LOCK
// 
//     tabs->addTab(categoryView, "lis");
//     
//     tabs->setCurrentIndex(1);
//     setCentralWidget(tabs);
    


    updateTittleWhenOpenSaveDoc();


    connect(m_gplacsWidget, SIGNAL( modified() ), SLOT( updateTittleWhenChangeDocState() ));

    connect(m_gplacsWidget, SIGNAL(dashemitShowAppInfo()), SLOT(showAboutAppDialog()));

    menuBar()->hide();






}

MainWindow::~MainWindow()
{
}

void MainWindow::setupActions()
{





    KStandardAction::quit   (this, SLOT( close()      ), actionCollection());

    
    



    
    
    

    

    connect(m_gplacsWidget, SIGNAL(saveRequest()), SLOT(saveFile()));
    connect(m_gplacsWidget, SIGNAL(openRequest()), SLOT(openFile()));

}


bool MainWindow::queryClose()
{
    if (m_gplacsWidget->isModified())
    {
        QString paletteFileName = m_gplacsWidget->fileName();

        if (paletteFileName.isEmpty())
            paletteFileName = i18n("Untitled");

        switch (KMessageBox::warningYesNoCancel(this,
                                                i18n( "The document \"%1\" has been modified.\n"
                                                        "Do you want to save your changes or discard them?", paletteFileName),
                                                i18n( "Close Document" ), KStandardGuiItem::save(), KStandardGuiItem::discard()))
        {
        case KMessageBox::Yes:
        {
            
            
            
            
            
            m_gplacsWidget->showDashboard();

            saveFile();

            return m_gplacsWidget->isSaved();
        }
        case KMessageBox::No :
            return true;
            
        default :
            return false;
        }
    }

    return true;
}

void MainWindow::openFile()
{
    QString filter = QString("*.gplacs|") + i18n("All Supported Files") +
                     QString("\n*.gplacs|") + i18n("GPLACS standard file format") + QString(" (*.gplacs)");

    KUrl paletteUrl = KFileDialog::getOpenUrl(KUrl(), filter);



    QString paletteFileName;

    if (!paletteUrl.isEmpty())
    {
        if (KIO::NetAccess::download(paletteUrl, paletteFileName, this))
        {
            if (m_gplacsWidget->load(paletteFileName))
            {
                updateTittleWhenOpenSaveDoc();

                m_gplacsWidget->setModified(false);
                m_gplacsWidget->setSaved(true);
            }



            KIO::NetAccess::removeTempFile(paletteFileName);
        }
        else
            KMessageBox::error(this, KIO::NetAccess::lastErrorString());
    }
}

void MainWindow::showAboutAppDialog()
{
    const KAboutData *aboutData = KGlobal::mainComponent().aboutData();
    KAboutApplicationDialog a(aboutData, KAboutApplicationDialog::HideTranslators, this);
    a.exec();
}

void MainWindow::newFile()
{
    MainWindow * newWnd = new MainWindow();
    newWnd->show();
}

void MainWindow::saveFile()
{
    

    if (!m_gplacsWidget->fileName().isEmpty())
    {
        if (m_gplacsWidget->save(m_gplacsWidget->fileName()))
        {
            updateTittleWhenOpenSaveDoc();
        }

    }
    else
    {
        QString filter = QString("*.gplacs|") + i18n("All Supported Files") +
                         QString("\n*.gplacs|") + i18n("GPLACS standard file format") + QString(" (*.gplacs)");

        QString paletteFileName = KFileDialog::getSaveFileName(KUrl(QDir::homePath()), filter);

        if (KIO::NetAccess::exists(KUrl(paletteFileName), KIO::NetAccess::DestinationSide, widget()))
            if (KMessageBox::warningContinueCancel(widget(), i18n("A file named \"%1\" already exists. Are you sure you want to overwrite it?", paletteFileName), QString(), KGuiItem(i18n("Overwrite"))) != KMessageBox::Continue)
                return;


        if (m_gplacsWidget->save(paletteFileName))
        {
            updateTittleWhenOpenSaveDoc();

        }

    }
}

void MainWindow::saveFileAs(const QString &filename)
{






    
}


void MainWindow::updateInputTypePreviewImage(bool text_input)
{






}

void MainWindow::updateTittleWhenChangeDocState()
{
    QString paletteFileName = m_gplacsWidget->fileName();

    if (paletteFileName.isEmpty())
        paletteFileName = i18n("Untitled");

    setWindowTitle(QString("%1 - GPLACS " + i18n("[modificado]")).arg(paletteFileName));
}

void MainWindow::updateTittleWhenOpenSaveDoc()
{
    QString paletteFileName = m_gplacsWidget->fileName();

    if (paletteFileName.isEmpty())
        paletteFileName = i18n("Untitled");

    setWindowTitle(QString("%1 - GPLACS").arg(paletteFileName));
}

void MainWindow::optionsPreferences()
{
    
    
    
    
    

















}

} 
