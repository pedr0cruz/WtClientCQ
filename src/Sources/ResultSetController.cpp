//	ResultSetController.cpp
//

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "ResultSetController.h"
#include "ResultSet2View.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using namespace Wt;

/// Constructor
ResultSetController::ResultSetController(const string & name) : SubjectGoF(name)
{
	rsModel_ = new ResultSet2Model(this);
}

// Crea y configura la vista
WWidget* ResultSetController::createView(WContainerWidget* resultsetContainer)
{
	rsViewContainer_ = resultsetContainer;

	rsView_ = new ResultSet2View(rsViewContainer_);
	rsView_->setModel(rsModel_);

//	rsView_->selectionChanged()
//		.connect(this, &ResultSetController::recordChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

	rsView_->clicked().connect(this, &ResultSetController::clicked);
	rsView_->doubleClicked().connect(this, &ResultSetController::doubleClicked);
	//rsView_->enterPressed().connect(this, &ResultSetController::enterPressed);
	//rsView_->escapePressed().connect(this, &ResultSetController::escapePressed);
	rsView_->focussed().connect(this, &ResultSetController::focussed);
	rsView_->keyPressed().connect(this, &ResultSetController::keyPressed);
	rsView_->mouseWheel().connect(this, &ResultSetController::mouseWheel);
	rsView_->scrolled().connect(this, &ResultSetController::scrolled);

	//TODO FIXME HACK
//	rsView_->onSelectedRow()
//		.connect(this, &ResultSetController::recordChanged);

	rsViewContainer_->addWidget(rsView_);

	return rsView_;
}

void ResultSetController::recordChanged(const string & sQuery)
{
	rsModel_->fillModel(sQuery);
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

#if 0
void ResultSetController::rowChanged()
{
}
#endif

void ResultSetController::clicked()
{
	auto a = 0;
	auto b = a;
}

void ResultSetController::doubleClicked()
{
	auto a = 0;
	auto b = a;
}

//rsView_->enterPressed().connect(this, &ResultSetController::enterPressed);
//rsView_->escapePressed().connect(this, &ResultSetController::escapePressed);()

void ResultSetController::focussed()
{
	auto a = 0;
	auto b = a;
}

void ResultSetController::keyPressed()
{
	auto a = 0;
	auto b = a;
}

void ResultSetController::mouseWheel()
{
	auto a = 0;
	auto b = a;
}

void ResultSetController::scrolled(WScrollEvent e)
{
	auto a = 0;
	auto b = a;
}

ResultSetController::~ResultSetController()
{
	delete rsModel_;
}

