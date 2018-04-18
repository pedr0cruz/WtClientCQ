#ifndef RECORDSETS_CTRL_H
#define RECORDSETS_CTRL_H

#include <Wt/WObject>
#include <Wt/WTabWidget>
#include <Wt/WTemplateFormView>

#include <map>
#include <string>

#include "ObserverGoF.h"

class RecordSetsModel;
class RecordSetsView;
class RecordSetController;

///	Esta clase funciona como contenedor para todas las tuplas MVC. Además, 
/// incluye un puntero al Widget contenedor con las pestañas. Cada tupla
/// MVC funciona de manera independiente con su propio controlador, modelo
/// y vista.
class RecordSetsController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
    //RecordSetsController(Wt::WContainerWidget* tabWidgetParent);
    RecordSetsController(const std::string & parent);

    /// Crea la vista
    Wt::WWidget* createView(Wt::WContainerWidget* rssParentContainer);

    /// Crea un nuevo controlador para una nueva pestaña
    RecordSetController* newController(const string & name);

    /// Evento que ocurre al cambiar la pestaña activa
	void tabChanged(int currentTab);

	/// Destructor
	~RecordSetsController();

protected:
    /// Modelo asociado a este controlador
    RecordSetsModel* model_;
    /// Vista asociada a este controlador
    RecordSetsView* view_;

    /// Mapa de indices (enteros) a controladores (uno por pestaña)
    typedef std::map<int, RecordSetController*> ControllersMap;
    ControllersMap controllersMap_;
};

#endif /// RECORDSETS_CTRL_H
