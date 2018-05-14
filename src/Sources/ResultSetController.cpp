//	ResultSetController.cpp

#include "stdafx.h"

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "ResultSetController.h"
#include "ResultSetView.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using std::string;
using namespace Wt;

// Constructor
ResultSetController::ResultSetController(const string & name) : SubjectGoF(name)
{
	model_ = new ResultSetModel(0, 0, this);
}

// Crea y configura la vista
//WWidget* ResultSetController::createView(WContainerWidget* resultsetContainer)
ResultSetView* ResultSetController::createView(WContainerWidget* resultsetContainer)
{
    viewContainer_ = resultsetContainer;

    view_ = new ResultSetView(viewContainer_);
	view_->setModel(model_);

//	view_->selectionChanged()
//		.connect(this, &ResultSetController::recordChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

	view_->clicked().connect(this, &ResultSetController::clicked);
	view_->doubleClicked().connect(this, &ResultSetController::doubleClicked);
	//view_->enterPressed().connect(this, &ResultSetController::enterPressed);
	//view_->escapePressed().connect(this, &ResultSetController::escapePressed);
	view_->focussed().connect(this, &ResultSetController::focussed);
	view_->keyPressed().connect(this, &ResultSetController::keyPressed);
	view_->mouseWheel().connect(this, &ResultSetController::mouseWheel);
	view_->scrolled().connect(this, &ResultSetController::scrolled);

	//TODO FIXME HACK
//	view_->onSelectedRow()
//		.connect(this, &ResultSetController::recordChanged);

	viewContainer_->addWidget(view_);

	return view_;
}

void ResultSetController::recordChanged(const string & sQuery)
{
	model_->fillModel(sQuery);
	view_->fillTable();
	view_->refresh();

/*	if (view_->selectedIndexes().empty())
		return;
	WModelIndex selected = *view_->selectedIndexes().begin();
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

//view_->enterPressed().connect(this, &ResultSetController::enterPressed);
//view_->escapePressed().connect(this, &ResultSetController::escapePressed);()

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
    delete view_;
    delete model_;
}

