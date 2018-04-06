#ifndef RESULTSETCTRL_H
#define RESULTSETCTRL_H

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
#include "ResultSetView.h"
#include "ResultSetModel.h"

#include <string>

//using namespace Wt;

///	Controller for ResultSet which includes the result obtained from a query.
///	This class implements a Subject Pattern and contains a selected item.
class ResultSetController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
	ResultSetController(const std::string & name);
	/// Crea la vista con el Modelo
    Wt::WWidget* createView(Wt::WContainerWidget* rsContainer);
	void recordChanged(string s);
	/// Slot para seleccion de nuevo item
	string selectedItem() { return selectedItem_; }
	/// Destructor
	~ResultSetController();

protected:
    Wt::WContainerWidget* rsViewContainer_;
	ResultSetView*  rsView_;
	ResultSetModel* rsModel_;
	std::string selectedItem_;

	void fillModel();
};

#endif /// RESULTSETCTRL_H
