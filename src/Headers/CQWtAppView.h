#ifndef CQWTAPPVIEW_H 
#define CQWTAPPVIEW_H

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

using std::vector;

/// definicion que incluye lineas para probar la clase
#define MYTEST 

using namespace Wt;

///	CQWtAppView: clase que implementa la vista de la aplicacion.
///	CQWtAppView recibe en formato JSON los datos y se ocupa hacer
/// el rendering de dichos datos. Se va a cambiar para usar los
/// widgets de WT, algo que no se ha logrado todavia.
class CQWtAppView
{
protected:
    WContainerWidget    *wt_root,				    ///< Widget raiz
                        *appContainer_,			    ///< Contendor exterior
                        *topPanelContainer_,	    ///< Contenedor del panel superior
                        *workSpaceContainer_,       ///< Contenedor del arbol izquierdo
                        *resultSetsTabsContainer_,  ///< Contenedor con pestañas para las tablas de resultados
                        *recordSetsTabsContainer_,  ///< Contenedor con pestañas para los formularios
                        *footerContainer_;          ///< Contenedor del pie de pagina
    /*
    WContainerWidget    *wt_root,				    ///< Widget raiz
        *appContainer_,			    ///< Contendor exterior
        *topPanelContainer_,	    ///< Contenedor del panel superior
        *workSpaceContainer_;       ///< Contenedor del arbol izquierdo
    WTabWidget  *resultSetTabsContainer_,   ///< Contenedor con pestañas para las tablas de resultados
                *recordSetTabsContainer_;   ///< Contenedor con pestañas para los formularios
    WContainerWidget    *footerContainer_;          ///< Contenedor del pie de pagina
    */
    WTabWidget  *resultSetsTabWidget_,   ///< Widget con las pestañas para las tablas de resultados
                *recordSetsTabWidget_;   ///< Widget con las pestañas para los formularios

    ///< Vector con punteros a tablas WTableViews que van dentro de resultSetTabsContainer_
    //vector <Wt::WTableView>         resultSetTablesVec_;
    ///< Vector con punteros a formularios WTemplateFormView que van dentro de recordSetTabsContainer_
    //vector <Wt::WTemplateFormView>  recordSetFormsVec_;
/*
        std::shared_ptr < WContainerWidget > wt_root;				///< Widget raiz
        std::shared_ptr < WContainerWidget > appContainer_;			///< Contendor exterior
        std::shared_ptr < WContainerWidget > topPanelContainer_;	///< Contenedor del panel superior
        std::shared_ptr < WContainerWidget > workSpaceContainer_;	///< Contenedor del arbol izquierdo
        std::shared_ptr < WContainerWidget > resultSetContainer_;	///< Contenedor de la tabla de resultados
        std::shared_ptr < WContainerWidget > recordFormContainer_;	///< Contenedor de los formulario
*/
public:
	/// Constructor: crea toda la vista exterior de la App
	CQWtAppView(Wt::WContainerWidget* PageRoot)
    //CQWtAppView(std::shared_ptr <Wt::WContainerWidget> PageRoot)
    {
        Wt::WBootstrapTheme* p_wtTheme = new Wt::WBootstrapTheme();
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
		/// Se crea contenedor adicional interno a pantalla completa
		appContainer_ = new Wt::WContainerWidget(wt_root);
		appContainer_->setHeight(WLength("100%")); // ó (100, WLength::Percentage));

		///////////////// Interiores

		/// Panel Detalles

		Wt::WGridLayout *layoutDetalles = new Wt::WGridLayout();
		layoutDetalles->setRowResizable(0); // No cambia de tamaño externo
        resultSetsTabsContainer_ = new Wt::WContainerWidget(appContainer_);
        resultSetsTabWidget_ = new Wt::WTabWidget(resultSetsTabsContainer_);
        layoutDetalles->addWidget(resultSetsTabWidget_, 0, 0);

#ifdef MYTEST
		/// Imprime el texto "Panel TABLE"
		//resultSetContainer_->setStyleClass("green-box");
        resultSetsTabWidget_->setStyleClass("green-box");
		item = new Wt::WText(Wt::WString(cell).arg("TABLE"));
        Wt::WString text("aaa");
        Wt::WMenuItem* menuItem = resultSetsTabWidget_->addTab(dynamic_cast<Wt::WWidget*> (item), text);
        //resultSetTabsContainer_->addWidget(item);
#endif

		/// Panel Formularios

		//recordFormContainer_ = new Wt::WContainerWidget(appContainer_);
        //aaa
        //tabsContainer_ = new Wt::WTabWidget(appContainer_);
        //recordSetTabsContainer_ = dynamic_cast <Wt::WContainerWidget*> (tabsContainer_);
        //layoutDetalles->addWidget(recordSetTabsContainer_, 1, 0);

#ifdef MYTEST
		/// Imprime el texto "Panel DETAILS" 	
        //aaa
		//item = new Wt::WText(Wt::WString(cell).arg("DETAILS"));
        //recordSetTabsContainer_->setStyleClass("green-box");
        //recordSetTabsContainer_->addWidget(item);
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
		/// Al eliminar el Contendor exterior, se borran recursivamente todo lo interior
		//delete appContainer_;		
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
    WContainerWidget* appContainer() { return appContainer_; }
    WContainerWidget* topPanelContainer() { return topPanelContainer_; }
    WContainerWidget* workSpaceContainer(){ return workSpaceContainer_; }
    //WContainerWidget* resultSetContainer() { return resultSetContainer_; }
    //WContainerWidget* recordFormContainer() { return recordFormContainer_; }

    WContainerWidget* resultSetsTabsContainer() { return resultSetsTabsContainer_; }
    WContainerWidget* recordSetsTabsContainer() { return recordSetsTabsContainer_; }

    WContainerWidget* footerContainer() { return footerContainer_; }

    WTabWidget* resultSetsTabWidget() { return resultSetsTabWidget_; }
    WTabWidget* recordSetsTabWidget() { return recordSetsTabWidget_; }
};

#endif /// CQWTAPPVIEW_H