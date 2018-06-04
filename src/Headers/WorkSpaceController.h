///  WorkSpaceController.h

#ifndef WORKSPACECTRL_H
#define WORKSPACECTRL_H

#pragma once

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

#include "WorkSpaceView.h"
#include "WorkSpaceModel.h"

///	Main Application Controller. Implements an Observer Pattern (GoF),
/// and creates the model and the view asociated with this controller.
class WorkSpaceController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
    /// @param name Nombre asociado al controlador, vista y modelo
    WorkSpaceController(const std::string & name);

    /// Crea una vista (pudiera haber varias para el mismo modelo)
    Wt::WTreeView *createView(Wt::WContainerWidget* wsContainer);

    /// Eventos a los que debe reaccionar este controlador

    /// Ha cambiado el elemento seleccionado en el árbol de la izquierda
    void folderChanged();
    /// Se ha cambiado el ancho de una columna
    void columnResized(int col, Wt::WLength width);
    /// Se ha movido la vista dentro de la ventana
    //EventSignal<WScrollEvent>& scrolled();
    void viewScrolled(Wt::WScrollEvent e);

    /// Se ha movido la vista dentro del contenedor
    // se trata de capturar el evento en el que el usuario
    // mueve el divisor vertical para ajustar el ancho del
    // arbol contenido dentro de la vista del workspace
    //EventSignal<WScrollEvent>& scrolled();
    void containerScrolled(Wt::WScrollEvent e);

    ///  Fin de eventos a los que debe reaccionar este controlador

    /// Slot para seleccion de nuevo item
    std::string selectedItem() { return selectedItem_; }

    /// Destructor
    ~WorkSpaceController();

protected:
    ///  DATOS ESPECÍFICOS de cada controlador

    ///  Contenedor de la vista
    Wt::WContainerWidget* viewContainer_;

    /// Modelo asociado a este controlador
    WorkSpaceModel* model_;
    /// Vista asociada a este controlador
    WorkSpaceView* view_;

    ///  Datos particulares de cada tipo de vista
    std::string selectedItem_;
    /// FIN de datos particulares de cada tipo de vista

    /// FIN de DATOS ESPECÍFICOS de cada controlador

    void fillModel();
};

#endif /// WORKSPACECTRL_H
