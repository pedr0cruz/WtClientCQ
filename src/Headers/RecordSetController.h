#ifndef RECORDSET_CTRL_H
#define RECORDSET_CTRL_H

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
#include "RecordSetView.h"
#include "RecordSetModel.h"

using namespace Wt;

///	Controller for ResultSet which includes the result obtained from a query.
///	This class implements a Subject Pattern and contains a selected item.
class RecordSetController : public Wt::WObject, public SubjectGoF
{
public:
	/// Constructor
	RecordSetController(const string & name);
	/// Crea la vista
	WWidget* createView(WContainerWidget* recContainer);
	//std::shared_ptr <WWidget> createView(std::shared_ptr <WContainerWidget> rsContainer);

	//void recordChanged(string s);
	//EventSignal<WScrollEvent>& scrolled();

	void clicked();
	void doubleClicked();
	void focussed();
	void keyPressed();
	void mouseWheel();
	void scrolled(WScrollEvent e);

//	void rowChanged();

	/// Slot para seleccion de nuevo item
	string selectedItem() { return selectedItem_; }

	/// Destructor
	~RecordSetController();

protected:
	WContainerWidget* recViewContainer_;
	//std::shared_ptr <WContainerWidget> recViewContainer_;

	//std::shared_ptr <RecordSetView>  recView_;
    RecordSetView*  recView_;
    //std::vector <RecordSetView*> recViewVec_;

	//std::shared_ptr <RecordSetModel> recModel_;
    RecordSetModel* recModel_;
    //std::vector <RecordSetModel*> recModelVec_;

	string selectedItem_;

	void fillModel();
};

#endif /// RECORDSET_CTRL_H
