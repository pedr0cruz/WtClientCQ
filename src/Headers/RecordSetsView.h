//  RecordSetsView.h

#ifndef RECORDSETS_VIEW_H
#define RECORDSETS_VIEW_H

#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>

#include "TabWidget.h"
#include "RecordSetsModel.h"

///	RecordSetsView: Shows the data from the associated model.
/// Inherits from WContainerWidget and from WTabWidget to implement 
//  a Tab widget and its inner container.
class RecordSetsView : /* public Wt::WContainerWidget, */ public TabWidget
{
public:
//    static RecordSetsView* createView(Wt::WContainerWidget* parentContainer);
	
    RecordSetsView(Wt::WContainerWidget *parent = 0);

    virtual ~RecordSetsView();

//    Wt::WTabWidget* getTabWidget();
//    Wt::WContainerWidget* getTabWidgetContainer();

    void setModel(RecordSetsModel* model);
    //void setModel(std::shared_ptr <RecordSetModel> model);

private:
    ///  DATOS ESPECÍFICOS de cada tipo de vista

//    RecordSetsView(Wt::WContainerWidget *parent = 0);

    RecordSetsModel* model_;
    //Wt::WTabWidget* tabWidget_;
    //Wt::WContainerWidget* tabWidgetContainer_;

    /// FIN de DATOS ESPECÍFICOS de cada tipo de vista
};

#endif /// RECORDSETS_VIEW_H
