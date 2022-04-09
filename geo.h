#include<iostream>

//lista figur geometrycznych
class Odcinek;
class Trojkat;
class Prosta;
class Okrag;

//lista przeksztalcen geometrycznych
/*jednokladnosc
 *obrot
 *przesuniecie o wektor
 *symetria wzgledem prostej
 *symetria wzgledem punktu
 *przeksztalcenie afiniczne
 *inwersja
 *
 */

class Punkt{
public:
	double x,y;
	
	//punkt o współrzędnych (1) i (2) +
	Punkt(double,double);

	//punkt przecięcia dwóch prostych +
	Punkt(Prosta,Prosta);
	
	//czy oba punkty są sobie równe + 
	bool operator==(Punkt);
	
	//dodawanie (1) do punktu +
	Punkt operator+(Punkt);
	
	//odejmowanie (1) od punktu +
	Punkt operator-(Punkt);	
	
	//iloczyn o skalar +
	Punkt operator*(double);
	
	//iloczyn skalarny +
	double operator*(Punkt);
	
	//iloczyn wektorowy +
	double operator%(Punkt);
	
	//długość do (0,0) + 
	double abs();
	
	//odległość do (1) +
 	double operator/(Punkt);	

};

class Prosta{
public:
	
	double a, b, c;

	//prosta ax+by+c=0 +
	Prosta(double,double,double);

	//prosta przechodząca przez (1) i (2) +
	Prosta(Punkt,Punkt);

	//prosta która biegnie przez przecięcia (1) i (2) +
	Prosta(Okrag, Okrag);

	//prosta która biegnie przez (1) +
	Prosta(Odcinek);
	
	// sprawdź czy równoległe do (1) +
	bool operator||(Prosta);
	
	//punkt przecięcia tej prostej i (1) +
	Punkt operator*(Prosta);
	
	//prosta równoległa przez (1) +
	Prosta par(Punkt);
	
	//prosta prostopadla przez (1) +
	Prosta orto(Punkt);
};

class Okrag{
public:
	Punkt srodek;
	double r;

	//okrag opisany na (1), (2), (3)
	Okrag(Punkt,Punkt,Punkt);
	
	//okrag o środku w (1) i promieniu (2) +
	Okrag(Punkt,double);
	
	//Okrag o środku w (1) i promieniu (2) +
	Okrag(Punkt,Punkt);
	
	//Okrąg opisany na (1) i (2)
	Okrag(Odcinek, Punkt);
	
	//Okrąg opisany na (1)
	Okrag(Trojkat);
};

class Odcinek{
public:
	Punkt p1, p2;
	
	//odcinek o krańcach w (1) i (2) +
	Odcinek(Punkt,Punkt);
	
	//odcinek o  krańcach w punktach przecięcia (1) i (2)
	Odcinek(Okrag,Okrag);
	
	//odcinek o krańcach w punktach przecięcia (1) i (2)
	Odcinek(Okrag, Prosta);
	
	//dlugosc odcinka +
	double abs();

};

class Trojkat{
public:
	Punkt A,B,C;
	
	//Trojkat o punktach (1), (2), (3) +
	Trojkat(Punkt,Punkt,Punkt);
	
	//Trojkat o punktach przeciecia parami przez (1), (2), (3) +
	Trojkat(Prosta,Prosta,Prosta);
	
	//obwod trojkata +
	double obwod();
	
	//pole figury +
	double pole();
	
	//czy trojkat jest przystajacy do (1) +
	bool operator==(Trojkat);
	
	//czy trojkat jest podobny do (1) +
	bool operator!=(Trojkat);
	/* o - okrag
	 * pu - punkt
	 * pr - prosta
	 */
	
	// okrag wpisany w trojkat
	Okrag o_Wpisany();
	
	// okrag opisany na trojkacie
	Okrag o_Opisany();
	
	// punkt przeciecia wysokosci trojkata
	Punkt ortocentrum();
	
	// punkt przeciecia srodkowych trojkata
	Punkt pu_Ciezkosci();
	
	// prosta Eulera trojkata
	Prosta pr_Eulera();
	
	// prosta Nagela trojkata
	Prosta pr_Nagela();
	
	// okrag dziewieciu punktow trojkata
	Okrag o_dziewieciu_pu();
	
};
//odcinek od (1) w kierunku (2) o dlugosci (3) +
Punkt Przedluzenie(Punkt, Punkt, double);

//jednokladnosc prostej (3) o skali (2) wzgledem punktu (1)
Prosta jednokladnosc(Punkt, double, Prosta);

//jednokladnosc punktu (3) o skali (2) wzgledem punktu (1) +
Punkt jednokladnosc(Punkt, double, Punkt);

//jednokladnosc okregu (3) o skali (2) wzgledem punktu (1) 
Okrag jednokladnosc(Punkt, double, Okrag);

//jednokladnosc odcinka (3) o skali (2) wzgledem punktu (1) 
Odcinek jednokladnosc(Punkt, double, Odcinek);

//jednokladnosc trojkata (3) o skali (2) wzgledem punktu (1) +
Trojkat jednokladnosc(Punkt, double, Trojkat);