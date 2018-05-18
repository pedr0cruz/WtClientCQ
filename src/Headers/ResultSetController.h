///  ResultSetController.h

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
    /// @param name Nombre asociado al controlador, vista y modelo
    ResultSetController(const std::string & name);

    /// Crea una vista (pudiera haber varias para el mismo modelo)
    /// @param container Wt::WContainerWidget* Puntero a objeto contenedor
    /// @return ResultSetView* Puntero a vista creada
    ResultSetView* createView(Wt::WContainerWidget* container);

    ///  Eventos a los que debe reaccionar este controlador

    /// Ha cambiado el registro mostrado
    /// @param s const std::string & Cadena de texto con datos del registro cambiado
    void recordChanged(const std::string & s);
    /// El usuario ha pulsado el botón primario del ratón sobre la vista
    void clicked();
    /// El usuario ha pulsado el botón primario del ratón sobre la vista
    void doubleClicked();
    /// El usuario ha pulsado doblemente el botón primario del ratón sobre la vista
    void focussed();
    /// El usuario ha pulsado alguna tecla sobre la vista 
    void keyPressed();
    /// El usuario ha movido la rueda del ratón sobre la vista 
    void mouseWheel();
    /// Ha cambiado la fila del conjunto de resultados mostrados en la vista
    void rowChanged();
    /// Se ha desplazado la vista dentro de la ventana
    //EventSignal<Wt::WScrollEvent>& scrolled();
    void scrolled(Wt::WScrollEvent e);

    ///  Fin de eventos a los que debe reaccionar este controlador

    /// Slot para seleccion de nuevo item
    /// @return std::string Cadena con el elemento seleccionado
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

    /// Actualiza datos del modelo 
    void fillModel();
};

#endif /// RESULTSET_CTRL_H
