#ifndef WORKSPACECTRL_H
#define WORKSPACECTRL_H

#include <Wt/WObject>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItemModel>
#include <Wt/WModelIndex>

#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>

#include "ObserverGoF.h"
#include "WorkSpaceView.h"
#include "WorkSpaceModel.h"

using namespace Wt;

///	WorkSpaceController: Main Application Controller.
/// This class implements a Subject Pattern and creates the view
class WorkSpaceController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
	WorkSpaceController(string name);
	/// Crea la vista con el Modelo
	WTreeView *createView(WContainerWidget* wsContainer);
	void folderChanged(); ///< Slot para seleccion de nuevo item
	string selectedItem() { return selectedItem_; }
	~WorkSpaceController();
protected:
	WContainerWidget* wsViewContainer_;
	WorkSpaceView* wsView_;
	WorkSpaceModel *wsModel_;
	string selectedItem_;
};

#endif /// WORKSPACECTRL_H
