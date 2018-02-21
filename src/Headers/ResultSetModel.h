#ifndef RESULTSET_MODEL_H
#define RESULTSET_MODEL_H

#include <Wt/WObject>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WModelIndex>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>

#ifdef MyDEBUG
#include "CQJSONdummy.h"
#else
#include "CQJSON.h"
#endif

// #include "ResultSetView.h"

using namespace Wt;
//using namespace std;

class ResultSetModel : public WStandardItemModel // Guarda un modelo personalizado
{
public:
#ifdef MyDEBUG
	CQJSONdummy* cqSession;
#else
	CQJSON* cqSession;
#endif
	// Constructor.
	ResultSetModel(WObject *parent);

	bool fillModel(string QueryName);

protected:
	// Vectores necesarios para tablas simples WTable
	vector<string> wTableHeader;
	vector < vector<string> > wTableData;
	vector < vector<string> > wTableFilterData;

	// Return the mime type.
//	virtual string mimeType() const {
//		return ResultSetView::ItemSelectionMimeType;
//	}
};


#endif // RESULTSET_MODEL_H