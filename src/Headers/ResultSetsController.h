//  ResultSetsController

#ifndef RESULTSETS_CTRL_H
#define RESULTSETS_CTRL_H

#pragma once

#include <Wt/WObject>

#include <Wt/WTabWidget>
#include <Wt/WTableView>






#include "ResultSetsView.h"
#include "ResultSetsModel.h"
#include "ResultSetController.h"

#include "ObserverGoF.h"

///	Esta clase funciona como contenedor para todas las tuplas MVC
/// conectadas a cada una de las pestañas. Además, incluye punteros
/// a la vista y al modelo correspondientes a este controlador.
class ResultSetsController : public Wt::WObject, public SubjectGoF
{
public:
    /// Constructor
    ResultSetsController(const std::string & parent);

    /// Crea la vista
    //Wt::WContainerWidget* createView(Wt::WContainerWidget* parentContainer);
    ResultSetsView* createView(Wt::WContainerWidget* parentContainer);

    /// Crea un nuevo controlador para una nueva pestaña
    ResultSetController* getNewControllerIfNeeded(const std::string & name);

    /// Eventos a los que debe reaccionar este controlador

    /// Ha cambiado la pestaña activa, se recibe como 
    /// argumento el indice de la nueva pestaña.
    void tabChanged(int currentTab);

    /// Se ha movido la vista dentro de la ventana
    //EventSignal<WScrollEvent>& scrolled();












    /// Destructor
    ~ResultSetsController();

protected:
    ///  DATOS ESPECÍFICOS de cada controlador

    ///  Control de pestañas
    //Wt::WTabWidget* tabWidget_;

    ///  Contenedor del control de pestañas
    //Wt::WContainerWidget* tabWidgetContainer_;

    /// Modelo asociado a este controlador
    ResultSetsModel* model_;
    /// Vista asociada a este controlador
    ResultSetsView* view_;

    /// Mapa de indices (enteros) a controladores (uno por pestaña)
    typedef std::map<int, ResultSetController*> ControllersMap;
    ControllersMap controllersMap_;
    typedef std::map<const std::string, int> IndexesMap;
    IndexesMap indexesMap_;

    ResultSetController* currentController_;

    /// FIN de DATOS ESPECÍFICOS de cada controlador

    void fillModel();
};

#endif /// RESULTSETS_CTRL_H
