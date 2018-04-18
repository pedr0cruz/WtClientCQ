#ifndef RESULTSET_VIEW_H
#define RESULTSET_VIEW_H

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
#include <Wt/WImage>

#include "ResultSetModel.h"

//using namespace std;
using namespace Wt;


///	TableView: Shows the data from a model.
/// This class inherits from WTable to implement a custom table view.
class TableView : public WTable
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
	TableView(Wt::WContainerWidget *parent = 0);
	void setHeader(vector<string>);
	void addRow(vector<string>);
	void setHidden(bool, const Wt::WAnimation &animation = Wt::WAnimation());

	Signal<int>& rowSelected(){ return rowSelect; }
	Signal<int>& onFindByColumn(){ return findByColumn; }
	Signal<int, bool>& onSortByColumn(){ return sortByColumn; }

	~TableView();

};

////////////////////////// ResultSetView /////////////////////////////////////////

///	ResultSetView: Shows the data from a result set.
/// This class inherits from WContainerWidget to implement a container which holds
/// a set of results.
class ResultSetView : public Wt::WContainerWidget
{
private:
	ResultSetModel* Model_;
	bool usePager;
	int maxRows;
	int totalRows;
	int maxPages;
	int actualPage;

	vector<string> header;
	vector < vector<string> > data;
	vector < vector<string> > filterData;

	TableView *table;
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

	Wt::Signal<string> rowSelect;

	void filterBy(int, Wt::WString);
	void sortByColumn(int, bool);

	void updatePagination();
	void showRows();

public:
	ResultSetView(Wt::WContainerWidget *parent = 0);
	ResultSetView(vector<string>, Wt::WContainerWidget *parent = 0);
	static const char *ItemSelectionMimeType;

	void setHeader(vector<string>);
	void setData(vector < vector<string> >);
	void createData(); ///< toma el modelo y lo guarda de la matriz <vector <vector>>
	void fillTable();
	void clearTable();

	TableView* getTable(){ return table; };

	void setMaxRows(int t){ maxRows = t; }
	void setPager(bool pager){ usePager = pager; }
	void setModel(ResultSetModel* model){ Model_ = model; }


	Wt::Signal<string>& onSelectedRow(){ return rowSelect; }

	~ResultSetView();
};
#endif /// RESULTSET_VIEW_H
