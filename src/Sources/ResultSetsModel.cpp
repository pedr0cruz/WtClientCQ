// ResultSetsModel.cpp
// Representa el Modelo en el MVC del ResultSet
// Se conecta con el CQ y contruye la tabla de elementos JSON del RS

#include "stdafx.h"

#include <boost/algorithm/string/replace.hpp>

#include "ResultSetsModel.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

#if !defined (FALSE_DEFINED)
#	define FALSE         0
#	define FALSE_DEFINED 1
#endif
#if !defined (TRUE_DEFINED)
#	define TRUE          0
#	define TRUE_DEFINED  1
#endif

// Constructor
ResultSetsModel::ResultSetsModel(WObject* parent) : WStandardItemModel(parent)
{
    currentTabIndex_ = 0;
}

ResultSetsModel::~ResultSetsModel()
{
}

// Actualiza el modelo
bool ResultSetsModel::fillModel(int selectedTabIndex)
{
    bool changed = (currentTabIndex_ != selectedTabIndex);
    currentTabIndex_ = selectedTabIndex;
    return changed;
}

