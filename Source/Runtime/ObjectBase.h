//
// Created by ASUS on 10/04/2021.
//

#pragma once

#include "Util/Types.h"
#include <vector>

class CObjectBase
{
public:
    /**
     *
     */
    CObjectBase() = default;
    virtual ~CObjectBase() = default;

    /**
     * Curly braces initialize:
     *  {
     *      ...initialize code...
     *  }
     */
    virtual void PreInit() {}

    virtual void Init() {}
    virtual void PostInit() {}

    /**
     * Java finalize() method. Called before the object is GCed.
     */
    virtual void Finalize() {}

    virtual void MarkReferencedObjects()
    {
    }

private:

};

