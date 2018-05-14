///  RecordSetsController.h

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

///	Esta clase funciona como contenedor para todas las tuplas MVC. Además, incluye 
/// un puntero al Widget contenedor con las pestañas. Cada tupla MVC funciona de 
/// manera independiente con su propio controlador, modelo y vista.
class RecordSetsController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
    /// @param name const std::string & Identifica el sujeto que notifica que hubo cambios
    RecordSetsController(const std::string & name);

    /// Crea la vista
    /// @param container Wt::WContainerWidget* Puntero a objeto contenedor
    /// @return Wt::WWidget* Puntero a vista (objeto derivado de contenedor Wt::WWidget)
    Wt::WWidget* createView(Wt::WContainerWidget* container);

    /// Crea un nuevo controlador para una nueva pestaña
    /// @param name Nombre asociado al controlador a crear
    /// @return RecordSetController* Puntero a controlador con el nombre especificado
    RecordSetController* newController(const std::string & name);

    /// Evento que ocurre al cambiar la pestaña activa
    /// @param currentTab int indice de pestaña activada
    void tabChanged(int currentTab);

	/// Destructor
	~RecordSetsController();

protected:
    /// Modelo asociado a este controlador
    RecordSetsModel* model_;
    /// Vista asociada a este controlador
    RecordSetsView* view_;

    ///  DATOS ESPECÍFICOS de cada controlador

    /// Mapa de indices (enteros) a controladores (uno por pestaña)
    typedef std::map<int, RecordSetController*> ControllersMap;
    ControllersMap controllersMap_;

    /// FIN de DATOS ESPECÍFICOS de cada controlador
};

#endif /// RECORDSETS_CTRL_H
