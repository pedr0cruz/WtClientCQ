#ifndef CQWTAPPVIEW_H 
#define CQWTAPPVIEW_H

#include <Wt/WApplication>
#include <Wt/WFileResource>
#include <Wt/WContainerWidget>
#include <Wt/WBootstrapTheme>
#include <Wt/WBorderLayout>
#include <Wt/WText>
#include <Wt/WLength>

#define MYTEST // con esta directiva agrega lineas para probar la clase

using namespace Wt;

class CQWtAppView
{
protected: 
	WContainerWidget	*wt_root,				// Widget raiz
						*appContainer_,			// Contendor exterior
						*topPanelContainer_,	// Contenedor del panel superior
						*workSpaceContainer_,	// Contenedor del arbol izquierdo
						*resultSetContainer_,	// Contenedor de la tabla de resultados
						*recordFormContainer_,	// Contenedor de los formularios
						*footerContainer_;		// Contendor del pie de pagina
public:
	// Constructor: crea toda la vista exterior de la App
	CQWtAppView(Wt::WContainerWidget *PageRoot)
	{
		Wt::WBootstrapTheme * p_wtTheme = new Wt::WBootstrapTheme();
		p_wtTheme->setVersion(Wt::WBootstrapTheme::Version3);
		Wt::WApplication::instance()->setTheme(p_wtTheme);
		Wt::WApplication::instance()->setTitle("Proyecto CQWt");

		// Configuracion inicial del root
		wt_root = (PageRoot);
		wt_root->setId("wt_root");
		wt_root->setStyleClass(Wt::WString::fromUTF8(""));
		wt_root->setHeight(WLength(100, WLength::Percentage));
		wt_root->setInline(0);

		///////////////////////////////////////////////////////////////
		// ENTORNO: Se contruye de adentro hacia afuera
		///////////////////////////////////////////////////////////////
#ifdef MYTEST	// Para escribir textos en los paneles
		const char *cell = "{1} panel"; 
		WText *item;
#endif
		// Creo un contendor adicional interno full screen
		appContainer_ = new Wt::WContainerWidget(wt_root);
		appContainer_->setHeight(WLength("100%")); // ó (100, WLength::Percentage));

		///////////////// Interiores
		// Panel Detalles
		Wt::WGridLayout *layoutDetalles = new Wt::WGridLayout();
		layoutDetalles->setRowResizable(0); // No cambia de tamaño externo
		resultSetContainer_ = new Wt::WContainerWidget(appContainer_);
		layoutDetalles->addWidget(resultSetContainer_, 0, 0);
#ifdef _MYTEST	// Imprime el texto "Panel TABLE"
		resultSetContainer_->setStyleClass("green-box");
		item = new Wt::WText(Wt::WString(cell).arg("TABLE"));
		resultSetContainer_->addWidget(item);
#endif
		// Panel Formularios
		recordFormContainer_ = new Wt::WContainerWidget(appContainer_);
		layoutDetalles->addWidget(recordFormContainer_, 1, 0);
#ifdef MYTEST	// Imprime el texto "Panel DETAILS" 	
		item = new Wt::WText(Wt::WString(cell).arg("DETAILS"));
		recordFormContainer_->setStyleClass("green-box");
		recordFormContainer_->addWidget(item);
#endif
		///////////////// Interior (Izquierdo)
		Wt::WGridLayout *layoutInterior = new Wt::WGridLayout();
		layoutInterior->addLayout(layoutDetalles, 0, 1); // Coloco el detalle(tabla y formularios)
		layoutInterior->setColumnStretch(1, 1); // La segunda columna ocupa todo el espacio posible
		layoutInterior->setColumnResizable(0);
		// Panel WorkSpace
		workSpaceContainer_ = new Wt::WContainerWidget(appContainer_);
		layoutInterior->addWidget(workSpaceContainer_, 0, 0);
#ifdef _MYTEST	// Imprime el texto "Panel LEFT" 	
		item = new Wt::WText(Wt::WString(cell).arg("LEFT"));
		workSpaceContainer_->setStyleClass("green-box");
		workSpaceContainer_->addWidget(item);
#endif
		///////////////// Exteriores (Superior e Inferior)
		Wt::WGridLayout *layoutExterior = new Wt::WGridLayout();
		layoutExterior->addLayout(layoutInterior, 1, 0); // Coloco el centro
		layoutExterior->setRowStretch(1, 1);
		// Panel Superior
		topPanelContainer_ = new Wt::WContainerWidget(appContainer_);
		layoutExterior->addWidget(topPanelContainer_, 0, 0);
#ifdef MYTEST	// Imprime el texto "Panel TOP" 	
		item = new Wt::WText(Wt::WString(cell).arg("TOP"));
		topPanelContainer_->addWidget(item);
		topPanelContainer_->setStyleClass("green-box");
#endif
		// Panel inferior
		footerContainer_ = new Wt::WContainerWidget(appContainer_);
		layoutExterior->addWidget(footerContainer_, 2, 0);
#ifdef MYTEST	// Imprime el texto "Panel DOWN" 	
		item = new Wt::WText(Wt::WString(cell).arg("DOWN"));
		footerContainer_->setStyleClass("green-box");
		footerContainer_->addWidget(item);
#endif
		// Ingresa el layout al container principal de la app
		appContainer_->setLayout(layoutExterior); 

		// Metodos autogenerados por WtDesigner
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
		// Al eliminar el Contendor exterior, se borran recursivamente todo lo interior
		delete appContainer_;		
	}
	// Gets
	WContainerWidget* appContainer() {	return appContainer_;	}
	WContainerWidget* topPanelContainer() { return topPanelContainer_; }
	WContainerWidget* workSpaceContainer(){ return workSpaceContainer_; }
	WContainerWidget* resultSetContainer() { return resultSetContainer_; }
	WContainerWidget* recordFormContainer() { return recordFormContainer_; }
	WContainerWidget* footerContainer() { return footerContainer_; }
};

#endif // CQWTAPPVIEW_H