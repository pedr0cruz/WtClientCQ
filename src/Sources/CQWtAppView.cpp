// CQWtAppView.cpp

#include "stdafx.h"

#include <Wt/WApplication>
#include <Wt/WFileResource>
#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>
#include <Wt/WTemplateFormView>
#include <Wt/WBootstrapTheme>
#include <Wt/WBorderLayout>
#include <Wt/WText>
#include <Wt/WLength>

#include <CQWtAppView.h>

#include <ResultSetsView.h>
#include <RecordSetsView.h>

using namespace Wt;

// Constructor: crea toda la vista exterior de la App
CQWtAppView::CQWtAppView(Wt::WContainerWidget *PageRoot)
{
	Wt::WBootstrapTheme * p_wtTheme = new Wt::WBootstrapTheme();
	p_wtTheme->setVersion(Wt::WBootstrapTheme::Version3);
	Wt::WApplication::instance()->setTheme(p_wtTheme);
	Wt::WApplication::instance()->setTitle("Proyecto CQWt");

	// Configuracion inicial del root
	wt_root = PageRoot;
	wt_root->setId("wt_root");
	wt_root->setStyleClass(Wt::WString::fromUTF8(""));
	wt_root->setHeight(WLength(100, WLength::Percentage));
	wt_root->setInline(0);

	///////////////////////////////////////////////////////////////
	// ENTORNO: Se contruye de adentro hacia afuera
	///////////////////////////////////////////////////////////////
#if defined (MYTEST)
    // Para escribir textos en los paneles
	const char *cell = "{1} panel"; 
	WText *item;
#endif
	// Creo un contendor adicional interno full screen
	//appContainer_ = new Wt::WContainerWidget(wt_root);
	//appContainer_->setHeight(WLength("100%")); // ó (100, WLength::Percentage));
    appContainer_ = wt_root;

	///////////////// Interiores

	// Panel Detalles
	Wt::WGridLayout *layoutDetalles = new Wt::WGridLayout();
	layoutDetalles->setRowResizable(0); // No cambia de tamaño externo

    // Lista de pestañas con tablas de resultados
    resultSetsViewContainer_ = new Wt::WContainerWidget(appContainer_);
    resultSetsView_ = new ResultSetsView(resultSetsViewContainer_);

    // Agrega el contenedor (que contiene el panel con las pestañas) 
    // en la fila superior de la rejilla.
    layoutDetalles->addWidget(resultSetsViewContainer_, 0, 0);

#if defined (MYTEST)
#if 0
	/// Imprime el texto "Panel TABLE"
	resultSetContainer_->setStyleClass("green-box");
	item = new Wt::WText(Wt::WString(cell).arg("TABLE"));
	resultSetContainer_->addWidget(item);
#endif

    /*
	auto newTabForResultSets = new Wt::WTableView();
//    resultSetsViewContainer_->setStyleClass("green-box");
	//item = new Wt::WText(Wt::WString(cell).arg("TABLE"));
	Wt::WString tab_text("tab1-tableview1");
    //auto menu_for_tab = resultSetsTabWidget_->addTab(newTabForResultSets, tab_text);
    auto menu_for_tab = resultSetsView_->addTab(newTabForResultSets, tab_text);
    */
#endif

    // Panel contenedor de pestañas con formularios (panel derecho inferior)
	//recordSetsTabsContainer_ = new Wt::WContainerWidget(appContainer_);
    // Panel con las pestañas de las planillas
    //recordSetsTabWidget_ = new RecordSetsView(recordSetsTabsContainer_);

    // Panel contenedor de pestañas con formularios (panel derecho inferior)
    //recordSetsTabsContainer_ = RecordSetsView::createView(appContainer_);
    // Panel con las pestañas de las planillas
    //recordSetsTabWidget_ = new Wt::WTabWidget(recordSetsTabsContainer_);
    recordSetsViewContainer_ = new Wt::WContainerWidget(appContainer_);
    recordSetsView_ = new RecordSetsView(recordSetsViewContainer_);

    //	CHECK: the argument should be recordFormContainer_ OR appContainer_ ???
    //recordFormContainer_->addTab(new Wt::WContainerWidget(recordFormContainer_), Wt::WString ("tab1"));
    //layoutDetalles->addWidget(recordFormContainer_, 1, 0);

    // Agrega el panel con las planillas (formularios) al contenedor creado antes
    //recordSetsTabsContainer_->addWidget(recordSetsTabWidget_);

    // Agrega el contenedor (que contiene el panel con las pestañas) al contenedor interior
    //layoutDetalles->addWidget(recordSetsTabsContainer_, 1, 0);
    layoutDetalles->addWidget(recordSetsViewContainer_, 1, 0);

#if 0 && defined (MYTEST)
    // Imprime el texto "Panel DETAILS" 	
	item = new Wt::WText(Wt::WString(cell).arg("DETAILS"));
    //recordSetsTabsContainer_->setStyleClass("green-box");
//    recordSetsViewContainer_->setStyleClass("green-box");

	//recordFormContainer_->addWidget(item);
	//	CHECK: the argument should be recordFormContainer_ OR appContainer_ ???
    //recordSetsTabWidget_->addTab(new Wt::WTemplateFormView(recordSetsTabsContainer_), Wt::WString("tab1"));
    recordSetsView_->addTab(new Wt::WTemplateFormView(recordSetsViewContainer_), Wt::WString("tab1-form1"));
#endif

	///////////////// Interior (Izquierdo)
	Wt::WGridLayout *layoutInterior = new Wt::WGridLayout();
	layoutInterior->addLayout(layoutDetalles, 0, 1); ///< Coloco el detalle(tabla y formularios)
	layoutInterior->setColumnStretch(1, 1); ///< La segunda columna ocupa todo el espacio posible
	layoutInterior->setColumnResizable(0);

	// Panel WorkSpace
	workSpaceContainer_ = new Wt::WContainerWidget(appContainer_);
    workSpaceContainer_->setWidth(WLength(30, WLength::Percentage));
#if defined (MYTEST)
    // Imprime el texto "Panel LEFT" 	
    item = new Wt::WText(Wt::WString(cell).arg("LEFT"));
    //	workSpaceContainer_->setStyleClass("green-box");
    workSpaceContainer_->addWidget(item);
#endif
    layoutInterior->addWidget(workSpaceContainer_, 0, 0);

	///////////////// Exteriores (Superior e Inferior)
	Wt::WGridLayout *layoutExterior = new Wt::WGridLayout();
	layoutExterior->addLayout(layoutInterior, 1, 0); // Coloco el centro
	layoutExterior->setRowStretch(1, 1);

	// Panel Superior
	topPanelContainer_ = new Wt::WContainerWidget(appContainer_);
	layoutExterior->addWidget(topPanelContainer_, 0, 0);

#if 0 && defined (MYTEST)
	// Imprime el texto "Panel TOP" 	
	item = new Wt::WText(Wt::WString(cell).arg("TOP"));
	topPanelContainer_->addWidget(item);
//	topPanelContainer_->setStyleClass("green-box");
#endif

	// Panel inferior
	footerContainer_ = new Wt::WContainerWidget(appContainer_);
	layoutExterior->addWidget(footerContainer_, 2, 0);

#if 0 && defined (MYTEST)
	// Imprime el texto "Panel DOWN" 	
	item = new Wt::WText(Wt::WString(cell).arg("DOWN"));
//	footerContainer_->setStyleClass("green-box");
	footerContainer_->addWidget(item);
#endif

	// Ingresa el layout al container principal de la app
	appContainer_->setLayout(layoutExterior); 

	// Metodos autogenerados por WtDesigner
	addAllStyleSheets();
	connectAllSignals();
	addAllJavaScripts();
}

