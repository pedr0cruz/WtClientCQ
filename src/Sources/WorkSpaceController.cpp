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

#if defined (_DEBUG)
//#   define _AMD64_
//#	include <WinDef.h>
//#	include <WinBase.h>
extern "C" void OutputDebugStringA(const char* lpOutputString);
#define OutputDebugString OutputDebugStringA
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
    view_->scrolled()
        .connect(this, &WorkSpaceController::viewScrolled);

    viewContainer_->scrolled()
        .connect(this, &WorkSpaceController::containerScrolled);

	viewContainer_->addWidget(view_);

	return view_;
}

void WorkSpaceController::folderChanged()
{
#if defined(_DEBUG)
    OutputDebugStringA("WorkSpaceController::folderChanged()\n");
#endif
    if (view_->selectedIndexes().empty()) {
        return;
    }
	WModelIndex selected = *view_->selectedIndexes().begin();
	boost::any d = selected.data(UserRole);
	if (!d.empty()) {
		selectedItem_ = boost::any_cast<std::string>(d);
		if (selected.flags().testFlag(ItemIsDragEnabled)){
			notify(); // a los observadores o controladoras principales
#if defined(_DEBUG)
            OutputDebugStringA("\tselected.flags().testFlag(ItemIsDragEnabled) => notify()\n");
#endif
		}
	}
}

void WorkSpaceController::columnResized(int col, Wt::WLength width)
{
#if defined(_DEBUG)
    char msg[1000];
    _snprintf_s(msg, sizeof(msg)-1, "WorkSpaceController::columnResized (col: %d, width: %f)\n", col, width.value());
    OutputDebugStringA(msg);
#endif
}

void WorkSpaceController::viewScrolled(Wt::WScrollEvent e)
{
#if defined(_DEBUG)
    char msg[1000];
    _snprintf_s(msg, sizeof(msg)-1, "WorkSpaceController::viewScrolled (x: %d/%d, y: %d/%d)\n",
        e.scrollX(), e.viewportWidth(),
        e.scrollY(), e.viewportHeight());
    OutputDebugStringA(msg);
#endif
}

void WorkSpaceController::containerScrolled(Wt::WScrollEvent e)
{
//    std::cout << "e.scrollX: " << e.scrollX();
//    std::cout << "e.viewportWidth: " << e.viewportWidth();
#if defined(_DEBUG)
    char msg[1000];
    _snprintf_s(msg, sizeof(msg)-1, "WorkSpaceController::containerScrolled (x: %d/%d, y: %d/%d)\n", 
        e.scrollX(), e.viewportWidth(), 
        e.scrollY(), e.viewportHeight());
    OutputDebugStringA(msg);
#endif
}


WorkSpaceController::~WorkSpaceController()
{
	delete model_;
}

