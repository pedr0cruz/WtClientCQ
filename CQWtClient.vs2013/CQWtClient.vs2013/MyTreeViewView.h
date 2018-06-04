///  MyTreeViewView.h

#ifndef MYTREEVIEWVIEW_H
#define MYTREEVIEWVIEW_H

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
#include <Wt/WTreeView>
#include <Wt/WSignal>
#include <Wt/WImage>

#include "MyTreeViewView.h"
#include "MyTreeViewModel.h"

#include <vector>
#include <string>

///	Shows the data from a model. Inherits from WTemplateFormView 
/// to implement the view associated to a form model.
class MyTreeViewView : public Wt::WTreeView
{
public:
    /// Constructor
    /// @param parent Wt::WContainerWidget* Puntero a objeto contenedor
    MyTreeViewView(Wt::WContainerWidget *parent = 0);

    /// Establece el modelo para la vista
    /// @param model RecordSetModel* Puntero a objeto que implementa el modelo
    void setModel(MyTreeViewModel* model);

    /// Oculta o muestra la vista
    /// @param hidden bool false: la vista, true: la muestra
    /// @param animation const Wt::WAnimation & Anmación a usar, por defecto es  Wt::WAnimation()
	//void setHidden(bool hidden, const Wt::WAnimation &animation = Wt::WAnimation());

//	Signal<int>& rowSelected(){ return rowSelect; }
//	Signal<int>& onFindByColumn(){ return findByColumn; }
//	Signal<int, bool>& onSortByColumn(){ return sortByColumn; }
//    Wt::Signal<std::string> itemSelect;
    //Wt::Signal<int>& rowSelected(){ return rowSelect; }

    /// Destructor
    virtual ~MyTreeViewView();

private:
    ///  DATOS ESPECÍFICOS de cada tipo de vista

    MyTreeViewModel* model_;

    /// FIN de DATOS ESPECÍFICOS de cada tipo de vista
};

#endif /// MYTREEVIEWVIEW_H
