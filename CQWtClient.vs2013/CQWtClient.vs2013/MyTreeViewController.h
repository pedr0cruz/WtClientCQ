/// MyTreeViewController.h

#pragma once

#include "stdafx.h"

#include <Wt/WObject>

#include <string>

#include "ObserverGoF.h"

class MyTreeViewController 
    : public Wt::WObject
    , public SubjectGoF
{
public:
    MyTreeViewController(const std::string & name);
    virtual ~MyTreeViewController();
};

