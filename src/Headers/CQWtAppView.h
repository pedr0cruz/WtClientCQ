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

//using std::vector;

/// definicion que incluye lineas para probar la clase
#define MYTEST 

//using namespace Wt;

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
                            *resultSetsTabsContainer_,  ///< Contenedor con pestañas para las tablas de resultados
                            *recordSetsTabsContainer_,  ///< Contenedor con pestañas para los formularios
                            *footerContainer_;          ///< Contenedor del pie de pagina
    Wt::WTabWidget  *resultSetsTabWidget_,   ///< Widget con las pestañas para las tablas de resultados
                    *recordSetsTabWidget_;   ///< Widget con las pestañas para los formularios

    //< Vector con punteros a tablas WTableViews que van dentro de resultSetTabsContainer_
    //vector <Wt::WTableView>         resultSetTablesVec_;
    //< Vector con punteros a formularios WTemplateFormView que van dentro de recordSetTabsContainer_
    //vector <Wt::WTemplateFormView>  recordSetFormsVec_;

public:
	/// Constructor: crea toda la vista exterior de la App
	CQWtAppView(Wt::WContainerWidget* PageRoot)
    {
        /// Crea tema basado en bootstrap
        Wt::WBootstrapTheme* p_wtTheme = new Wt::WBootstrapTheme();
		p_wtTheme->setVersion(Wt::WBootstrapTheme::Version3);
		Wt::WApplication::instance()->setTheme(p_wtTheme);
		Wt::WApplication::instance()->setTitle("Proyecto CQWt");

		/// Configuracion inicial del root
		wt_root = PageRoot;
		wt_root->setId("wt_root");
		wt_root->setStyleClass(Wt::WString::fromUTF8(""));
        wt_root->setHeight(Wt::WLength(100, Wt::WLength::Percentage));
		wt_root->setInline(0);

		///////////////////////////////////////////////////////////////
		/// ENTORNO: Se contruye de adentro hacia afuera
		///////////////////////////////////////////////////////////////

#ifdef MYTEST	
		/// Para escribir textos en los paneles
		const char *cell = "{1} panel"; 
        Wt::WText *item;
#endif

		/// Se crea contenedor adicional interno a pantalla completa
		appContainer_ = new Wt::WContainerWidget(wt_root);
		appContainer_->setHeight(Wt::WLength("100%")); // ó (100, WLength::Percentage));

		///////////////// Paneles Interiores

		/// Panel Detalles
		Wt::WGridLayout *layoutDetalles = new Wt::WGridLayout();
        /// No cambia de tamaño externo
		layoutDetalles->setRowResizable(0);

        /// Crea el contenedor del control de pestañas del panel superior
        resultSetsTabsContainer_ = new Wt::WContainerWidget(appContainer_);
        /// Crea el control de pestañas del panel superior
        resultSetsTabWidget_ = new Wt::WTabWidget(resultSetsTabsContainer_);
        /// Agrega el control de pestañas al contenedor de detalles
        layoutDetalles->addWidget(resultSetsTabWidget_, 0, 0);

#ifdef MYTEST
		/// Imprime el texto "Panel TABLE"
        resultSetsTabWidget_->setStyleClass("green-box");
		item = new Wt::WText(Wt::WString(cell).arg("TABLE"));
        Wt::WString text("aaa");
        Wt::WMenuItem* menuItem = resultSetsTabWidget_->addTab(dynamic_cast<Wt::WWidget*> (item), text);
#endif

		/// Panel Formularios

		//recordFormContainer_ = new Wt::WContainerWidget(appContainer_);
        //aaa
        //tabsContainer_ = new Wt::WTabWidget(appContainer_);
        //recordSetTabsContainer_ = dynamic_cast <Wt::WContainerWidget*> (tabsContainer_);
        //layoutDetalles->addWidget(recordSetTabsContainer_, 1, 0);

        recordSetsTabsContainer_ = new Wt::WContainerWidget(appContainer_);
        recordSetsTabWidget_ = new Wt::WTabWidget(recordSetsTabsContainer_);

#ifdef MYTEST
        recordSetsTabWidget_->setStyleClass("green-box");
        auto item2 = new Wt::WText("zzz");
        Wt::WString text2("aaa");
        Wt::WMenuItem* menuItem2 = recordSetsTabWidget_->addTab(dynamic_cast<Wt::WWidget*> (item2), text2);
#endif

        layoutDetalles->addWidget(recordSetsTabsContainer_, 1, 0);

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

        /// Layout exterior
		Wt::WGridLayout *layoutExterior = new Wt::WGridLayout();
        /// Coloco el centro
        layoutExterior->addLayout(layoutInterior, 1, 0);
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

		/// Métodos autogenerados por WtDesigner

		addAllStyleSheets();
		connectAllSignals();
		addAllJavaScripts();
	}

	void addAllStyleSheets()
	{
		Wt::WApplication::instance()->useStyleSheet(Wt::WLink("resources/main.css"));
	}

	void addAllJavaScripts()
	{
	}

	void connectAllSignals()
	{
	}

	~CQWtAppView()
	{
		/// Al eliminar el Contenedor exterior, se borran recursivamente todos los contenedores interiores
		delete appContainer_;		
	}
	// Gets
    /*
	std::shared_ptr <WContainerWidget> appContainer() { return appContainer_; }
	std::shared_ptr <WContainerWidget> topPanelContainer() { return topPanelContainer_; }
	std::shared_ptr <WContainerWidget> workSpaceContainer(){ return workSpaceContainer_; }
	std::shared_ptr <WContainerWidget> resultSetContainer() { return resultSetContainer_; }
	std::shared_ptr <WContainerWidget> recordFormContainer() { return recordFormContainer_; }
	std::shared_ptr <WContainerWidget> footerContainer() { return footerContainer_; }
    */
    Wt::WContainerWidget* appContainer() { return appContainer_; }
    Wt::WContainerWidget* topPanelContainer() { return topPanelContainer_; }
    Wt::WContainerWidget* workSpaceContainer() { return workSpaceContainer_; }
    //Wt::WContainerWidget* resultSetContainer() { return resultSetContainer_; }
    //Wt::WContainerWidget* recordFormContainer() { return recordFormContainer_; }

    Wt::WContainerWidget* resultSetsTabsContainer() { return resultSetsTabsContainer_; }
    Wt::WContainerWidget* recordSetsTabsContainer() { return recordSetsTabsContainer_; }

    Wt::WContainerWidget* footerContainer() { return footerContainer_; }

    Wt::WTabWidget* resultSetsTabWidget() { return resultSetsTabWidget_; }
    Wt::WTabWidget* recordSetsTabWidget() { return recordSetsTabWidget_; }
};

#endif /// CQWTAPPVIEW_H