#ifndef RESULTSET2_VIEW_H
#define RESULTSET2_VIEW_H

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WTemplate>
#include <Wt/WCssDecorationStyle>
#include <Wt/WAnimation>
#include <Wt/WDialog>
#include <Wt/WLabel>
#include <vector>
#include <string>
#include <Wt/WSignal>
#include <Wt/WTableView>

#include "ResultSet2Model.h"

//using namespace std;
using namespace Wt;

#if 1
///	TableView2: Shows the data from a model.
/// This class inherits from WTable to implement a custom table view.
class TableView2 : public Wt::WTableView
{
private:
	int selectedRow;
	int selectedHeader;
	Signal<int> rowSelect;
	Signal<int> findByColumn;
	Signal<int, bool> sortByColumn;

	vector<bool> sortOrder;

	void s_selectRow(int);

public:
	TableView2(Wt::WContainerWidget *parent = 0);
	void setHeader(vector<string>);
	void addRow(vector<string>);
	void setHidden(bool, const Wt::WAnimation &animation = Wt::WAnimation());
	void setHeaderCount(int headers_count, Wt::Orientation header_orientation);

/*
	Signal< int, int > &  cellClicked()
		Signal emitted when a cell is clicked.More...

		Signal< int, int, int, int > &  currentCellChanged()
		Signal emitted when a new cell received focus.More...

		Signal &  itemSelectionChanged()
		Signal emitted when the selection changes.More...
*/

	Signal<int>& rowSelected(){ return rowSelect; }
	Signal<int>& onFindByColumn(){ return findByColumn; }
	Signal<int, bool>& onSortByColumn(){ return sortByColumn; }

	~TableView2();

};
#endif

////////////////////////// ResultSet2View /////////////////////////////////////////

///	ResultSet2View: Shows the data from a result set.
/// This class inherits from WContainerWidget to implement a container which holds
/// a set of results.
class ResultSet2View : public Wt::WContainerWidget
{
private:
	ResultSet2Model* Model_;
	bool usePager;
	int maxRows;
	int totalRows;
	int maxPages;
	int actualPage;

	vector<string> header;
	vector < vector<string> > data;
	vector < vector<string> > filterData;

	TableView2 *table;
	Wt::WContainerWidget *divPager;
	Wt::WContainerWidget *divTotalPages;
	Wt::WText *totalPages;
	Wt::WContainerWidget *divTablesPager;
	Wt::WMenu *pagerTable;
	Wt::WContainerWidget * firstItem;
	Wt::WMenuItem * firstItem_mi;
	Wt::WContainerWidget * previousItem;
	Wt::WMenuItem * previousItem_mi;
	Wt::WContainerWidget * nextItem;
	Wt::WMenuItem * nextItem_mi;
	Wt::WContainerWidget * lastItem;
	Wt::WMenuItem * lastItem_mi;

	void s_nextTablaCliente();
	void s_lastTablaCliente();
	void s_prevTablaCliente();
	void s_firstTablaCliente();
	void s_findByColumn(int);
	void s_rowSelected(int);

//	Wt::Signal<string> rowSelect;

//	Wt::EventSignal<WScrollEvent>& Wt::WContainerWidget::scrolled();

	void filterBy(int, Wt::WString);
	void sortByColumn(int, bool);

	void updatePagination();
	void showRows();

public:
	ResultSet2View(Wt::WContainerWidget *parent = 0);
	ResultSet2View(vector<string>, Wt::WContainerWidget *parent = 0);
	static const char *ItemSelectionMimeType;

	void setHeader(vector<string>);
	void setData(vector < vector<string> >);
	void createData(); ///< toma el modelo y lo guarda de la matriz <vector <vector>>
	void fillTable();
	void clearTable();

	TableView2* getTable(){ return table; };

	void setMaxRows(int t){ maxRows = t; }
	void setPager(bool pager){ usePager = pager; }
	void setModel(ResultSet2Model* model){ Model_ = model; }

//	Wt::Signal<string>& onSelectedRow(){ return rowSelect; }
	
	/*
	Wt::Signal& Wt::WAbstractItemView::selectionChanged()
	{
	}
	*/

	~ResultSet2View();
};
#endif /// RESULTSET2_VIEW_H
