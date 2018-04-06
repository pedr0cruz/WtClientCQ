#ifndef RECORDSET_MODEL_H
#define RECORDSET_MODEL_H

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
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

// #include "RecordSetView.h"

using namespace Wt;
//using namespace std;

///	RecordSetModel: Stores the data for a custom model.
/// This class inherits from WStandardItemModel to implement a custom model.
class RecordSetModel : public WStandardItemModel ///< Guarda un modelo personalizado
{
public:
#ifdef MyDEBUG
	CQJSONdummy* cqSession;
#else
	CQJSON* cqSession;
#endif
	/// Constructor.
	RecordSetModel(WObject *parent);

	bool fillModel(string QueryName);

protected:
	/// Vectores necesarios para tablas simples WTable
#if 0
	vector < string > wTableHeader;
	vector < vector <string> > wTableData;
	vector < vector <string> > wTableFilterData;
#endif

	// Return the mime type.
//	virtual string mimeType() const {
//		return ResultSetView::ItemSelectionMimeType;
//	}
};


#endif /// RECORDSET_MODEL_H
