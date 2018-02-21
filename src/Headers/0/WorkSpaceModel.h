#ifndef WORKSPACE_MODEL_H
#define WORKSPACE_MODEL_H

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

using namespace Wt;

class WorkSpaceModel : public WStandardItemModel
{
public:
	WorkSpaceModel( WObject* parent );
	bool fillModel();
protected:
#ifdef MyDEBUG
	CQJSONdummy* cqSession;
#else
	CQJSON* cqSession;
#endif
	WModelIndex         wsItem_;
	/// Mapas para la descripcion de los elementos del WS
	std::map<std::string, WString> wsNameMap_;
	std::map<std::string, WStandardItem*> wsItemMap_;
	std::map<std::string, Json::Object*> jsonObjectMap_;

private:
	WStandardItem* createFolderItem(const WString& location, const std::string& wsId = std::string());
	WStandardItem* createElementItem(const WString& location, const std::string& wsId = std::string(), Json::Object &joItem = Json::Value());

};

#endif WORKSPACE_MODEL_H