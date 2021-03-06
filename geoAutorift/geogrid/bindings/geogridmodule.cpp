/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright 2019 California Institute of Technology. ALL RIGHTS RESERVED.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * United States Government Sponsorship acknowledged. This software is subject to
 * U.S. export control laws and regulations and has been classified as 'EAR99 NLR'
 * (No [Export] License Required except when exporting to an embargoed country,
 * end user, or in support of a prohibited end use). By downloading this software,
 * the user agrees to comply with all applicable U.S. export laws and regulations.
 * The user has the responsibility to obtain export licenses, or other export
 * authority as may be required before exporting this software to any 'EAR99'
 * embargoed foreign country or citizen of those countries.
 *
 * Authors: Piyush Agram, Yang Lei
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */



#include <Python.h>
#include <string>
#include "geogrid.h"
#include "geogridmodule.h"

static const char * const __doc__ = "Python extension for geogrid";

PyModuleDef moduledef = {
    //header
    PyModuleDef_HEAD_INIT,
    //name of the module
    "geogrid",
    //module documentation string
    __doc__,
    //size of the per-interpreter state of the module;
    -1,
    geogrid_methods,
};

//Initialization function for the module
PyMODINIT_FUNC
PyInit_geogrid()
{
    PyObject* module = PyModule_Create(&moduledef);
    if (!module)
    {
        return module;
    }
    return module;
}

PyObject* createGeoGrid(PyObject* self, PyObject *args)
{
    geoGrid* ptr = new geoGrid;
    return Py_BuildValue("K", (uint64_t) ptr);
}

PyObject* destroyGeoGrid(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    if (!PyArg_ParseTuple(args, "K", &ptr))
    {
        return NULL;
    }

    if (((geoGrid*)(ptr))!=NULL)
    {
        delete ((geoGrid*)(ptr));
    }
    return Py_BuildValue("i", 0);
}

PyObject* setEPSG(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    int code;
    if (!PyArg_ParseTuple(args, "Ki", &ptr, &code))
    {
        return NULL;
    }
    ((geoGrid*)(ptr))->epsgcode = code;
    return Py_BuildValue("i", 0);
}

PyObject* setRepeatTime(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    double repeatTime;
    if (!PyArg_ParseTuple(args, "Kd", &ptr, &repeatTime))
    {
        return NULL;
    }
    ((geoGrid*)(ptr))->dt = repeatTime;
    return Py_BuildValue("i", 0);
}

PyObject* setRadarImageDimensions(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    int wid, len;
    if (!PyArg_ParseTuple(args, "Kii", &ptr, &wid, &len))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->nPixels = wid;
    ((geoGrid*)(ptr))->nLines = len;
    return Py_BuildValue("i", 0);
}

PyObject* setRangeParameters(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    double r0, rspace;
    if (!PyArg_ParseTuple(args, "Kdd", &ptr, &r0, &rspace))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->startingRange = r0;
    ((geoGrid*)(ptr))->dr = rspace;
    return Py_BuildValue("i", 0);
}

PyObject* setAzimuthParameters(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    double t0, prf;
    if (!PyArg_ParseTuple(args, "Kdd", &ptr, &t0, &prf))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->sensingStart = t0;
    ((geoGrid*)(ptr))->prf = prf;
    return Py_BuildValue("i", 0);
}

PyObject* setXLimits(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    double x0, x1;
    if (!PyArg_ParseTuple(args, "Kdd", &ptr, &x0, &x1))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->xmin = x0;
    ((geoGrid*)(ptr))->xmax = x1;
    return Py_BuildValue("i", 0);
}

PyObject* setYLimits(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    double x0, x1;
    if (!PyArg_ParseTuple(args, "Kdd", &ptr, &x0, &x1))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->ymin = x0;
    ((geoGrid*)(ptr))->ymax = x1;
    return Py_BuildValue("i", 0);
}

PyObject* setDEM(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    char* name;
    if (!PyArg_ParseTuple(args, "Ks", &ptr, &name))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->demname = std::string(name);
    return Py_BuildValue("i", 0);
}

PyObject* setVelocities(PyObject *self, PyObject* args)
{
    uint64_t ptr;
    char *vx;
    char *vy;
    if (!PyArg_ParseTuple(args, "Kss", &ptr, &vx, &vy))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->vxname = std::string(vx);
    ((geoGrid*)(ptr))->vyname = std::string(vy);
    return Py_BuildValue("i", 0);
}

PyObject* setSlopes(PyObject *self, PyObject* args)
{
    uint64_t ptr;
    char *sx;
    char *sy;
    if (!PyArg_ParseTuple(args, "Kss", &ptr, &sx, &sy))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->dhdxname = std::string(sx);
    ((geoGrid*)(ptr))->dhdyname = std::string(sy);
    return Py_BuildValue("i", 0);
}

PyObject* setWindowLocationsFilename(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    char* name;
    if (!PyArg_ParseTuple(args, "Ks", &ptr, &name))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->pixlinename = std::string(name);
    return Py_BuildValue("i", 0);
}

PyObject* setWindowOffsetsFilename(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    char* name;
    if (!PyArg_ParseTuple(args, "Ks", &ptr, &name))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->offsetname = std::string(name);
    return Py_BuildValue("i", 0);
}

PyObject* setRO2VXFilename(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    char* name;
    if (!PyArg_ParseTuple(args, "Ks", &ptr, &name))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->ro2vx_name = std::string(name);
    return Py_BuildValue("i", 0);
}

PyObject* setRO2VYFilename(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    char* name;
    if (!PyArg_ParseTuple(args, "Ks", &ptr, &name))
    {
        return NULL;
    }
    
    ((geoGrid*)(ptr))->ro2vy_name = std::string(name);
    return Py_BuildValue("i", 0);
}

PyObject* setLookSide(PyObject *self, PyObject *args)
{
    uint64_t ptr;
    int side;
    if (!PyArg_ParseTuple(args, "Ki", &ptr, &side))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->lookSide = side;
    return Py_BuildValue("i", 0);
}

PyObject* setOrbit(PyObject *self, PyObject *args)
{
    uint64_t ptr, orb;
    if (!PyArg_ParseTuple(args, "KK", &ptr, &orb))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->orbit = (cOrbit*)(orb);
    return Py_BuildValue("i", 0);
}


PyObject* geogrid(PyObject* self, PyObject* args)
{
    uint64_t ptr;
    if (!PyArg_ParseTuple(args, "K", &ptr))
    {
        return NULL;
    }

    ((geoGrid*)(ptr))->geogrid();
    return Py_BuildValue("i", 0);
}
