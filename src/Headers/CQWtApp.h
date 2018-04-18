/// CQWtApp.h

#ifndef CQWTAPP_H
#define CQWTAPP_H

#pragma once

#include "CQWtAppView.h"
#include "ObserverGoF.h"
#include "WorkSpaceController.h"

#include "RecordSetController.h"
#include "RecordSetsController.h"

#include "ResultSetController.h"
#include "ResultSetsController.h"

/// Definici�n de la clase CQWtApplication, responsable del control de la aplicaci�n.
/// Se comporta como un Observer (GoF) y un MVC
/// Contiene una grilla de 4x2 dentro de la cual hay las siguientes Controladoras:
/// Cabecera(TopPanel): Contiene wigted para barra superior y menu principal
/// Arbol(WorkSpace): Contiene los elementos del workspace de ClearQuest
/// Tabla(ResultSetTable): Contenedor (GoF) de tablas de resultados, cada una asociada a un Modelo de datos
/// Formulario (RecordForm): Contendor (GoF) de formularios abiertos, cada formulario se comporta como Flyweigh (GoF)
/// Pie (Footer): Muestra informaci�n y status, se comporta como Cadena de Responsabilidad (GoF)
/// Cada Controladora tiene asociada una vista que se comporta como Factory-Method (GoF) y un modelo de datos
//
class CQWtApplication : public Wt::WApplication, public ObserverGoF
{
public:
    /// Constructor 
	CQWtApplication(const Wt::WEnvironment& env);
    /// Destructor
    virtual ~CQWtApplication();

	/// Llamado desde un sujeto que cambia (Patron Observer-GoF)
	void update(SubjectGoF* s);

protected:

	/// Vista principal, configurada como grilla de Widgets
	CQWtAppView* mainView;

	/// Controlador de panel izquierdo
	WorkSpaceController* workSpaceCtrl;

    /// Controlador de panel superior
    ResultSetsController* resultSetsCtrl;

    /// Controlador de panel inferior
    RecordSetsController* recordSetsCtrl;

private:
	/// Establece los archivos de recursos a utilizar
	void setResources(); 
};

#endif // CQWTAPP_H
