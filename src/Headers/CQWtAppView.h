// CQWtAppView.h
//

#ifndef CQWTAPPVIEW_H 
#define CQWTAPPVIEW_H

#pragma once

#include <Wt/WApplication>
#include <Wt/WFileResource>
#include <Wt/WContainerWidget>
#include <Wt/WBootstrapTheme>
#include <Wt/WBorderLayout>
#include <Wt/WText>
#include <Wt/WLength>
#include <Wt/WTabWidget>
#include <Wt/WTemplateFormView>

#include <vector>

/// definicion que incluye lineas para probar la clase
#define MYTEST 

/// Declaraciones adelantadas de clases (forward class declarations)
class ResultSetsView;
class RecordSetsView;

///	CQWtAppView: clase que implementa la vista de la aplicacion.
///	CQWtAppView recibe en formato JSON los datos y se ocupa hacer
/// el rendering de dichos datos. Se va a cambiar para usar los
/// widgets de WT, algo que no se ha logrado todavia.
class CQWtAppView
{
protected:
    Wt::WContainerWidget    *wt_root,				    ///< Widget raiz
                            *appContainer_,			    ///< Contendor exterior
                            *topPanelContainer_,	    ///< Contenedor del panel superior
                            *workSpaceContainer_,       ///< Contenedor del arbol izquierdo
//                            *resultSetsTabsContainer_,  ///< Contenedor con pestañas para las tablas de resultados
//                            *recordSetsTabsContainer_,  ///< Contenedor con pestañas para los formularios
                            *footerContainer_;          ///< Contenedor del pie de pagina
#if 0
    Wt::WTabWidget  *resultSetsTabWidget_,   ///< Widget con las pestañas para las tablas de resultados
                    *recordSetsTabWidget_;   ///< Widget con las pestañas para los formularios
#endif
    Wt::WContainerWidget* resultSetsViewContainer_;
    ResultSetsView* resultSetsView_;

    Wt::WContainerWidget* recordSetsViewContainer_;
    RecordSetsView* recordSetsView_;

    //< Vector con punteros a tablas WTableViews que van dentro de resultSetTabsContainer_
    //vector <Wt::WTableView>         resultSetTablesVec_;
    //< Vector con punteros a formularios WTemplateFormView que van dentro de recordSetTabsContainer_
    //vector <Wt::WTemplateFormView>  recordSetFormsVec_;

public:
	/// Constructor: crea toda la vista exterior de la App
    CQWtAppView(Wt::WContainerWidget* PageRoot);

    void addAllStyleSheets();

    void addAllJavaScripts();

    void connectAllSignals();

    ~CQWtAppView();

public:
    /// Getters para las propiedades
#if 0
    Wt::WContainerWidget* appContainer() { return appContainer_; }
    Wt::WContainerWidget* topPanelContainer() { return topPanelContainer_; }
    Wt::WContainerWidget* workSpaceContainer() { return workSpaceContainer_; }
    
    Wt::WContainerWidget* resultSetsTabsContainer() { return resultSetsTabsContainer_; }
    Wt::WTabWidget*       resultSetsTabWidget() { return resultSetsTabWidget_; }

    Wt::WContainerWidget* recordSetsTabsContainer() { return recordSetsTabsContainer_; }
    Wt::WTabWidget*       recordSetsTabWidget() { return recordSetsTabWidget_; }

    Wt::WContainerWidget* footerContainer() { return footerContainer_; }
#endif
    Wt::WContainerWidget* appContainer();
    Wt::WContainerWidget* topPanelContainer();
    Wt::WContainerWidget* workSpaceContainer();

//    Wt::WContainerWidget* resultSetsTabsContainer();
//    Wt::WTabWidget*       resultSetsTabWidget();

//    Wt::WContainerWidget* recordSetsTabsContainer();
//    Wt::WTabWidget*       recordSetsTabWidget();

    Wt::WContainerWidget* resultSetsViewContainer();
    ResultSetsView* resultSetsView();

    Wt::WContainerWidget* recordSetsViewContainer();
    RecordSetsView* recordSetsView();

    Wt::WContainerWidget* footerContainer();
};

#endif /// CQWTAPPVIEW_H