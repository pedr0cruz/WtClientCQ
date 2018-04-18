#ifndef RESULTSETS_CTRL_H
#define RESULTSETS_CTRL_H

#include <Wt/WObject>

#include <Wt/WTabWidget>
#include <Wt/WTableView>






#include "ResultSetsView.h"
#include "ResultSetsModel.h"
#include "ResultSetController.h"

#include "ObserverGoF.h"

//class ResultSetsModel;
//class ResultSetsView;
//class ResultSetController;

///	Esta clase funciona como contenedor para todas las tuplas MVC
/// conectadas a cada una de las pestañas. Además, incluye punteros
/// a la vista y al modelo correspondientes a este controlador.
class ResultSetsController : public Wt::WObject, public SubjectGoF
{
public:
    /// Constructor
    ResultSetsController(const std::string & parent);

    /// Crea la vista
    Wt::WContainerWidget* createView(Wt::WContainerWidget* recParentContainer);

    /// Crea un nuevo controlador para una nueva pestaña
    ResultSetController* newController(const std::string & name);

    /// Eventos a los que debe reaccionar este controlador

    /// Cambia la pestaña activa
    void tabChanged(const std::string s);
    /// Se ha movido la vista dentro de la ventana
    //EventSignal<WScrollEvent>& scrolled();












    /// Devuelve el indice numerico de la pestaña seleccionada
    int currentTabIndex() { return view_->currentTabIndex(); }

    /// Destructor
    ~ResultSetsController();

protected:
    ///  Control de pestañas
    Wt::WTabWidget* rssTabWidget_;
    ///  Contenedor del control de pestañas
    Wt::WContainerWidget* rssTabWidgetContainer_;
    /// Modelo asociado a este controlador
    ResultSetsModel* model_;
    /// Vista asociada a este controlador
    ResultSetsView* view_;

    /// Datos particulares de cada tipo de vista
    /// Mapa de indices (enteros) a controladores (uno por pestaña)
    typedef std::map<int, ResultSetController*> ControllersMap;
    ControllersMap controllersMap_;
    /// FIN de datos particulares de cada tipo de vista

    void fillModel();
};

#endif /// RESULTSETS_CTRL_H
