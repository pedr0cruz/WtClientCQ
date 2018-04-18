#ifndef WORKSPACECTRL_H
#define WORKSPACECTRL_H

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

///	WorkSpaceController: Main Application Controller.
/// Implements a Subject Pattern and creates the view
class WorkSpaceController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
	WorkSpaceController(string name);

    /// Crea una vista (pudiera haber varias para el mismo modelo)
    Wt::WTreeView *createView(Wt::WContainerWidget* wsContainer);

    /// Eventos a los que debe reaccionar este controlador

    /// Ha cambiado el elemento seleccionado en el árbol de la izquierda
    void folderChanged();
    /// Se ha movido la vista dentro de la ventana
    //EventSignal<WScrollEvent>& scrolled();
    void scrolled(Wt::WScrollEvent e);

    ///  Fin de eventos a los que debe reaccionar este controlador

    /// Slot para seleccion de nuevo item
    std::string selectedItem() { return selectedItem_; }

    /// Destructor
    ~WorkSpaceController();

protected:
    ///  Contenedor de la vista
    Wt::WContainerWidget* viewContainer_;

    /// Modelo asociado a este controlador
    WorkSpaceModel *model_;
    /// Vista asociada a este controlador
    WorkSpaceView* view_;

    ///  Datos particulares de cada tipo de vista
    std::string selectedItem_;
    /// FIN de datos particulares de cada tipo de vista

    void fillModel();
};

#endif /// WORKSPACECTRL_H
