// RecordSetController.h

#ifndef RECORDSET_CTRL_H
#define RECORDSET_CTRL_H

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

#include "RecordSetView.h"
#include "RecordSetModel.h"

///	Controller for RecordSet which includes the result obtained from a given ResultSet
/// in the table visible in the top view.
///	Implements the Subject of the Observer Pattern and contains a selected item which
/// happens to be the control wich has the focus.
class RecordSetController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
    RecordSetController(const std::string & name);

    /// Crea una vista (pudiera haber varias para el mismo modelo)
    Wt::WWidget* createView(Wt::WContainerWidget* container);

    ///  Eventos a los que debe reaccionar este controlador

    /// Cambia el control que tiene el foco
    void itemChanged(const std::string & s);
    /// Se ha movido la vista dentro de la ventana
    //EventSignal<WScrollEvent>& scrolled();

	void clicked();
	void doubleClicked();
    void enterPressed();
    void escapePressed();
    void focussed();
	void keyPressed();
    void mouseWheel();

    void scrolled(Wt::WScrollEvent e);

    /// Slot para seleccion de nuevo item
    std::string selectedItem() { return selectedItem_; }

	/// Destructor
	~RecordSetController();

protected:
    ///  Contenedor de la vista
    Wt::WContainerWidget* viewContainer_;

    /// Modelo asociado a este controlador
    RecordSetModel* model_;
    /// Vista asociada a este controlador
    RecordSetView*  view_;

    ///  DATOS ESPECÍFICOS de cada tipo de vista

    std::string selectedItem_;

    /// FIN de DATOS ESPECÍFICOS de cada tipo de vista

	void fillModel();
};

#endif /// RECORDSET_CTRL_H