void CQWtAppView::addAllStyleSheets()
{
	Wt::WApplication::instance()->useStyleSheet(Wt::WLink("resources/main.css"));
}

void CQWtAppView::addAllJavaScripts()
{
}

void CQWtAppView::connectAllSignals()
{
}

CQWtAppView::~CQWtAppView()
{
	// Al eliminar el Contendor exterior, se borran recursivamente todo lo interior
	delete appContainer_;		
}

// Getters

WContainerWidget* CQWtAppView::appContainer()
{
	return appContainer_;
}

WContainerWidget* CQWtAppView::topPanelContainer()
{
	return topPanelContainer_;
}

WContainerWidget* CQWtAppView::workSpaceContainer()
{
	return workSpaceContainer_;
}

#if 0
WContainerWidget* CQWtAppView::resultSetsTabsContainer()
{
	return resultSetsTabsContainer_;
}

WContainerWidget* CQWtAppView::recordSetsTabsContainer()
{
	return recordSetsTabsContainer_;
}
#endif

WContainerWidget* CQWtAppView::resultSetsViewContainer()
{
    return resultSetsViewContainer_;
}

WContainerWidget* CQWtAppView::recordSetsViewContainer()
{
    return recordSetsViewContainer_;
}

WContainerWidget* CQWtAppView::footerContainer()
{
	return footerContainer_;
}
