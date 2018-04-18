//	RecordSetsController.cpp
//

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include <string>
#include <vector>

#include "ObserverGoF.h"

#include "RecordSetsModel.h"
#include "RecordSetsView.h"
#include "RecordSetsController.h"

#include "RecordSetController.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using std::string;
using std::vector;

using namespace Wt;

static const string s_recordSetsTabsWidget("recordSetsTabWidget");

/// Constructor
RecordSetsController::RecordSetsController(const string & name) : SubjectGoF(name)
{
    model_ = new RecordSetsModel(this);
}

RecordSetsController::~RecordSetsController()
{
    for each (auto key_value_pair in controllersMap_) {
        delete key_value_pair.second;
    }
    delete view_;
    delete model_;
}

RecordSetController* RecordSetsController::newController(const string & name)
{
    auto controller = new RecordSetController(name);
/*
    auto form = new WTemplateFormView();
    auto newTabIndex = recTabWidget_->count();
    auto menuItem = view_->addTab(form, name);
*/
    auto newControllerIndex = controllersMap_.size();
    controllersMap_[newControllerIndex] = controller;
    return controller;
}

// Crea y configura la vista
WWidget* RecordSetsController::createView(WContainerWidget* recordSetsContainer)
{
    view_ = new RecordSetsView(recordSetsContainer);
    view_->setModel(model_);

    view_->currentChanged().connect(this, &RecordSetsController::tabChanged);

    return view_->getTabWidgetContainer();
}

void RecordSetsController::tabChanged(int currentTab)
{
    model_->setCurrentTab(currentTab);
    controllersMap_[currentTab]->notify();
}

