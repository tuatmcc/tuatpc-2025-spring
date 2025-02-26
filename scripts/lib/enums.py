from enum import Enum

class AggregateType(Enum):
    ALL = "all"
    SUM = "sum"
    MAX = "max"
    MIN = "min"

class Difficulty(Enum):
    MILK = "Milk"
    ASSAM = "Assam"
    BENIHUKI = "Benihuki"
    CEYLON = "Ceylon"
    DARJEELING = "Darjeeling"
    EARLGRAY = "Earlgray"
    FLAVOR = "Flavor"
    PAKCHI = "ผักชี"