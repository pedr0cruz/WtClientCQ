/// CQWtAppView.h

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
    /// Widget contenedor del widget con las pestañas para las tablas de resultados
    Wt::WContainerWidget* resultSetsViewContainer_;
    /// La vista de conjuntos de resultados (tablas) es un widget con pestañas
    ResultSetsView* resultSetsView_;

    /// Widget contenedor del widget con las pestañas para los formularios
    Wt::WContainerWidget* recordSetsViewContainer_;
    /// La vista de conjuntos de registros (formularios) es un widget con pestañas 
    RecordSetsView* recordSetsView_;

    //< Vector con punteros a tablas WTableViews que van dentro de resultSetTabsContainer_
    //vector <Wt::WTableView>         resultSetTablesVec_;
    //< Vector con punteros a formularios WTemplateFormView que van dentro de recordSetTabsContainer_
    //vector <Wt::WTemplateFormView>  recordSetFormsVec_;

public:
	/// Constructor: crea toda la vista exterior de la App
    CQWtAppView(Wt::WContainerWidget* PageRoot);

    /// Función generada por WtDesigner
    void addAllStyleSheets();
    /// Función generada por WtDesigner
    void addAllJavaScripts();
    /// Función generada por WtDesigner
    void connectAllSignals();

    /// Destructor
    ~CQWtAppView();

public:
    /// Funciones para obtener las propiedades ("getters")

    /// Contenedor principal de nivel superior
    Wt::WContainerWidget* appContainer();
    /// Contenedor del panel superior
    Wt::WContainerWidget* topPanelContainer();
    /// Contenedor del panel izquierdo ("workspace")
    Wt::WContainerWidget* workSpaceContainer();
    /// Contenedor de las pestañas con vistas de resultados (tablas)
    Wt::WContainerWidget* resultSetsViewContainer();
    /// Vista con las pestañas con vistas de resultados
    ResultSetsView*       resultSetsView();
    /// Contenedor de las pestañas con vistas de registros (formularios)
    Wt::WContainerWidget* recordSetsViewContainer();
    /// Vista con las pestañas con vistas de registros (formularios)
    RecordSetsView*       recordSetsView();
    /// Contenedor del panel inferior ("footer")
    Wt::WContainerWidget* footerContainer();
};

#endif /// CQWTAPPVIEW_H
