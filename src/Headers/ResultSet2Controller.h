#ifndef RESULTSET2_CTRL_H
#define RESULTSET2_CTRL_H

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
#include "ResultSet2View.h"
#include "ResultSet2Model.h"

using namespace Wt;

///	Controller for ResultSet which includes the result obtained from a query.
///	This class implements a Subject Pattern and contains a selected item.
class ResultSet2Controller : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
	ResultSet2Controller(string name);
	/// Crea la vista con el Modelo
	WWidget* createView(WContainerWidget* rsContainer);

	//void recordChanged(string s);

	void rowChanged();

	/// Slot para seleccion de nuevo item
	string selectedItem() { return selectedItem_; }
	/// Destructor
	~ResultSet2Controller();

protected:
	WContainerWidget* rsViewContainer_;
	ResultSet2View*  rsView_;
	ResultSet2Model* rsModel_;
	string selectedItem_;

	void fillModel();
};

#endif /// RESULTSET2_CTRL_H