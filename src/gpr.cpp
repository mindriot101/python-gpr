#include <pybind11/pybind11.h>
#include <iostream>
#include "parser.h"

namespace py = pybind11;

PYBIND11_MODULE(gpr, m) {
    m.doc() = "GCODE parsing library";

    m.def("parse_gcode", &gpr::parse_gcode, "A function to parse gcode");

    py::enum_<gpr::address_type>(m, "AddressType")
        .value("Integer", gpr::address_type::ADDRESS_TYPE_INTEGER)
        .export_values();

    py::class_<gpr::addr>(m, "Address");

    py::class_<gpr::chunk>(m, "Chunk");

    py::class_<gpr::block>(m, "Block");

    py::class_<gpr::gcode_program>(m, "Program");
}
