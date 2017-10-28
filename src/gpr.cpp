#include <pybind11/pybind11.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "parser.h"

namespace py = pybind11;

gpr::gcode_program parse_from_file(std::string &filename) {
    std::ifstream infile(filename);
    std::string file_contents((std::istreambuf_iterator<char>(infile)),
            std::istreambuf_iterator<char>());
    return gpr::parse_gcode(file_contents);
}

PYBIND11_MODULE(gpr, m) {
    m.doc() = "GCODE parsing library";

    m.def("parse_gcode", &gpr::parse_gcode, "A function to parse gcode");
    m.def("parse_gcode_from_file", &parse_from_file, "Read gcode from file specified");

    py::enum_<gpr::address_type>(m, "AddressType")
        .value("Integer", gpr::address_type::ADDRESS_TYPE_INTEGER)
        .value("Double", gpr::address_type::ADDRESS_TYPE_DOUBLE)
        .export_values();

    py::enum_<gpr::chunk_type>(m, "ChunkType")
        .value("Comment", gpr::chunk_type::CHUNK_TYPE_COMMENT)
        .value("WordAddress", gpr::chunk_type::CHUNK_TYPE_WORD_ADDRESS)
        .value("Percent", gpr::chunk_type::CHUNK_TYPE_PERCENT)
        .value("Word", gpr::chunk_type::CHUNK_TYPE_WORD)
        .export_values();

    py::class_<gpr::addr>(m, "Address")
        .def(py::init<const gpr::address_type &, const gpr::addr_value &>())
        .def("address_type", &gpr::addr::tp)
        .def("double_value", &gpr::addr::double_value)
        .def("int_value", &gpr::addr::int_value)
        .def("print", &gpr::addr::print)
        ;

    py::class_<gpr::comment_data>(m, "CommentData")
        .def(py::init())
        .def(py::init<const char, const char, const std::string&>())
        .def_readwrite("left_delim", &gpr::comment_data::left_delim)
        .def_readwrite("right_delim", &gpr::comment_data::right_delim)
        .def_readwrite("comment_text", &gpr::comment_data::comment_text)
        ;

    py::class_<gpr::word_address_data>(m, "WordAddressData")
        .def(py::init())
        .def(py::init<const char, const gpr::addr>())
        .def_readwrite("wd", &gpr::word_address_data::wd)
        .def_readwrite("adr", &gpr::word_address_data::adr)
        ;

    py::class_<gpr::chunk>(m, "Chunk")
        .def(py::init())
        .def(py::init<const char>())
        .def(py::init<const char, const char, const std::string&>())
        .def(py::init<const char, const gpr::addr>())
        .def("chunk_type", &gpr::chunk::tp)
        .def("left_delim", &gpr::chunk::get_left_delim)
        .def("right_delim", &gpr::chunk::get_right_delim)
        .def("comment_text", &gpr::chunk::get_comment_text)
        .def("word", &gpr::chunk::get_word)
        .def("address", &gpr::chunk::get_address)
        .def("single_word", &gpr::chunk::get_single_word)
        ;

    py::class_<gpr::block>(m, "Block")
        .def(py::init<const int, const bool, const std::vector<gpr::chunk>>())
        .def(py::init<const bool, const std::vector<gpr::chunk>>())
        .def(py::init<const gpr::block&>())
        .def("to_string", &gpr::block::to_string)
        .def("__len__", &gpr::block::size)
        .def("__getitem__", &gpr::block::get_chunk)
        .def("line_number", &gpr::block::line_number)
        .def("__repr__", [](const gpr::block &block){
            return "<Block \"" + block.to_string() + "\">";
        })
        ;

    py::class_<gpr::gcode_program>(m, "Program")
        .def(py::init<const std::vector<gpr::block>>())
        .def("__len__", &gpr::gcode_program::num_blocks)
        .def("__getitem__", &gpr::gcode_program::get_block)
        .def("__repr__", [](const gpr::gcode_program &program) {
            return "<Program with " + std::to_string(program.num_blocks()) + " blocks>";
        })
        ;
}
