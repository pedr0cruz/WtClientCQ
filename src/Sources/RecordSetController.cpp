//	RecordSetController.cpp
//

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "RecordSetController.h"
#include "RecordSetView.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using namespace Wt;

// Constructor
RecordSetController::RecordSetController(const string & name) : SubjectGoF(name)
{
    recModel_ = new RecordSetModel(this);
}

// Crea y configura la vista
WWidget* RecordSetController::createView(WContainerWidget* recordsetContainer)
{
    recViewContainer_ = recordsetContainer;

    recView_ = new RecordSetView(recordsetContainer);
    recView_->setModel(recModel_);

//	recView_->selectionChanged()
//		.connect(this, &RecordSetController::recordChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

	recView_->clicked().connect(this, &RecordSetController::clicked);
	recView_->doubleClicked().connect(this, &RecordSetController::doubleClicked);
	recView_->enterPressed().connect(this, &RecordSetController::enterPressed);
	recView_->escapePressed().connect(this, &RecordSetController::escapePressed);
	recView_->focussed().connect(this, &RecordSetController::focussed);
	recView_->keyPressed().connect(this, &RecordSetController::keyPressed);
	recView_->mouseWheel().connect(this, &RecordSetController::mouseWheel);
	//recView_->scrolled().connect(this, &RecordSetController::scrolled);

	//TODO FIXME HACK
//	recView_->onSelectedRow()
//		.connect(this, &RecordSetController::recordChanged);

	recViewContainer_->addWidget(recView_);
	return recView_;
}

void RecordSetController::recordChanged( string sQuery ) 
{
	recModels_->fillModel( sQuery );
	recView_->fillTable();
	recView_->refresh();

/*	if (recView_->selectedIndexes().empty())
		return;
	WModelIndex selected = *recView_->selectedIndexes().begin();
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
void RecordSetController::rowChanged()
{
}
#endif

void RecordSetController::clicked()
{
	auto a = 0;
	auto b = a;
}

void RecordSetController::doubleClicked()
{
	auto a = 0;
	auto b = a;
}

void RecordSetController::enterPressed()
{
    auto a = 0;
    auto b = a;
}

void RecordSetController::focussed()
{
	auto a = 0;
	auto b = a;
}

void RecordSetController::keyPressed()
{
	auto a = 0;
	auto b = a;
}

void RecordSetController::mouseWheel()
{
	auto a = 0;
	auto b = a;
}

RecordSetController::~RecordSetController()
{
	delete recModel_;
}

