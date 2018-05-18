/// RecordSetController.h

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
    /// @param name Nombre asociado al controlador, vista y modelo
    RecordSetController(const std::string & name);

    /// Crea una vista (pudiera haber varias para el mismo modelo)
    /// @param container Wt::WContainerWidget* Puntero a objeto contenedor
    /// @return Wt::WWidget* Puntero a vista que es un objeto de alguna clase derivada de Wt::WWidget
    Wt::WWidget* createView(Wt::WContainerWidget* container);

    ///  Eventos a los que debe reaccionar este controlador

    /// Cambia el control que tiene el foco
    /// @param s const std::string & Cadena que especifica el control que recibe el foco
    void itemChanged(const std::string & s);

    // Se ha movido la vista dentro de la ventana
    //EventSignal<WScrollEvent>& scrolled();

    /// Indica que el usuario puls� el bot�n primario del rat�n sobre la vista
	void clicked();
    /// Indica que el usuario puls� doblemente el bot�n primario del rat�n sobre la vista
    void doubleClicked();
    /// Indica que el usuario puls� la tecla ENTER teniendo la vista el foco 
    void enterPressed();
    /// Indica que el usuario puls� la tecla ESCAPE teniendo la vista el foco 
    void escapePressed();
    /// Indica que la vista recibi� el foco
    void focussed();
    /// Indica que el usuario puls� alguna tecla teniendo la vista el foco
    void keyPressed();
    /// Indica que el usuario movi� la rueda del rat�n teniendo la vista el foco
    void mouseWheel();
    /// Indica que el contenido de la vista se desplaz� 
    /// @param e Wt::WScrollEvent Ofrece datos sobre el desplazamiento
    void scrolled(Wt::WScrollEvent e);

    /// Slot para seleccion de nuevo item
    /// @return Cadena que contiene el valor del elemento seleccionado
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

    ///  DATOS ESPEC�FICOS de cada tipo de vista

    std::string selectedItem_;

    /// FIN de DATOS ESPEC�FICOS de cada tipo de vista

    /// Actualiza los datos del modelo
	void fillModel();
};

#endif /// RECORDSET_CTRL_H
