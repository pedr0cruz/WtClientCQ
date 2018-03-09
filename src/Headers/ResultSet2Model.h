#ifndef RESULTSET2_MODEL_H
#define RESULTSET2_MODEL_H

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

// #include "ResultSetView.h"

using namespace Wt;
//using namespace std;

///	ResultSet2Model: Stores the data for a custom model.
/// This class inherits from WStandardItemModel to implement 
/// a custom model.
class ResultSet2Model : public WStandardItemModel ///< Guarda un modelo personalizado
{
public:
#ifdef MyDEBUG
	CQJSONdummy* cqSession;
#else
	CQJSON* cqSession;
#endif
	/// Constructor.
	ResultSet2Model(WObject *parent);

	bool fillModel(string QueryName);

protected:
	/// Vectores necesarios para tablas simples WTable
	vector < string > wTableHeader;
	vector < vector <string> > wTableData;
	vector < vector <string> > wTableFilterData;

	// Return the mime type.
//	virtual string mimeType() const {
//		return ResultSetView::ItemSelectionMimeType;
//	}
};


#endif /// RESULTSET2_MODEL_H
