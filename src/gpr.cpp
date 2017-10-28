#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(gpr, m) {
    m.doc() = "GCODE parsing library";
}
