// CQWtApp.h

#ifndef CQWTAPP_H
#define CQWTAPP_H

#include "CQWtAppView.h"
#include "ObserverGoF.h"
#include "WorkSpaceController.h"
#include "ResultSetController.h"
#include "ResultSet2Controller.h"

/// Definición de la clase CQWtApplication, responsable del control de la aplicación.
/// Se comporta como un Observer (GoF) y un MVC
/// Contiene una grilla de 4x2 dentro de la cual hay las siguientes Controladoras:
/// Cabecera(TopPanel): Contiene wigted para barra superior y menu principal
/// Arbol(WorkSpace): Contiene los elementos del workspace de ClearQuest
/// Tabla(ResultSetTable): Contenedor (GoF) de tablas de resultados, cada una asociada a un Modelo de datos
/// Formulario (RecordForm): Contendor (GoF) de formularios abiertos, cada formulario se comporta como Flyweigh (GoF)
/// Pie (Footer): Muestra información y status, se comporta como Cadena de Responsabilidad (GoF)
/// Cada Controladora tiene asociada una vista que se comporta como Factory-Method (GoF) y un modelo de datos
//
class CQWtApplication : public Wt::WApplication, public ObserverGoF
{
public:
	CQWtApplication(const Wt::WEnvironment& env);
	~CQWtApplication();

	/// Llamado desde un sujeto que cambia (Patron Observer-GoF)
	void update(SubjectGoF* s);

protected:
	/// Vista principal, configurada como grilla de Widgets
	CQWtAppView* mainView;
	WorkSpaceController* workSpaceCtrl;
#if ! defined (USE_RESULTSET2)
	ResultSetController* resultSetCtrl;
#else
	ResultSet2Controller* resultSetCtrl;
#endif

private:
	/// Establece los archivos de recursos a utilizar
	void setResources(); 
};

#endif // CQWTAPP_H