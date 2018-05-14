/// RecordSetModel.h

#ifndef RECORDSET_MODEL_H
#define RECORDSET_MODEL_H

#pragma once

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

#include <string>
#include <vector>

///	Stores the data for a custom model. This class inherits 
/// from WStandardItemModel to implement a custom model.
class RecordSetModel : public Wt::WStandardItemModel
{
public:
	/// Constructor
    /// @param rows Initial number of rows of the model
    /// @param cols Initial number of columns of the model
    /// @param parent Wt::WObject* Puntero a objeto padre para el ciclo de vida del objeto
    RecordSetModel(int rows, int cols, Wt::WObject *parent);

	/// Llena modelo con datos para el elemento dado
    /// @param result_set const std::string & Cadena que especifica el conjunto de datos a usar
    bool fillModel(const std::string & result_set);

protected:

#ifdef MyDEBUG
    /// Puntero a Objeto que se comunica con el servidor y que se implementa 
    /// con el patrón Singleton. Esta es una variante de la clase que no
    /// utiliza ni necesita Las bibliotecas de ClearQuest.
    CQJSONdummy* cqSession;
#else
    /// Puntero a Objeto que se comunica con el servidor y que se implementa
    /// con el patrón Singleton. Esta es la variante oficial que utiliza las
    /// bibliotecas de ClearQuest y éstas son por tanto imprescindibles.
    CQJSON* cqSession;
#endif

    ///  DATOS del modelo

    std::vector < std::string > form_data_vec_;

    /// FIN de DATOS del modelo
};

#endif /// RECORDSET_MODEL_H
