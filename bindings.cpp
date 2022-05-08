#include "include/nf.hpp"
#include "include/brush.hpp"
#include "include/window.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;


PYBIND11_MODULE(nuclear_fusion, m) {
    py::class_<nf::Window>(m, "Window")
        .def(py::init<>())
        .def("resize", &nf::Window::resize)
        .def("main", &nf::Window::main)
        .def("set_brush", &nf::Window::set_brush);
    
    py::class_<nf::Brush>(m, "Brush")
        .def(py::init<const char*, float, float>())
        .def("set_color", static_cast<void (nf::Brush::*)(uint8_t, uint8_t, uint8_t, uint8_t)>(&nf::Brush::setColor))
        .def("draw_line", &nf::Brush::draw_line, "window"_a, "x1"_a, "y1"_a, "x2"_a, "y2"_a, "step"_a=0.01)
        .def("draw_circle", &nf::Brush::draw_circle, "window"_a, "x"_a, "y"_a, "r"_a, "step"_a=0.01)
        .def("draw_ellipse", &nf::Brush::draw_ellipse, "window"_a, "x"_a, "y"_a, "rx"_a, "ry"_a, "step"_a=0.01);

    py::class_<nf::Vec2>(m, "Vec2")
        .def(py::init<float, float>())
        .def("rotate", static_cast<nf::Vec2 (nf::Vec2::*)(float, const nf::Vec2&, bool)>(&nf::Vec2::rotate),
            "angle"_a, "center"_a=nf::Vec2{0,0}, "is_degree"_a=false);
}
