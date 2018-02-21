#include "CQWtApp.h"

#include <Wt/WBootstrapTheme>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <boost/filesystem.hpp>

// Constructor  
CQWtApplication::CQWtApplication(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
	// Inicializa recursos
	setResources();
	// Prepara la interface de usuario
	mainView = new CQWtAppView(root()); // Crea toda la estructura de la app

	// Aqui debe inicializar el singelton de CQ

	// Crea la controladora del WorkSpace
	workSpaceCtrl = new WorkSpaceController("WorkSpaceCtrl");
	workSpaceCtrl->createView(mainView->workSpaceContainer()); // Indica en que vista trabajará
	workSpaceCtrl->attach(this); // GoF: conecta sujeto con Observador

	resultSetCtrl = new ResultSetController("ResultSetCtrl");
	resultSetCtrl->createView(mainView->resultSetContainer()); // Indica en que vista trabajará
	resultSetCtrl->attach(this); // GoF: conecta sujeto con Observador

	//	internalPathChanged().connect(this, &CQWtApplication::handlePathChange);
	refresh(); // recargar todos los elementos incluyendo los bundles

}

// Update: Llamado desde un sujeto que cambia (Patron Observer-GoF)
void CQWtApplication::update(SubjectGoF* aController)
{
	// Como Observador, recibe notificaciones de los diferentes Sujetos (Controladoras)
	// Evento en el WorkSpace
	if (aController->subjectName() == "WorkSpaceCtrl" ){
		WorkSpaceController *ws = (WorkSpaceController*)aController;
		resultSetCtrl->recordChanged( ws->selectedItem() );
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
	//messageResourceBundle().use(WApplication::appRoot() + "about"); // otra opcion, probar
	setTwoPhaseRenderingThreshold(0); // Establece two-phase rendering para JavaScript		
	refresh(); // recargar todos los elementos incluyendo los bundles
}