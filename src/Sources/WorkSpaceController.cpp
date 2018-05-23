//  WorkSpaceController.cpp

#include "stdafx.h"

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "WorkSpaceController.h"
#include "WorkSpaceView.h"

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

#include <string>

using std::string;
using namespace Wt;

// Constructor
WorkSpaceController::WorkSpaceController(const string & name) :SubjectGoF(name)
{
	model_ = new WorkSpaceModel(this);
	model_->fillModel();
}

// Crea y configura la vista
WTreeView *WorkSpaceController::createView(WContainerWidget* workSpaceContainer) 
{
	viewContainer_ = workSpaceContainer;

	view_ = new WorkSpaceView();
	view_->setModel(model_);
	view_->expandToDepth(1);

	view_->selectionChanged()
		.connect(this, &WorkSpaceController::folderChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);
    view_->columnResized()
        .connect(this, &WorkSpaceController::columnResized);

    viewContainer_->scrolled()
        .connect(this, &WorkSpaceController::containerScrolled);

	viewContainer_->addWidget(view_);

	return view_;
}

void WorkSpaceController::folderChanged()
{
    if (view_->selectedIndexes().empty()) {
        return;
    }
	WModelIndex selected = *view_->selectedIndexes().begin();
	boost::any d = selected.data(UserRole);
	if (!d.empty()) {
		selectedItem_ = boost::any_cast<std::string>(d);
		if (selected.flags().testFlag(ItemIsDragEnabled)){
			notify(); // a los observadores o controladoras principales
		}
	}
}

void WorkSpaceController::columnResized(int col, Wt::WLength width)
{
    std::cout << "col: " << col;
    std::cout << " width: " << width.value();
}

void WorkSpaceController::containerScrolled(Wt::WScrollEvent e)
{
    std::cout << "e.scrollX: " << e.scrollX();
    std::cout << "e.viewportWidth: " << e.viewportWidth();
}


WorkSpaceController::~WorkSpaceController()
{
	delete model_;
}

