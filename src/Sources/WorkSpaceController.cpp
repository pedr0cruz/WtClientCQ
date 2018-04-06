
#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "WorkSpaceController.h"
#include "WorkSpaceView.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using namespace Wt;

// Constructor
WorkSpaceController::WorkSpaceController(string name) :SubjectGoF(name)
{
	wsModel_ = new WorkSpaceModel(this);
	wsModel_->fillModel();
}

// Crea y configura la vista
WTreeView *WorkSpaceController::createView(WContainerWidget* workSpaceContainer) 
{
	wsViewContainer_ = workSpaceContainer;

	wsView_ = new WorkSpaceView();
	wsView_->setModel(wsModel_);
	wsView_->expandToDepth(1);

	wsView_->selectionChanged()
		.connect(this, &WorkSpaceController::folderChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

	wsViewContainer_->addWidget(wsView_);

	return wsView_;
}

void WorkSpaceController::folderChanged()
{
    if (wsView_->selectedIndexes().empty()) {
        return;
    }
	WModelIndex selected = *wsView_->selectedIndexes().begin();
	boost::any d = selected.data(UserRole);
	if (!d.empty()) {
		selectedItem_ = boost::any_cast<std::string>(d);
		if (selected.flags().testFlag(ItemIsDragEnabled)){
			notify(); // a los observadores o controladoras principales
		}
	}
}

WorkSpaceController::~WorkSpaceController()
{
	delete wsModel_;
}

