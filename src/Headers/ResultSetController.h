//  ResultSetController.h

#ifndef RESULTSET_CTRL_H
#define RESULTSET_CTRL_H

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItemModel>
#include <Wt/WModelIndex>

#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>

#include "ObserverGoF.h"

#include "ResultSetView.h"
#include "ResultSetModel.h"

///	Controller for ResultSet which includes the result obtained from a query.
///	Implements the Subject of the Observer Pattern and contains a selected item.
class ResultSetController : public Wt::WObject, public SubjectGoF
{
public:
    /// Constructor
    ResultSetController(const std::string & name);

    /// Crea una vista (pudiera haber varias para el mismo modelo)
    //Wt::WContainerWidget* createView(Wt::WContainerWidget* container);
    ResultSetView* createView(Wt::WContainerWidget* container);

    ///  Eventos a los que debe reaccionar este controlador

    /// Ha cambiado el registro mostrado
    void recordChanged(const std::string & s);
    void clicked();
    void doubleClicked();
    void focussed();
    void keyPressed();
    void mouseWheel();
    void rowChanged();
    /// Se ha movido la vista dentro de la ventana
    //EventSignal<Wt::WScrollEvent>& scrolled();
    void scrolled(Wt::WScrollEvent e);

    ///  Fin de eventos a los que debe reaccionar este controlador

    /// Slot para seleccion de nuevo item
    std::string selectedItem() { return selectedItem_; }

    /// Destructor
    ~ResultSetController();

protected:
    ///  DATOS ESPECÍFICOS de cada tipo de vista

    ///  Contenedor de la vista
    Wt::WContainerWidget* viewContainer_;

    /// Modelo asociado a este controlador
    ResultSetModel* model_;
    /// Vista asociada a este controlador
    ResultSetView*  view_;

    ///  Datos particulares de cada tipo de vista
    std::string selectedItem_;

    /// FIN de DATOS ESPECÍFICOS de cada tipo de vista

    void fillModel();
};

#endif /// RESULTSET_CTRL_H
