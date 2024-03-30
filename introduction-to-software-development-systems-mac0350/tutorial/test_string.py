import pytest

@pytest.mark.string
def test_str_equal():
    str1 = "oiee"
    str2 = "tchauu"
    assert str1==str2
    
@pytest.mark.string
def test_str_diff():
    str1 = "imee"
    str2 = "imee"
    assert str1==str2
    
@pytest.mark.outros
def test_str_int():
    str1 = "1"
    num1 = 1
    assert str1 != num1
    
