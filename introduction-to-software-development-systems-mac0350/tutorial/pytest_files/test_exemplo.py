import pytest
from pytest_check import check
from exemplo1 import fatorial

def test_fatorial():
    fat = fatorial(5)
    
    with check:
        check.equal(fatorial(2), 5)
    with check:
        check.equal(fatorial(5),7)  
    with check:
        check.equal(fatorial(5),120)
    with check:
        check.equal(fatorial(4), 24)