class Unit {
    // 
};

typedef struct Quantity{
    double value;
    Unit unit;
} Quantity;

typedef struct gasStatus {
    Quantity press;
    Quantity volumn;
    Quantity tempearture;
} gasStatus;