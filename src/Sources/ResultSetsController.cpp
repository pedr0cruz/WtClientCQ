//	ResultSetsController.cpp

#include "stdafx.h"

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>
#include <Wt/WTemplateFormView>
#include <Wt/WStackedWidget>
#include <Wt/WMenuItem>

#include <string>
#include <vector>

#include "ObserverGoF.h"

#include "ResultSetController.h"

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

// Constructor
ResultSetsController::ResultSetsController(const string & name) : SubjectGoF(name)
//    , tabWidget_(nullptr)
//    , tabWidgetContainer_(nullptr)
{
    model_ = new ResultSetsModel(this);
}

// Destructor
ResultSetsController::~ResultSetsController()
{
    for each (auto key_value_pair in controllersMap_) {
        delete key_value_pair.second;
    }
    delete view_;
    delete model_;
}

// Crea la vista que contiene todas las pestañas
//WContainerWidget* ResultSetsController::createView(WContainerWidget* parentContainer)
ResultSetsView* ResultSetsController::createView(WContainerWidget* parentContainer)
{
    //tabWidgetContainer_ = parentContainer;
    //tabWidget_ = new ResultSetsView(tabWidgetContainer_);
    //tabWidgetContainer_ = ResultSetsView::createView(tabWidgetContainer_);
    //view_ = new ResultSetsView(tabWidgetContainer_);
    view_ = new ResultSetsView(parentContainer);
    view_->setModel(model_);

    //	rsView_->selectionChanged()
    //		.connect(this, &ResultSetController::recordChanged);
    //treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

    view_->currentChanged().connect(this, &ResultSetsController::tabChanged);

    return view_;
}


ResultSetController* ResultSetsController::getNewControllerIfNeeded(const string & name)
{
    ResultSetController* controller = nullptr;

    auto itIndex = indexesMap_.find(name);
    if (indexesMap_.end() == itIndex) {
        controller = new ResultSetController(name);
        ResultSetView* rsView = new ResultSetView();
        Wt::WMenuItem* tabMenuItem = view_->addTab(rsView, name);
        int new_tab_index = static_cast <int> (indexesMap_.size());
        indexesMap_[name] = new_tab_index;
        controllersMap_[new_tab_index] = controller;
    }
    else {
        int selected_tab_index = itIndex->second;
        view_->setCurrentIndex(selected_tab_index);
        auto itController = controllersMap_.find(selected_tab_index);
        controller = itController->second;
    }

    currentController_ = controller;

    return currentController_;
}

#if 0
ResultSetController* ResultSetsController::currentController()
{
    auto currentTabIndex = tabWidget_->currentIndex();
    /*
    auto tabObject = tabWidget_->children()[currentTabIndex];
    WTabWidget = tab->
    */
    return controllersMap_[currentTabIndex];
}
#endif

void ResultSetsController::tabChanged(int currentTab)
{
    model_->fillModel(currentTab);
    controllersMap_[currentTab]->notify();
}

