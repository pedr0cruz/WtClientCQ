//  RecordSetView.h

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

///	RecordSetView: Shows the data from a model.
/// Inherits from WTemplateFormView to implement the view associated to a form model.
class RecordSetView : public Wt::WTemplateFormView
{
public:
	RecordSetView(Wt::WContainerWidget *parent = 0);

    void setModel(RecordSetModel* model);

	void setHidden(bool, const Wt::WAnimation &animation = Wt::WAnimation());

//	Signal<int>& rowSelected(){ return rowSelect; }
//	Signal<int>& onFindByColumn(){ return findByColumn; }
//	Signal<int, bool>& onSortByColumn(){ return sortByColumn; }

    Wt::Signal<std::string> itemSelect;

	~RecordSetView();

private:
    ///  DATOS ESPECÍFICOS de cada tipo de vista

    RecordSetModel* model_;
    std::string selectedInputCtrlId;

    /// FIN de DATOS ESPECÍFICOS de cada tipo de vista
};

#endif /// RECORDSET_VIEW_H
