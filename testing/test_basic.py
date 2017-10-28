import pytest
import gpr


@pytest.fixture
def filename():
    return 'vendor/gpr/gcode_samples/linuxcnc_sample.ngc'


def test_read_from_file_contents(filename):
    with open(filename) as infile:
        program = gpr.parse_gcode(infile.read())
        assert len(program) == 30351


def test_read_from_filename(filename):
    program = gpr.parse_gcode_from_file(filename)
    assert len(program) == 30351
