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

/// Constructor
ResultSet2Controller::ResultSet2Controller(const string & name) : SubjectGoF(name)
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

	rsView_->clicked().connect(this, &ResultSet2Controller::clicked);
	rsView_->doubleClicked().connect(this, &ResultSet2Controller::doubleClicked);
	//rsView_->enterPressed().connect(this, &ResultSet2Controller::enterPressed);
	//rsView_->escapePressed().connect(this, &ResultSet2Controller::escapePressed);
	rsView_->focussed().connect(this, &ResultSet2Controller::focussed);
	rsView_->keyPressed().connect(this, &ResultSet2Controller::keyPressed);
	rsView_->mouseWheel().connect(this, &ResultSet2Controller::mouseWheel);
	rsView_->scrolled().connect(this, &ResultSet2Controller::scrolled);

	//TODO FIXME HACK
//	rsView_->onSelectedRow()
//		.connect(this, &ResultSet2Controller::recordChanged);

	rsViewContainer_->addWidget(rsView_);

	return rsView_;
}

void ResultSet2Controller::recordChanged(const string & sQuery)
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
void ResultSet2Controller::rowChanged()
{
}
#endif

void ResultSet2Controller::clicked()
{
	auto a = 0;
	auto b = a;
}

void ResultSet2Controller::doubleClicked()
{
	auto a = 0;
	auto b = a;
}

//rsView_->enterPressed().connect(this, &ResultSet2Controller::enterPressed);
//rsView_->escapePressed().connect(this, &ResultSet2Controller::escapePressed);()

void ResultSet2Controller::focussed()
{
	auto a = 0;
	auto b = a;
}

void ResultSet2Controller::keyPressed()
{
	auto a = 0;
	auto b = a;
}

void ResultSet2Controller::mouseWheel()
{
	auto a = 0;
	auto b = a;
}

void ResultSet2Controller::scrolled(WScrollEvent e)
{
	auto a = 0;
	auto b = a;
}

ResultSet2Controller::~ResultSet2Controller()
{
	delete rsModel_;
}

