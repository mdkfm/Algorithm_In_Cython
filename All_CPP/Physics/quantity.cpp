#include<cmath>
#include<iostream>

class Dimension {
private:
    int dmns[6]; // the degree of every dmn except 1
public:
    explicit Dimension(int const dmns[6]);
    Dimension(Dimension const &d);
    int addable(Dimension const &d) const;
    Dimension operator * (Dimension const &d) const;
    Dimension operator / (Dimension const &d) const;
    Dimension operator = (Dimension const &d);
};

Dimension::Dimension(int const dmns[6]){
    for(int i = 0; i < 6; i++){
        this->dmns[i] = dmns[i];
    }
}

Dimension::Dimension(Dimension const &d){
    for(int i = 0; i < 6; i++){
        dmns[i] = d.dmns[i];
    }
}

int Dimension::addable(Dimension const &d) const{
    int i;
    for(i = 0; i < 6; i++){
        if(dmns[i] != d.dmns[i]){
            return 0;
        }
    }
    return 1;
}

Dimension Dimension::operator * (Dimension const &d) const{
    int result[6], i;
    for(i = 0; i < 6; i++){
        result[i] = dmns[i] + d.dmns[i];
    }
    return Dimension(result);
}

Dimension Dimension::operator / (Dimension const &d) const{
    int result[6], i;
    for(i = 0; i < 6; i++){
        result[i] = dmns[i] - d.dmns[i];
    }
    return Dimension(result);
}

Dimension Dimension::operator = (Dimension const &d){
    for(int i = 0; i < 6; i++){
        dmns[i] = d.dmns[i];
    }
    return *this;
}

class Unit{
private:
    Dimension dmn;
public:
    Unit(int const dmns[6]);
    Unit(Dimension const &dmn);
    Unit(Unit const &unit);
    int addable(Unit const &unit) const;
    Unit operator * (Unit const &unit) const;
    Unit operator / (Unit const  &unit) const;
    Unit operator = (Unit const &unit);
};

Unit::Unit(int const dmns[6]): dmn(dmns){}

Unit::Unit(Dimension const &dmn): dmn(dmn){}

Unit::Unit(Unit const &unit): dmn(unit.dmn){}

int Unit::addable(Unit const &unit) const{
    return dmn.addable(unit.dmn);
}

Unit Unit::operator * (Unit const &unit) const{
    return Unit(dmn * unit.dmn);
}

Unit Unit::operator / (Unit const &unit) const{
    return Unit(dmn / unit.dmn);
}

Unit Unit::operator = (Unit const &unit){
    dmn = unit.dmn;
    return *this;
}

class Quantity{
private:
    double value;
    int oom; // order of magnitude
    Unit unit;
public:
    Quantity(double const value, int const oom, int const dmns[6]);
    Quantity(double const value, int const oom, Unit const &unit);
    void display() const;
    Quantity operator * (Quantity const &quantity) const;
    Quantity operator / (Quantity const &quantity) const;
    Quantity operator + (Quantity const &quantity) const;
    Quantity operator - (Quantity const &quantity) const;
};

Quantity::Quantity(double const value, int const oom, int const dmns[6]): unit(dmns){
    this->value = value;
    this->oom = oom;
}

Quantity::Quantity(double const value, int const oom, Unit const &unit): unit(unit){
    this->value = value;
    this->oom = oom;
}

void Quantity::display() const{
    std::cout << value << " * 10^" << oom << " * ";
    // unit.display();
}

Quantity Quantity::operator * (Quantity const &quantity) const{
    double result_value = value * quantity.value;
    int result_order_of_magnitude = oom + quantity.oom;
    Unit result_unit = unit * quantity.unit;
    return Quantity(result_value, result_order_of_magnitude, result_unit);
}

Quantity Quantity::operator / (Quantity const &quantity) const{
    double result_value = value / quantity.value;
    int result_order_of_magnitude = oom - quantity.oom;
    Unit result_unit = unit / quantity.unit;
    return Quantity(result_value, result_order_of_magnitude, result_unit);
}

Quantity Quantity::operator + (Quantity const &quantity) const{
    if(!unit.addable(quantity.unit)){
        throw "Unit not addable";
    }
    int result_oom = oom > quantity.oom ? oom : quantity.oom;
    double result_value = value * pow(10, oom - result_oom) + quantity.value * pow(10, quantity.oom - result_oom);
    return Quantity(result_value, result_oom, unit);
}

Quantity Quantity::operator - (Quantity const &quantity) const{
    if(!unit.addable(quantity.unit)){
        throw "Unit not addable";
    }
    double result_value = value - quantity.value;
    int result_order_of_magnitude = oom > quantity.oom ? oom : quantity.oom;
    return Quantity(result_value, result_order_of_magnitude, unit);
}

int main(){
    //test
    int dmns[6] = {1, 0, 1, 0, 1, 0};
    int dmns2[6] = {0, 1, 0, 1, 0, 1};
    Quantity q1(1, 0, Unit(dmns));
    Quantity q2(2, 0, Unit(dmns2));
    (q1 * q2).display();
    return 0;
}