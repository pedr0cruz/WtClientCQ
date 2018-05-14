///  RecordSetView.h

#ifndef RECORDSET_VIEW_H
#define RECORDSET_VIEW_H

#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WTemplate>
#include <Wt/WCssDecorationStyle>
#include <Wt/WAnimation>
#include <Wt/WDialog>
#include <Wt/WLabel>
#include <Wt/WFormModel>
#include <Wt/WTemplateFormView>
#include <Wt/WSignal>
#include <Wt/WImage>

#include <vector>
#include <string>

#include "RecordSetModel.h"

///	Shows the data from a model. Inherits from WTemplateFormView 
/// to implement the view associated to a form model.
class RecordSetView : public Wt::WTemplateFormView
{
public:
    /// Constructor
    /// @param parent Wt::WContainerWidget* Puntero a objeto contenedor
	RecordSetView(Wt::WContainerWidget *parent = 0);

    /// Establece el modelo para la vista
    /// @param model RecordSetModel* Puntero a objeto que implementa el modelo
    void setModel(RecordSetModel* model);

    /// Oculta o muestra la vista
    /// @param hidden bool false: la vista, true: la muestra
    /// @param animation const Wt::WAnimation & Anmación a usar, por defecto es  Wt::WAnimation()
	void setHidden(bool hidden, const Wt::WAnimation &animation = Wt::WAnimation());

//	Signal<int>& rowSelected(){ return rowSelect; }
//	Signal<int>& onFindByColumn(){ return findByColumn; }
//	Signal<int, bool>& onSortByColumn(){ return sortByColumn; }

    Wt::Signal<std::string> itemSelect;

    /// Destructor
	~RecordSetView();

private:
    ///  DATOS ESPECÍFICOS de cada tipo de vista

    RecordSetModel* model_;
    std::string selectedInputCtrlId;

    /// FIN de DATOS ESPECÍFICOS de cada tipo de vista
};

#endif /// RECORDSET_VIEW_H
