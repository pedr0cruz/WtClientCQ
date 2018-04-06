#ifndef RESULTSETS_CTRL_H
#define RESULTSETS_CTRL_H

#include <Wt/WObject>
#include <Wt/WTabWidget>
#include <Wt/WTableView>

#include "ObserverGoF.h"

class ResultSetsModel;
class ResultSetsView;
class ResultSet2Controller;

///	Esta clase funciona como contenedor para todas las tuplas MVC. Además, 
/// incluye un puntero al Widget contenedor con las pestañas. Cada tupla
/// MVC funciona de manera independiente con su propio controlador, modelo
/// y vista.
class ResultSetsController : public Wt::WObject, public SubjectGoF
{
public:
    /// Constructor
    //ResultSetsController(Wt::WContainerWidget* tabWidgetParent);
    ResultSetsController(const std::string & parent);

    /// Crea la vista
    Wt::WContainerWidget* createView(Wt::WContainerWidget* recParentContainer);

    /// Crea un nuevo controlador para una nueva pestaña
    ResultSet2Controller* newController(const string & name);

    /// Evento que ocurre al cambiar la pestaña activa
    void tabChanged(string s);
    //EventSignal<WScrollEvent>& scrolled();

    /// Slot para seleccion de nuevo item
    //string selectedTab() { return selectedTab_; }
    //int currentTabIndex() { return currentTabIndex_; }

    /// Destructor
    ~ResultSetsController();

protected:
    /// Modelo asociado a este controlador
    ResultSetsModel* model_;
    /// Vista asociada a este controlador
    ResultSetsView* view_;
    Wt::WTabWidget* rssTabWidget_;
    Wt::WContainerWidget* rssTabWidgetContainer_;

    /// Mapa de indices (enteros) a controladores (uno por pestaña)
    typedef std::map<int, ResultSet2Controller*> ControllersMap;
    ControllersMap controllersMap_;
};

#endif /// RESULTSETS_CTRL_H
