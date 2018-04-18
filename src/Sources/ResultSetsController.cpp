//	ResultSetsController.cpp
//

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>
#include <Wt/WTemplateFormView>

#include <string>
#include <vector>

#include "ObserverGoF.h"

#include "ResultSetController.h"

//#include "ResultSetsModel.h"
//#include "ResultSetsView.h"
#include "ResultSetsController.h"

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using std::string;
using std::vector;

using namespace Wt;

static const string s_resultSetsTabsWidget("resultSetsTabWidget");

/// Constructor
ResultSetsController::ResultSetsController(const string & name)
    : SubjectGoF(name)
    , rssTabWidget_(nullptr)
    , rssTabWidgetContainer_(nullptr)
{
    model_ = new ResultSetsModel(this);
}

/// Destructor
ResultSetsController::~ResultSetsController()
{
    for each (auto key_value_pair in controllersMap_) {
        delete key_value_pair.second;
    }
    delete view_;
    delete model_;
}

/// Crea la vista que contiene todas las pestañas
WContainerWidget* ResultSetsController::createView(WContainerWidget* parentContainer)
{
    rssTabWidgetContainer_ = parentContainer;
    //rssTabWidget_ = new ResultSetsView(rssTabWidgetContainer_);
    //rssTabWidgetContainer_ = ResultSetsView::createView(rssTabWidgetContainer_);
    rssTabWidgetContainer_ = new ResultSetsView(rssTabWidgetContainer_);
    //rssTabWidget_->setModel(rsModel_);

    //	rsView_->selectionChanged()
    //		.connect(this, &ResultSetController::recordChanged);
    //treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

    return rssTabWidgetContainer_;
}

ResultSet2Controller* ResultSetsController::newController(const string & name)
{
    ResultSet2Controller* controller = new ResultSet2Controller(name);
    WTableView* table = new WTableView();
    int newTabIndex = rssTabWidget_->count();
    WMenuItem* menuItem = rssTabWidget_->addTab(table, name);
    controllersMap_[newTabIndex] = controller;
    return controller;
}

#if 0
ResultSet2Controller* ResultSetsController::currentController()
{
    auto currentTabIndex = rssTabWidget_->currentIndex();
    /*
    auto tabObject = rssTabWidget_->children()[currentTabIndex];
    WTabWidget = tab->
    */
    return controllersMap_[currentTabIndex];
}
#endif
