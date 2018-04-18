#ifndef RECORDSETS_VIEW_H
#define RECORDSETS_VIEW_H

#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>

//#include <memory>

#include "RecordSetsModel.h"

///	RecordSetsView: Shows the data from the associated model.
/// Inherits from WContainerWidget and from WTabWidget to implement 
//  a Tab widget and its inner container.
class RecordSetsView : public Wt::WContainerWidget, public Wt::WTabWidget
{
public:
    static RecordSetsView* createView(Wt::WContainerWidget* parentContainer);
	
	virtual ~RecordSetsView();

    Wt::WTabWidget* getTabWidget();
    Wt::WContainerWidget* getTabWidgetContainer();

    void setModel(RecordSetsModel* model);
    //void setModel(std::shared_ptr <RecordSetModel> model);

private:
    RecordSetsView(Wt::WContainerWidget *parent = 0);
    //RecordSetView(std::shared_ptr <Wt::WContainerWidget> parent = nullptr);

    RecordSetsModel* model_;
    Wt::WTabWidget* tabWidget_;
    Wt::WContainerWidget* tabWidgetContainer_;
};

#endif /// RECORDSETS_VIEW_H
