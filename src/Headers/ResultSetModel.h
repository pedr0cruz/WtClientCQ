/// ResultSetModel.h

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

///	ResultSetModel: Stores the data for a custom model. This class 
/// inherits from WStandardItemModel to implement a custom model.
class ResultSetModel : public Wt::WStandardItemModel
{
public:
    /// Constructor
    /// @param rows Initial number of rows of the model
    /// @param cols Initial number of columns of the model
    /// @param parent Wt::WObject* Puntero a objeto padre para el ciclo de vida del objeto
    ResultSetModel(int rows, int cols, Wt::WObject *parent);

    /// Destructor
    virtual ~ResultSetModel();

    /// Llena el modelo con los datos de la consulta
    /// @param QueryName const string & Cadena de texto con el nombre de la consulta
    /// @return true en caso de éxito, false en caso de error
    bool fillModel(const std::string & QueryName);

private:
    static const char *ItemSelectionMimeType;

protected:
    ///  DATOS ESPECÍFICOS de cada modelo

#ifdef MyDEBUG
    CQJSONdummy* cqSession;
#else
    CQJSON* cqSession;
#endif

    /// Vectores necesarios para tablas simples WTable
    std::vector < std::string > wTableHeader;
    std::vector < std::vector <std::string> > wTableData;
    std::vector < std::vector <std::string> > wTableFilterData;

    /// FIN de DATOS ESPECÍFICOS de cada modelo

	/// Return the mime type.
	virtual std::string mimeType() const
    {
        return ItemSelectionMimeType;
	}
};

#endif /// RESULTSET_MODEL_H
