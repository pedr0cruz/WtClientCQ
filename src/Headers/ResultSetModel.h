// ResultSetModel.h
//

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
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

///	ResultSetModel: Stores the data for a custom model.
/// This class inherits from WStandardItemModel to implement 
/// a custom model.
class ResultSetModel : public Wt::WStandardItemModel ///< Guarda un modelo personalizado
{
public:
    /// Constructor
    ResultSetModel(Wt::WObject *parent);

    /// Destructor
    virtual ~ResultSetModel();

    /// Llena el modelo con los datos de la consulta
    bool fillModel(string QueryName);

protected:

#ifdef MyDEBUG
    CQJSONdummy* cqSession;
#else
    CQJSON* cqSession;
#endif

    /// Vectores necesarios para tablas simples WTable
    std::vector < std::string > wTableHeader;
    std::vector < std::vector <std::string> > wTableData;
    std::vector < std::vector <std::string> > wTableFilterData;

	/// Return the mime type.
	virtual std::string mimeType() const
    {
        return ItemSelectionMimeType;
	}

private:
    static const char *ItemSelectionMimeType;
};

#endif /// RESULTSET_MODEL_H
