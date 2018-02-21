
#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "ResultSetController.h"
#include "ResultSetView.h"

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using namespace Wt;

// Constructor
ResultSetController::ResultSetController(string name) : SubjectGoF(name)
{
	rsModel_ = new ResultSetModel(this);
}

// Crea y configura la vista
WWidget* ResultSetController::createView(WContainerWidget* resultsetContainer)
{
	rsViewContainer_ = resultsetContainer;

	rsView_ = new ResultSetView(rsViewContainer_);
	rsView_->setModel(rsModel_);

//	rsView_->selectionChanged()
//		.connect(this, &ResultSetController::recordChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

	rsViewContainer_->addWidget(rsView_);
	return rsView_;
}

void ResultSetController::recordChanged( string sQuery ) 
{
	rsModel_->fillModel( sQuery );
	rsView_->fillTable();
	rsView_->refresh();

/*	if (rsView_->selectedIndexes().empty())
		return;
	WModelIndex selected = *rsView_->selectedIndexes().begin();
	boost::any d = selected.data(UserRole);
	if (!d.empty()) {
		selectedItem_ = boost::any_cast<std::string>(d);
		if (selected.flags().testFlag(ItemIsDragEnabled)){
			notify(); // a los observadores o controladoras principales
		}
	}
	*/
}

ResultSetController::~ResultSetController()
{
	delete rsModel_;
}

