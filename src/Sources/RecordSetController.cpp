//	RecordSetController.cpp

#include "stdafx.h"

#include <boost/algorithm/string/replace.hpp>

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "RecordSetController.h"
#include "RecordSetView.h"

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using std::string;
using namespace Wt;

/// Constructor
RecordSetController::RecordSetController(const string & name) : SubjectGoF(name)
{
    model_ = new RecordSetModel(this);
}

/// Crea y configura la vista
WWidget* RecordSetController::createView(WContainerWidget* recordsetContainer)
{
    viewContainer_ = recordsetContainer;

    view_ = new RecordSetView(recordsetContainer);
    view_->setModel(model_);

    /// Conecta los generadores de eventos a las funciones receptoras

//	view_->selectionChanged()
//		.connect(this, &RecordSetController::recordChanged);
	//treeView->mouseWentUp().connect(this, &WorkSpaceController::showPopup);

	view_->clicked().connect(this, &RecordSetController::clicked);
	view_->doubleClicked().connect(this, &RecordSetController::doubleClicked);
	view_->enterPressed().connect(this, &RecordSetController::enterPressed);
	view_->escapePressed().connect(this, &RecordSetController::escapePressed);
	view_->focussed().connect(this, &RecordSetController::focussed);
	view_->keyPressed().connect(this, &RecordSetController::keyPressed);
	view_->mouseWheel().connect(this, &RecordSetController::mouseWheel);
	//view_->scrolled().connect(this, &RecordSetController::scrolled);

	//TODO FIXME HACK
//	view_->onSelectedRow()
//		.connect(this, &RecordSetController::recordChanged);

    /// Agrega la vista creada al contenedor superior
	viewContainer_->addWidget(view_);

	return view_;
}

#if 0
void RecordSetController::recordChanged( string sQuery ) 
{
	models_->fillModel( sQuery );
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

void RecordSetController::escapePressed()
{
    int a = 0;
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
    delete model_;
}

