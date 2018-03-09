//	ResultSet2Controller.cpp
//

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "ResultSet2Controller.h"
#include "ResultSet2View.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using namespace Wt;

// Constructor
ResultSet2Controller::ResultSet2Controller(string name) : SubjectGoF(name)
{
	rsModel_ = new ResultSet2Model(this);
}

// Crea y configura la vista
WWidget* ResultSet2Controller::createView(WContainerWidget* resultsetContainer)
{
	rsViewContainer_ = resultsetContainer;

	rsView_ = new ResultSet2View(rsViewContainer_);
	rsView_->setModel(rsModel_);

//	rsView_->selectionChanged()
//		.connect(this, &ResultSet2Controller::recordChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

	//TODO FIXME HACK
//	rsView_->onSelectedRow()
//		.connect(this, &ResultSet2Controller::recordChanged);

	rsViewContainer_->addWidget(rsView_);

	return rsView_;
}

#if 0

void ResultSet2Controller::recordChanged( string sQuery ) 
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

#endif

void ResultSet2Controller::rowChanged()
{
}

ResultSet2Controller::~ResultSet2Controller()
{
	delete rsModel_;
}

