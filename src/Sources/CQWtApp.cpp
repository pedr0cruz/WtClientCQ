//  CQWtApp.cpp

#include "stdafx.h"

//  Movido a stdafx.h
//#include "CQWtApp.h"

#include <Wt/WBootstrapTheme>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <boost/filesystem.hpp>

#include <string>

using std::string;
using namespace Wt;

// Application class Constructor  
CQWtApplication::CQWtApplication(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
	// Inicializa recursos
	setResources();
	// Prepara la interface de usuario, crea toda la estructura de la app
    mainView = new CQWtAppView(root());

	// Aqui debe inicializar el singleton de CQ

	// Crea la controladora del WorkSpace
	workSpaceCtrl = new WorkSpaceController("WorkSpaceCtrl");
    // Indica en que vista trabajará
    workSpaceCtrl->createView(mainView->workSpaceContainer());
    // GoF: conecta sujeto con Observador
	workSpaceCtrl->attach(this);

    // Crea la controladora de los ResultSets
    resultSetsCtrl = new ResultSetsController("ResultSetsCtrl");
    // Indica en que vista trabajará
    resultSetsCtrl->createView(mainView->resultSetsViewContainer());
    // GoF: conecta sujeto con Observador
    resultSetsCtrl->attach(this);

	// Crea la controladora del RecordSet
    recordSetsCtrl = new RecordSetsController("RecordSetsCtrl");
    // Indica en que vista trabajará
    recordSetsCtrl->createView(mainView->recordSetsViewContainer());

    // FIX / HACK / PENDIENTE / REVISAR
	// internalPathChanged().connect(this, &CQWtApplication::handlePathChange);

    // recargar todos los elementos incluyendo los bundles
	refresh();
}

// Update: Llamado desde un sujeto que cambia (Patron Observer-GoF)
void CQWtApplication::update(SubjectGoF* aController)
{
	// Como Observador, recibe notificaciones de los diferentes Sujetos (Controladoras)
	// Evento en el WorkSpace
    const std::string subjectName(aController->subjectName());
    if (subjectName == "WorkSpaceCtrl"){
        WorkSpaceController* ws = dynamic_cast <decltype (ws)> (aController);
        //	TODO FIXME HACK
//		resultSetCtrl->recordChanged(ws->selectedItem());
        string tabName(ws->selectedItem());
        resultSetsCtrl->getNewControllerIfNeeded(tabName);
    }
}

CQWtApplication::~CQWtApplication()
{
	delete mainView;
}

void CQWtApplication::setResources()
{
	// Archivos de recursos a utilizar en toda la app
	messageResourceBundle().use("resources/forms");
	messageResourceBundle().use("resources/configFile");
    // otra opcion, probar
    //messageResourceBundle().use(WApplication::appRoot() + "about");
    // Establece two-phase rendering para JavaScript		
    setTwoPhaseRenderingThreshold(0);
    // recargar todos los elementos incluyendo los bundles
	refresh();
}
