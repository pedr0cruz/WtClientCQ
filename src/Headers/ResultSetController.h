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

using namespace Wt;

class ResultSetController : public Wt::WObject, public SubjectGoF
{
public:
	// Constructor
	ResultSetController(string name);
	// Crea la vista con el Modelo
	WWidget* createView(WContainerWidget* rsContainer);
	void recordChanged(string s); // Slot para seleccion de nuevo item
	string selectedItem() { return selectedItem_; }
	// Destructor
	~ResultSetController();

protected:
	WContainerWidget* rsViewContainer_;
	ResultSetView*  rsView_;
	ResultSetModel* rsModel_;
	string selectedItem_;

	void fillModel();
};

#endif // RESULTSETCTRL_H