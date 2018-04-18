//  CQWtApp.cpp
//

#include "stdafx.h"

//  Movido a stdafx.h
//#include "CQWtApp.h"

#include <Wt/WBootstrapTheme>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <boost/filesystem.hpp>

/// Application class Constructor  
CQWtApplication::CQWtApplication(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
	/// Inicializa recursos
	setResources();
	/// Prepara la interface de usuario
	mainView = new CQWtAppView(root()); ///< Crea toda la estructura de la app

	/// Aqui debe inicializar el singleton de CQ

	/// Crea la controladora del WorkSpace
	workSpaceCtrl = new WorkSpaceController("WorkSpaceCtrl");
	workSpaceCtrl->createView(mainView->workSpaceContainer()); ///< Indica en que vista trabajará
	workSpaceCtrl->attach(this); ///< GoF: conecta sujeto con Observador
	//workSpaceCtrl->attach(std::shared_ptr <ObserverGoF> (this)); ///< GoF: conecta sujeto con Observador

    //resultSetCtrl->createView(mainView->resultSetTabsContainer()); ///< Indica en que vista trabajará
	//resultSetCtrl->attach(this); ///< GoF: conecta sujeto con Observador
    //resultSetCtrl->attach(std::shared_ptr <ObserverGoF>(this)); ///< GoF: conecta sujeto con Observador
    /// Crea la controladora de los ResultSets
    resultSetsCtrl = new ResultSetsController("ResultSetsCtrl");
    resultSetsCtrl->createView(mainView->resultSetsTabsContainer()); ///< Indica en que vista trabajará
    //resultSetsCtrl->attach(std::shared_ptr <ObserverGoF>(this)); ///< GoF: conecta sujeto con Observador
    resultSetsCtrl->attach(this); ///< GoF: conecta sujeto con Observador

	/// Crea la controladora del RecordSet
	//recordSetCtrl = new RecordSetController("RecordSetCtrl");
	//recordSetCtrl->createView(mainView->workSpaceContainer()); ///< Indica en que vista trabajará
    //recordSetCtrl->createView(mainView->recordSetTabsContainer()); ///< Indica en que vista trabajará
    recordSetsCtrl = new RecordSetsController("RecordSetsCtrl");
    recordSetsCtrl->createView(mainView->recordSetsTabsContainer()); ///< Indica en que vista trabajará

	//workSpaceCtrl->attach(this); ///< GoF: conecta sujeto con Observador
	//workSpaceCtrl->attach(std::shared_ptr <ObserverGoF>(this)); ///< GoF: conecta sujeto con Observador

	///	internalPathChanged().connect(this, &CQWtApplication::handlePathChange);
	refresh(); ///< recargar todos los elementos incluyendo los bundles
}

// Update: Llamado desde un sujeto que cambia (Patron Observer-GoF)
void CQWtApplication::update(SubjectGoF* aController)
{
	/// Como Observador, recibe notificaciones de los diferentes Sujetos (Controladoras)
	/// Evento en el WorkSpace
    const std::string subjectName(aController->subjectName());
    if (subjectName == "WorkSpaceCtrl"){
		//WorkSpaceController *ws = (WorkSpaceController*)aController;
        //WorkSpaceController* ws = reinterpret_cast <decltype (ws)> (aController);
        //std::shared_ptr <WorkSpaceController> ws = std::shared_ptr <WorkSpaceController> (
        //  reinterpret_cast <WorkSpaceController*> (aController)
        //);
        WorkSpaceController* ws = reinterpret_cast <decltype (ws)> (aController);
        //	TODO FIXME HACK
//		resultSetCtrl->recordChanged(ws->selectedItem());
        string selectedItem(ws->selectedItem());
        resultSetsCtrl->newController(selectedItem);
    }
}

CQWtApplication::~CQWtApplication()
{
	delete mainView;
}

void CQWtApplication::setResources()
{
	/// Archivos de recursos a utilizar en toda la app
	messageResourceBundle().use("resources/forms");
	messageResourceBundle().use("resources/configFile");
	//messageResourceBundle().use(WApplication::appRoot() + "about"); // otra opcion, probar
	setTwoPhaseRenderingThreshold(0); ///< Establece two-phase rendering para JavaScript		
	refresh(); ///< recargar todos los elementos incluyendo los bundles
}