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
RecordSetsController::RecordSetsController(const string & name)
    : SubjectGoF(name)
    , recTabWidget_(nullptr)
    , recTabWidgetContainer_(nullptr)
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
    auto form = new WTemplateFormView();
    auto newTabIndex = recTabWidget_->count();
    auto menuItem = view_->addTab(form, name);
    controllersMap_[newTabIndex] = controller;
    return controller;
}

#if 0
RecordSetController* RecordSetController::currentController()
{
    auto currentTabIndex = recTabWidget_->currentIndex();
    /*
    auto tabObject = rssTabWidget_->children()[currentTabIndex];
    WTabWidget = tab->
    */
    return controllersMap_[currentTabIndex];
}
#endif
