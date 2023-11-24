#include<iostream>
#include<math.h>

using std::cout;
using std::endl;

class Complex {
private:
    double real;
    double image;
public:
    Complex(double real_part=0.0, double image_part=0.0){
        this->real = real_part;
        this->image = image_part;
    }
    void display() const;
    double modulus() const;
    Complex operator = (const Complex c);
    Complex operator += (const Complex c);
    Complex operator + (const Complex b) const;
    Complex operator - (const Complex b) const;
    Complex operator * (const Complex b) const;
    Complex operator / (const Complex b) const;
};

void Complex::display() const{
    cout<<"Complex("<<real<<", "<<image<<")"<<endl;
}

double Complex::modulus() const{
    return sqrt(real * real + image * image);
}

Complex Complex::operator = (Complex c){
    this->real = c.real;
    this->image = c.image;
    return Complex(real, image);
}

Complex Complex::operator += (const Complex c){
    real += c.real;
    image = c.image;
    return Complex(real, image); 
}

Complex Complex::operator + (const Complex b) const{
    return Complex(real + b.real, image + b.image);
}

Complex Complex::operator - (const Complex b) const{
    return Complex(real - b.real, real + b.real);
}

Complex Complex::operator * (const Complex b) const{
    return Complex(real * b.real - image * b.image, real * b.image + image * b.real);
}

Complex Complex::operator / (const Complex b) const{
    double denominator = b.real * b.real + b.image * b.image;
    double result_real = real * b.real + image * b.image;
    double result_image = image * b.real - real * b.image;
    return Complex(result_real / denominator, result_image / denominator);
}


// int main(){
//     Complex c0 = Complex(1.2, 3.3);
//     Complex c1 = Complex(1.2, -3.3);
//     (c0 * c1).display();
//     c0.display();
//     c1.display();
//     Complex c;
//     c.display();
//     c = c0 / c1;
//     c.display();
// }