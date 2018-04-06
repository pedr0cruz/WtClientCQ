#ifndef CQWTAPPVIEW2_H 
#define CQWTAPPVIEW2_H

#include <Wt/WApplication>
#include <Wt/WFileResource>
#include <Wt/WContainerWidget>
#include <Wt/WBootstrapTheme>
#include <Wt/WBorderLayout>
#include <Wt/WText>
#include <Wt/WLength>

/// definicion que incluye lineas para probar la clase
#define MYTEST 

using namespace Wt;

///	CQWtAppView: clase que implementa la vista de la aplicacion.
///	CQWtAppView recibe en formato JSON los datos y se ocupa hacer
/// el rendering de dichos datos. Se va a cambiar para usar los
/// widgets de WT, algo que no se ha logrado todavia.
class CQWtAppView2
{
protected: 
	WContainerWidget	*wt_root,				///< Widget raiz
						*appContainer_,			///< Contenedor exterior
						*topPanelContainer_,	///< Contenedor del panel superior
						*workSpaceContainer_;	///< Contenedor del arbol izquierdo

	WContainerWidget	*resultSetsContainer_;	///< Contenedor de la tabla de resultados

	WContainerWidget	*recordFormContainer_,	///< Contenedor de los formularios
						*footerContainer_;		///< Contendor del pie de pagina

	std::vector <Wt::WMenuItem *> recordTabsVec_;
	std::vector <Wt::WMenuItem *> resultsetTabsVec_;

public:
	/// Constructor: crea toda la vista exterior de la App
	CQWtAppView2(Wt::WContainerWidget *PageRoot);

	void addAllStyleSheets();
	void addAllJavaScripts();
	void connectAllSignals();

	~CQWtAppView2();

	// Gets
	WContainerWidget* appContainer();
	WContainerWidget* topPanelContainer();
	WContainerWidget* workSpaceContainer();

	WContainerWidget* resultSetsContainer();

	WContainerWidget* recordFormsContainer();
	WContainerWidget* footerContainer();
};

#endif /// CQWTAPPVIEW2_H
