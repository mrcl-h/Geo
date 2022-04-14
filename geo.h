#include<iostream>

//lista figur geometrycznych
class Segment;
class Triangle;
class Line;
class Circle;

//lista przeksztalcen geometrycznych
/*jednokladnosc
 *obrot
 *przesuniecie o wektor
 *symetria wzgledem prostej
 *symetria wzgledem Pointu
 *przeksztalcenie afiniczne
 *inwersja
 *
 */

class Point{
public:
	double x,y;

	//Punkt o współrzędnych (1) i (2) +
	Point(double,double);

	//Punkt przecięcia dwóch prostych +
	Point(Line,Line);

	//czy oba Punkty są sobie równe +
	bool operator==(Point);

	//dodawanie (1) do punktu +
	Point operator+(Point);

	//odejmowanie (1) od Punktu +
	Point operator-(Point);

	//iloczyn o skalar +
	Point operator*(double);

	//iloczyn skalarny +
	double operator*(Point);

	//iloczyn wektorowy +
	double operator%(Point);

	//długość do (0,0) +
	double abs();

	//odległość do (1) +
 	double operator/(Point);

};

class Line{
public:

	double a, b, c;

	//Line ax+by+c=0 +
	Line(double,double,double);

	//prosta przechodząca przez (1) i (2) +
	Line(Point,Point);

	//prosta która biegnie przez przecięcia (1) i (2) +
	Line(Circle, Circle);

	//prosta która biegnie przez (1) +
	Line(Segment);

	// sprawdź czy równoległe do (1) +
	bool operator||(Line);

	//Punkt przecięcia tej prostej i (1) +
	Point operator*(Line);

	//prosta równoległa przez (1) +
	Line par(Point);

	//prosta prostopadla przez (1) +
	Line ortho(Point);
};

class Circle{
public:
	Point middle;
	double r;

	//Okrąg opisany na (1), (2), (3)
	Circle(Point,Point,Point);

	//Okrąg o środku w (1) i promieniu (2) +
	Circle(Point,double);

	//Okrąg o środku w (1) i promieniu (2) +
	Circle(Point,Point);

	//Okrąg opisany na (1) i (2)
	Circle(Segment, Point);

	//Okrąg opisany na (1)
	Circle(Triangle);
};

class Segment{
public:
	Point p1, p2;

	//Odcinek o krańcach w (1) i (2) +
	Segment(Point,Point);

	//Odcinek o  krańcach w punktach przecięcia (1) i (2)
	Segment(Circle,Circle);

	//Odcinek o krańcach w punktach przecięcia (1) i (2)
	Segment(Circle, Line);

	//dlugosc odcinka +
	double abs();

};

class Triangle{
public:
	Point A,B,C;

	//Trójkąt o Pointach (1), (2), (3) +
	Triangle(Point,Point,Point);

	//Trójkąt o punktach  przeciecia parami przez (1), (2), (3) +
	Triangle(Line,Line,Line);

	//obwod trójkąta +
	double perimeter();

	//pole trójkąta +
	double area();

	//czy trójkąt jest przystajacy do (1) +
	bool operator==(Triangle);

	//czy trójkąt jest podobny do (1) +
	bool operator!=(Triangle);
	/* c - okrąg
	 * p - Punkt
	 * l - prosta
	 */

	// okrąg wpisany w trójkąt
	Circle inscribed_c();

	// Okrąg opisany na trojkacie
	Circle circum_c();

	// Punkt przeciecia wysokosci trójkąta
	Point orthocenter();

	// Punkt przeciecia srodkowych trójkąta
	Point center_of_mass();

	// Prosta Eulera trójkąta
	Line euler_l();

	// prosta Nagela trójkąta
	Line nagel_l();

	// okrąg dziewięciu punktów trójkąta
	Circle nine_p_c();

};
//-------------Konstrukcje-----------------------

Point middle(Point, Point);

Point middle(Segment);

Line bisector(Line,Line);

Line bisector(Point,Point, Point);

Line tangent_to_c(Point, Line);

//Punkt na półprostej od (1) w kierunku (2) odległy o (3) od (1) +
Point lengthen(Point, Point, double);

//-------------Przekształcenia-------------------------

//jednokladnosc prostej (3) o skali (2) wzgledem Pointu (1)
Line homothety (Point, double, Line);

//jednokladnosc Pointu (3) o skali (2) wzgledem Pointu (1) +
Point homothety(Point, double, Point);

//jednokladnosc okregu (3) o skali (2) wzgledem Pointu (1)
Circle homothety(Point, double, Circle);

//jednokladnosc odcinka (3) o skali (2) wzgledem Pointu (1)
Segment homothety(Point, double, Segment);

//jednokladnosc Trianglea (3) o skali (2) wzgledem Pointu (1) +
Triangle homothety(Point, double, Triangle);
