//	CQWtAppView2.cpp

#include <Wt/WApplication>
#include <Wt/WFileResource>
#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>
#include <Wt/WTemplateFormView>
#include <Wt/WBootstrapTheme>
#include <Wt/WBorderLayout>
#include <Wt/WText>
#include <Wt/WLength>

#include <CQWtAppView2.h>

using namespace Wt;

/// Constructor: crea toda la vista exterior de la App
CQWtAppView2::CQWtAppView2(Wt::WContainerWidget *PageRoot)
{
	Wt::WBootstrapTheme * p_wtTheme = new Wt::WBootstrapTheme();
	p_wtTheme->setVersion(Wt::WBootstrapTheme::Version3);
	Wt::WApplication::instance()->setTheme(p_wtTheme);
	Wt::WApplication::instance()->setTitle("Proyecto CQWt");

	/// Configuracion inicial del root
	wt_root = PageRoot;
	wt_root->setId("wt_root");
	wt_root->setStyleClass(Wt::WString::fromUTF8(""));
	wt_root->setHeight(WLength(100, WLength::Percentage));
	wt_root->setInline(0);

	///////////////////////////////////////////////////////////////
	/// ENTORNO: Se contruye de adentro hacia afuera
	///////////////////////////////////////////////////////////////
#ifdef MYTEST	
	/// Para escribir textos en los paneles
	const char *cell = "{1} panel"; 
	WText *item;
#endif
	/// Creo un contendor adicional interno full screen
	appContainer_ = new Wt::WContainerWidget(wt_root);
	appContainer_->setHeight(WLength("100%")); // ó (100, WLength::Percentage));

	///////////////// Interiores
	/// Panel Detalles
	Wt::WGridLayout *layoutDetalles = new Wt::WGridLayout();
	layoutDetalles->setRowResizable(0); // No cambia de tamaño externo

	//resultSetContainer_ = new Wt::WContainerWidget(appContainer_);
	resultSetsContainer_ = dynamic_cast <Wt::WContainerWidget*> (new Wt::WTabWidget(appContainer_));

	layoutDetalles->addWidget(resultSetsContainer_, 0, 0);

#ifdef MYTEST

#if 0
	/// Imprime el texto "Panel TABLE"
	resultSetContainer_->setStyleClass("green-box");
	item = new Wt::WText(Wt::WString(cell).arg("TABLE"));
	resultSetContainer_->addWidget(item);
#endif

	auto newTab = new Wt::WTemplateFormView ();

	resultSetsContainer_->setStyleClass("green-box");
	//item = new Wt::WText(Wt::WString(cell).arg("TABLE"));
	Wt::WString tab_text("tab1-form1");

	WTabWidget* tabWidget = dynamic_cast <WTabWidget*> (resultSetsContainer_);
	auto menu_for_tab = tabWidget->addTab(newTab, tab_text);
	recordTabsVec_.push_back(menu_for_tab);

#endif
	/// Panel Formularios

	recordFormContainer_ = new Wt::WContainerWidget(appContainer_);

	//	CHECK: the argument should be recordFormContainer_ OR appContainer_ ???
	//recordFormContainer_->addTab(new Wt::WContainerWidget(recordFormContainer_), Wt::WString ("tab1"));

	layoutDetalles->addWidget(recordFormContainer_, 1, 0);

#ifdef MYTEST
	/// Imprime el texto "Panel DETAILS" 	
	item = new Wt::WText(Wt::WString(cell).arg("DETAILS"));
	recordFormContainer_->setStyleClass("green-box");
	//recordFormContainer_->addWidget(item);
	//	CHECK: the argument should be recordFormContainer_ OR appContainer_ ???
	//recordFormContainer_->addTab(new Wt::WContainerWidget(recordFormContainer_), Wt::WString ("tab1"));
#endif
	///////////////// Interior (Izquierdo)
	Wt::WGridLayout *layoutInterior = new Wt::WGridLayout();
	layoutInterior->addLayout(layoutDetalles, 0, 1); ///< Coloco el detalle(tabla y formularios)
	layoutInterior->setColumnStretch(1, 1); ///< La segunda columna ocupa todo el espacio posible
	layoutInterior->setColumnResizable(0);
	/// Panel WorkSpace
	workSpaceContainer_ = new Wt::WContainerWidget(appContainer_);
	layoutInterior->addWidget(workSpaceContainer_, 0, 0);
#ifdef MYTEST
	/// Imprime el texto "Panel LEFT" 	
	item = new Wt::WText(Wt::WString(cell).arg("LEFT"));
	workSpaceContainer_->setStyleClass("green-box");
	workSpaceContainer_->addWidget(item);
#endif
	///////////////// Exteriores (Superior e Inferior)
	Wt::WGridLayout *layoutExterior = new Wt::WGridLayout();
	layoutExterior->addLayout(layoutInterior, 1, 0); // Coloco el centro
	layoutExterior->setRowStretch(1, 1);
	/// Panel Superior
	topPanelContainer_ = new Wt::WContainerWidget(appContainer_);
	layoutExterior->addWidget(topPanelContainer_, 0, 0);
#ifdef MYTEST
	/// Imprime el texto "Panel TOP" 	
	item = new Wt::WText(Wt::WString(cell).arg("TOP"));
	topPanelContainer_->addWidget(item);
	topPanelContainer_->setStyleClass("green-box");
#endif
	/// Panel inferior
	footerContainer_ = new Wt::WContainerWidget(appContainer_);
	layoutExterior->addWidget(footerContainer_, 2, 0);
#ifdef MYTEST
	/// Imprime el texto "Panel DOWN" 	
	item = new Wt::WText(Wt::WString(cell).arg("DOWN"));
	footerContainer_->setStyleClass("green-box");
	footerContainer_->addWidget(item);
#endif
	/// Ingresa el layout al container principal de la app
	appContainer_->setLayout(layoutExterior); 

	/// Metodos autogenerados por WtDesigner
	addAllStyleSheets();
	connectAllSignals();
	addAllJavaScripts();
}

void CQWtAppView2::addAllStyleSheets()
{
	Wt::WApplication::instance()->useStyleSheet(Wt::WLink("resources/main.css"));
}

void CQWtAppView2::addAllJavaScripts()
{
}

void CQWtAppView2::connectAllSignals()
{
}

CQWtAppView2::~CQWtAppView2()
{
	/// Al eliminar el Contendor exterior, se borran recursivamente todo lo interior
	delete appContainer_;		
}

// Gets
WContainerWidget* CQWtAppView2::appContainer()
{
	return appContainer_;
}

WContainerWidget* CQWtAppView2::topPanelContainer()
{
	return topPanelContainer_;
}

WContainerWidget* CQWtAppView2::workSpaceContainer()
{
	return workSpaceContainer_;
}

#if 0
WContainerWidget* CQWtAppView2::resultSetContainer()
{
	return resultSetContainer_;
}
#endif

WContainerWidget* CQWtAppView2::resultSetsContainer()
{
	return resultSetsContainer_;
}

WContainerWidget* CQWtAppView2::recordFormsContainer()
{
	return recordFormContainer_;
}

WContainerWidget* CQWtAppView2::footerContainer()
{
	return footerContainer_;
}
