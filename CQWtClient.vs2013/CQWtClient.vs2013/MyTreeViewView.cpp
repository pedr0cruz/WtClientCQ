// MyTreeViewView.cpp

#include "stdafx.h"

#include <iostream>

#include <Wt/WAbstractItemModel>
#include <Wt/WItemSelectionModel>
#include <Wt/WMessageBox>

#include "MyTreeViewView.h"

using namespace Wt;

//const char *MyTreeViewView::FileSelectionMimeType = "application/x-computers-selection";

// Constructor
MyTreeViewView::MyTreeViewView(Wt::WContainerWidget *parent) : WTreeView(parent)
{
	// Elimina el menu de contexto del explorador y otros atributos
	setAttributeValue("oncontextmenu",
		"event.cancelBubble = true; event.returnValue = false; return false;");
	resize(WLength::Auto, WLength::Auto);
	setLayoutSizeAware(true);
	setSelectionMode(SingleSelection);
#if 0
    int col = 0;
    setColumnWidth(col++, Wt::WLength(150.0, Wt::WLength::Unit::Pixel));
    setColumnWidth(col++, Wt::WLength(150.0, Wt::WLength::Unit::Pixel));
    setColumnWidth(col++, Wt::WLength(150.0, Wt::WLength::Unit::Pixel));
    setColumnWidth(col++, Wt::WLength(150.0, Wt::WLength::Unit::Pixel));
    //setColumnWidth(col++, Wt::WLength(100.0, Wt::WLength::Unit::Pixel));
    //setColumnWidth(col++, Wt::WLength()); // CSS width: auto 
    setColumnWidth(col++, Wt::WLength(100.0, Wt::WLength::Unit::Percentage));

	// Accept drops for the custom mime type.
	acceptDrops(FileSelectionMimeType);
#endif
}

MyTreeViewView::~MyTreeViewView()
{
}

#if 0

void MyTreeViewView::dropEvent(const Wt::WDropEvent& event, const Wt::WModelIndex& target)
{
	/*
	* We reimplement the drop event to handle the dropping of a
	* selection of computers.
	*
	* The test below would always be true in this case, since we only
	* indicated support for that particular mime type.
	*/
	if (event.mimeType() == FileSelectionMimeType) {
		/*
		* The source object for a drag of a selection from a WTreeView is
		* a WItemSelectionModel.
		*/
		WItemSelectionModel *selection
			= dynamic_cast<WItemSelectionModel *>(event.source());

#ifdef WT_THREADED
		int result = WMessageBox::show
			("Drop event",
			"Move "
			+ boost::lexical_cast<std::string>(selection->selectedIndexes().size())
			+ " files to folder '"
			+ boost::any_cast<WString>(target.data(DisplayRole)).toUTF8()
			+ "' ?",
			Yes | No);
#else
		int result = Yes;
#endif

		if (Yes == result) {
			/*
			* You can access the source model from the selection and
			* manipulate it.
			*/
			WAbstractItemModel *sourceModel = selection->model();

			WModelIndexSet toChange = selection->selectedIndexes();

			for (WModelIndexSet::reverse_iterator i = toChange.rbegin();
				i != toChange.rend(); ++i) {
				WModelIndex index = *i;

				/*
				* Copy target folder to file. Since we are using a
				* dynamic WSortFilterProxyModel that filters on folder, this
				* will also result in the removal of the file from the
				* current view.
				*/
				std::map<int, boost::any> data = model()->itemData(target);
				data[DecorationRole] = index.data(DecorationRole);
				sourceModel->setItemData(index, data);
			}
		}
	}
}

#endif