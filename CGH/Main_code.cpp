#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fileapi.h>
#include <iomanip>
#include <complex>

const int N = 64;
const int p = 6;

void ft(double sign, std::complex<double> tab_SQ[N][N]);
void kwant_a(double input[N][N], int kwant);
void kwant_f(double input[N][N], int kwant);
std::string stopien_kwant(int kwant);

double error_psi(double tab_Ampl[N][N], double tab_Ampl_obiekt[N][N]);
double SNR(double tab_Ampl_obiekt[N][N], double tab_Ampl[N][N], double tab_Faza_obiekt[N][N], double tab_Faza[N][N]);

std::string otworz()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Wybierz plik";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "Sciezka do pliku: " << filename << "\n";
	}
	else
	{
		return 0;
	}

	return filename;
}

using namespace sf;
using namespace std;

bool click(Sprite check, RenderWindow& window)
{
	Vector2f mouse_pos = window.mapPixelToCoords(Mouse::getPosition(window));

	FloatRect bounds = check.getGlobalBounds();

	if (bounds.contains(mouse_pos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{

	std::string sciezka_input = "";

	///// Inicjalizacja trybu graficznego do wyboru parametrów programu /////

	RenderWindow window(VideoMode(600, 740), "Definicje funkcji programu", Style::None);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	window.setActive(true);

	bool kwant_b = false;
	bool siatka_bool = false;
	bool niest_b = false;
	bool kolor_b = false;
	bool flaga_wprowadzanie = false;

	std::string kwant_val = "";

	Font font1;
	if (!font1.loadFromFile("gothic.ttf"))
	{
		cout << "Blad wczytywania czcionki" << endl;
	}

	Texture ok_button;
	ok_button.loadFromFile("tekstury\\ok.png");

	Texture tak;
	tak.loadFromFile("tekstury\\tak.png");

	Texture nie;
	nie.loadFromFile("tekstury\\nie.png");

	Texture tak_s;
	tak_s.loadFromFile("tekstury\\tak_s.png");

	Texture nie_s;
	nie_s.loadFromFile("tekstury\\nie_s.png");

	Texture plik_texture;
	plik_texture.loadFromFile("tekstury\\plik.png");

	Texture bialy;
	bialy.loadFromFile("tekstury\\bialy.png");

	Texture czarny;
	czarny.loadFromFile("tekstury\\czarny.png");

	Texture bialy_s;
	bialy_s.loadFromFile("tekstury\\bialy_s.png");

	Texture czarny_s;
	czarny_s.loadFromFile("tekstury\\czarny_s.png");

	Texture blank;
	blank.loadFromFile("tekstury\\blank.png");

	Texture blank_s;
	blank_s.loadFromFile("tekstury\\blank_s.png");

	tak.setSmooth(true);
	tak.setRepeated(false);

	tak_s.setSmooth(true);
	tak_s.setRepeated(false);

	nie.setSmooth(true);
	nie.setRepeated(false);

	nie_s.setSmooth(true);
	nie_s.setRepeated(false);

	plik_texture.setSmooth(true);
	plik_texture.setRepeated(false);

	ok_button.setSmooth(true);
	ok_button.setRepeated(false);

	bialy.setSmooth(true);
	bialy.setRepeated(false);

	bialy_s.setSmooth(true);
	bialy_s.setRepeated(false);

	czarny.setSmooth(true);
	czarny.setRepeated(false);

	czarny_s.setSmooth(true);
	czarny_s.setRepeated(false);

	blank.setSmooth(true);
	blank.setRepeated(false);

	blank_s.setSmooth(true);
	blank_s.setRepeated(false);

	Sprite st_kwant;
	Sprite sn_kwant;

	st_kwant.setPosition(200, 200);
	sn_kwant.setPosition(320, 200);

	Sprite st_siatka;
	Sprite sn_siatka;

	st_siatka.setPosition(200, 330);
	sn_siatka.setPosition(320, 330);

	Sprite st_niest;
	Sprite sn_niest;

	st_niest.setPosition(200, 460);
	sn_niest.setPosition(320, 460);

	Sprite s_ok;
	s_ok.setPosition(250, 650);

	Sprite s_plik;
	s_plik.setPosition(260, 20);
	
	Sprite s_czarny;
	s_czarny.setPosition(200, 580);
	
	Sprite s_bialy;
	s_bialy.setPosition(320, 580);

	Sprite s_blank;
	s_blank.setPosition(440, 200);

	Text text0;
	text0.setFont(font1);
	text0.setFillColor(Color::White);
	text0.setPosition(210, 150);

	Text text1;
	text1.setFont(font1);
	text1.setFillColor(Color::White);
	text1.setString("Kwantowanie");
	text1.setPosition(210, 140);

	Text text2;
	text2.setFont(font1);
	text2.setFillColor(Color::White);
	text2.setString("Siatka");
	text2.setPosition(265, 270);

	Text text3;
	text3.setFont(font1);
	text3.setFillColor(Color::White);
	text3.setString("Wycinanie fragmentu widma");
	text3.setPosition(100, 400);

	Text text4;
	text4.setFont(font1);
	text4.setFillColor(Color::White);
	text4.setString("Kolor tekstur");
	text4.setPosition(220, 530);

	Text kwant_val_str;
	kwant_val_str.setFont(font1);
	kwant_val_str.setFillColor(Color::White);
	kwant_val_str.setPosition(450, 214);
	kwant_val_str.setCharacterSize(18);

	while (window.isOpen())
	{
		window.clear(Color::Black);

		text0.setString(sciezka_input);
		text0.setCharacterSize(18);
		text0.setPosition(window.getSize().x / 2 - text0.getLocalBounds().width / 2, 90);

		kwant_val_str.setString(kwant_val);

		s_ok.setTexture(ok_button);
		s_plik.setTexture(plik_texture);

		if (kwant_b == false)
		{
			st_kwant.setTexture(tak);
			sn_kwant.setTexture(nie_s);
		}
		if (kwant_b == true)
		{
			st_kwant.setTexture(tak_s);
			sn_kwant.setTexture(nie);
		}

		if (siatka_bool == false)
		{
			st_siatka.setTexture(tak);
			sn_siatka.setTexture(nie_s);
		}
		if (siatka_bool == true)
		{
			st_siatka.setTexture(tak_s);
			sn_siatka.setTexture(nie);
		}

		if (niest_b == false)
		{
			st_niest.setTexture(tak);
			sn_niest.setTexture(nie_s);
		}
		if (niest_b == true)
		{
			st_niest.setTexture(tak_s);
			sn_niest.setTexture(nie);
		}

		if (kolor_b == false)
		{
			s_czarny.setTexture(czarny_s);
			s_bialy.setTexture(bialy);
		}
		if (kolor_b == true)
		{
			s_czarny.setTexture(czarny);
			s_bialy.setTexture(bialy_s);
		}

		if (flaga_wprowadzanie == false)
		{
			s_blank.setTexture(blank);
		}
		if (flaga_wprowadzanie == true)
		{
			s_blank.setTexture(blank_s);
		}

		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);

		window.draw(st_kwant);
		window.draw(sn_kwant);

		window.draw(st_siatka);
		window.draw(sn_siatka);

		window.draw(st_niest);
		window.draw(sn_niest);

		window.draw(s_czarny);
		window.draw(s_bialy);

		window.draw(s_ok);
		window.draw(s_plik);

		window.draw(text0);

		if (kwant_b == true)
		{
			window.draw(s_blank);
			window.draw(kwant_val_str);
		}

		Event ev;

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
				case Event::MouseButtonPressed:
				{

					if (click(st_kwant, window) == true) 
					{
						kwant_b = true;
					}
					if (click(sn_kwant, window) == true)
					{
						kwant_b = false;
					}

					if (click(st_niest, window) == true)
					{
						niest_b = true;
					}
					if (click(sn_niest, window) == true)
					{
						niest_b = false;
					}

					if (click(st_siatka, window) == true)
					{
						siatka_bool = true;
					}
					if (click(sn_siatka, window) == true)
					{
						siatka_bool = false;
					}

					if (click(s_bialy, window) == true)
					{
						kolor_b = true;
					}
					if (click(s_czarny, window) == true)
					{
						kolor_b = false;
					}

					if (click(s_ok, window) == true)
					{
						if (sciezka_input != "")
						{
							window.close();
						}
					}

					if (click(s_plik, window) == true)
					{
						sciezka_input = otworz();
					}

					if (click(s_blank, window) == false)
					{

						flaga_wprowadzanie = false;

					}

					if (click(s_blank, window) == true)
					{

						flaga_wprowadzanie = true;
				
					}
				}

				case Event::KeyPressed:
				{

					if (flaga_wprowadzanie == true)
					{

						if (kwant_val.size() < 8)
						{

							if (Keyboard::isKeyPressed(Keyboard::Num1))
							{
								kwant_val.append("1");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num2))
							{
								kwant_val.append("2");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num3))
							{
								kwant_val.append("3");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num4))
							{
								kwant_val.append("4");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num5))
							{
								kwant_val.append("5");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num6))
							{
								kwant_val.append("6");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num7))
							{
								kwant_val.append("7");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num8))
							{
								kwant_val.append("8");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num9))
							{
								kwant_val.append("9");
							}
							if (Keyboard::isKeyPressed(Keyboard::Num0))
							{
								kwant_val.append("0");
							}
						}

						if (Keyboard::isKeyPressed(Keyboard::BackSpace))
						{
							if (kwant_val.size() > 0)
							{
								kwant_val.pop_back();
							}
						}
					}
				}
			}
		}

		window.display();
	}
	
	////// Deklaracje zmiennych, u¿ywanych w programie /////

	bool siatka_b = siatka_bool;
	bool kwantowanie_b = kwant_b;

	if (kolor_b == true)
	{
		kolor_b = false;
	}
	else
	{
		kolor_b = true;
	}

	bool tryb_b = kolor_b;
	bool wytnij_b = niest_b;

	const double M_PI = 3.14159265358979323846;

	complex<double> jUrojona(0.0, 1.0);

	complex<double> tab_SQ[N][N];

	double tab_Ampl[N][N] = { 0 };
	double tab_Faza[N][N] = { 0 };

	double tab_Ampl_old[N][N] = { 0 };
	double tab_Faza_old[N][N] = { 0 };

	double tab_Ampl_obiekt[N][N] = { 0 };
	double tab_Faza_obiekt[N][N] = { 0 };

	int tab_obiektA[N][N] = { 0 };	
	int tab_obiektF[N][N] = { 0 };

	int i, j;

	double ampl_old = 0;
	double faza_old = 0;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_SQ[i][j] = polar(0.0, 0.0);
		}
	}

	float pi = 3.14159265358979323846;

	int space = 0;
	int pspace = 0;
	int licz_lin = 0;

	int slash_pos = 0;
	int slash_last_pos = 0;

	char* path;
	_get_pgmptr(&path);

	std::string curr_path = path;

	std::string in_line = "";

	std::string line;
	std::string bef;
	std::string stringchar;
	std::string nazwa_ampl_wejscie;
	std::string nazwa_faza_wejscie;

	std::string nazwa_docelowa_faza;
	std::string nazwa_docelowa_ampl;

	std::string nazwa_docelowa_fold;
	std::string nazwa_docelowa_fold_obiekt;
	std::string nazwa_docelowa_fold_widmo;
	std::string nazwa_docelowa_fold_input;

	///// Deklaracja œcie¿ek, u¿ywanych w programie /////

	while (curr_path.find('\\', slash_last_pos) != -1) {

		slash_pos = curr_path.find('\\', slash_last_pos);

		slash_last_pos = slash_pos + 1;

	}

	int str_dl = curr_path.size();

	for (int i = slash_pos; i < str_dl; i++) {

		curr_path.pop_back();

	}

	nazwa_docelowa_fold = curr_path + "\\output";

	if (CreateDirectory(nazwa_docelowa_fold.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Stworzono folder output" << endl;
	}
	else
	{
		cout << "Nie udalo sie stworzyc folderu" << endl;
	}

	nazwa_docelowa_fold_obiekt = curr_path + "\\output\\obraz";

	if (CreateDirectory(nazwa_docelowa_fold_obiekt.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Stworzono folder obraz" << endl;
	}
	else
	{
		cout << "Nie udalo sie stworzyc folderu" << endl;
	}

	nazwa_docelowa_fold_widmo = curr_path + "\\output\\widmo";

	if (CreateDirectory(nazwa_docelowa_fold_widmo.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Stworzono folder widmo" << endl;
	}
	else
	{
		cout << "Nie udalo sie stworzyc folderu" << endl;
	}

	nazwa_docelowa_fold_input = curr_path + "\\output\\input";

	if (CreateDirectory(nazwa_docelowa_fold_input.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Stworzono folder input" << endl;
	}
	else
	{
		cout << "Nie udalo sie stworzyc folderu" << endl;
	}

	cout << "Kopiowanie pliku wejsciowego... ";

	std::string nazwa_docelowa_input = nazwa_docelowa_fold + "\\input\\input.txt";

	CopyFile(sciezka_input.c_str(), nazwa_docelowa_input.c_str(), false);

	cout << "Zakonczone." << endl;

	ifstream input(nazwa_docelowa_input.c_str(), ios::in);

	///////// Czytanie wejœcia z pliku //////////

	j = 0;

	while (getline(input, in_line))
	{
		int size = in_line.size();
		
		if (size > N) 
		{
			return 0;
		}

		for (int i = 0; i < size; i++)
		{
			if ((int)in_line[i] - 48 == 1)
			{
				tab_SQ[j][i] = polar(1.0, 0.0);
				tab_Ampl_obiekt[j][i] = 1.0;
				tab_Faza_obiekt[j][i] = 0.0;

				tab_obiektA[j][i] = 1;
				tab_obiektF[j][i] = 0;
			}
		}

		j++;

		if (j > N) 
		{
			return 0;
		}
	}

	input.close();

	////////// Zmiana obiektu w widmo ///////////

	ft(1.0, tab_SQ);

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_Ampl[i][j] = abs(tab_SQ[i][j]);
			tab_Faza[i][j] = arg(tab_SQ[i][j]);
		}
	}

	////////// Opcjonalne kwantowanie ///////////

	cout << endl;

	int kwant_stopien = 0;
	stringstream kwant_sstream;

	kwant_sstream << kwant_val;
	kwant_sstream >> kwant_stopien;

	if (kwantowanie_b == true)
	{
		kwant_a(tab_Ampl, kwant_stopien);
		kwant_f(tab_Faza, kwant_stopien);
	}

	///// Opcjonalne wycinanie fragmentów widma /////

	if (wytnij_b == true)
	{
		int il_pol = 0;
		int index1, index2, index3, index4;

		cout << "Ile pol wycinac?: ";
		cin >> il_pol;

		for (int i = 0; i < il_pol; i++)
		{
			cout << "Podaj indeksy " << i + 1 << " pola: "<<endl;
			cout << "Poczatek - x: ";
			cin >> index1;
			cout << "Poczatek - y: ";
			cin >> index2;
			cout << "Koniec - x: ";
			cin >> index3;
			cout << "Koniec - y: ";
			cin	>> index4;

			for (int i = index1; i <= index3; i++)
			{
				for (int j = index2; j <= index4; j++)
				{
					tab_Ampl[i][j] = 0.0;
				}
			}
		}
	}

	///// Przepisanie danych w celu póŸniejszego wyœwietlenia /////
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tab_Ampl_old[i][j] = tab_Ampl[i][j];
			tab_Faza_old[i][j] = tab_Faza[i][j];
		}
	}


	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_SQ[i][j] = polar(tab_Ampl[i][j],tab_Faza[i][j]);
		}
	}

	///// Zapis danych widma /////

	std::string sciezka_out_SQ_1 = curr_path + "\\output\\widmo\\tab_SQ_widmo.txt";
	ofstream zap1(sciezka_out_SQ_1.c_str(), ios::out | ios::trunc);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			zap1 << tab_SQ[i][j];
			zap1 << " ";

		}

		zap1 << endl;
	}

	zap1.close();

	std::string sciezka_out_AM_2 = curr_path + "\\output\\widmo\\tab_AM_widmo.txt";
	ofstream zap2(sciezka_out_AM_2.c_str(), ios::out | ios::trunc);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			zap2 << tab_Ampl_old[i][j];
			zap2 << " ";

		}

		zap2 << endl;
	}

	zap2.close();

	std::string sciezka_out_FA_2 = curr_path + "\\output\\widmo\\tab_FA_widmo.txt";
	ofstream zap3(sciezka_out_FA_2.c_str(), ios::trunc | ios::out);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			zap3 << tab_Faza_old[i][j];
			zap3 << " ";

		}

		zap3 << endl;
	}

	zap3.close();

	///// Zmiana widma w obraz /////
	
	ft(-1.0, tab_SQ);

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_Ampl[i][j] = abs(tab_SQ[i][j]);
			tab_Faza[i][j] = arg(tab_SQ[i][j]);

			if (tab_Faza[i][j] < 0) {
				tab_Faza[i][j] += pi * 2;
			}
		}
	}
	
	///// Obliczanie wspó³czynnika odwzorowania obrazu (PSI) i stosunku sygna³u do szumu (SNR) /////
		
	double psi = error_psi(tab_Ampl_obiekt, tab_Ampl);
	double snr = SNR(tab_Ampl_obiekt, tab_Ampl, tab_Faza_obiekt, tab_Faza);

	stringstream snr_sstream;
	stringstream psi_sstream;

	snr_sstream << scientific << snr;
	psi_sstream << setprecision(6) << fixed << psi;

	std::string snr_str;
	std::string psi_str;

	snr_sstream >> snr_str;
	psi_sstream >> psi_str;

	///// Czêœæ graficzna - zapis tekstur z wynikami obliczeñ //////
	
	RenderTexture texture;
	RenderTexture texture2;
	RenderTexture texture3;
	RenderTexture texture4;

	texture.create(2908, 2980);
	texture2.create(2908, 2980);
	texture3.create(2908, 2980);
	texture4.create(2908, 2980);

	Font font;

	Text text_obiekt;
	Text text_obraz;
	Text text_widmo;
	Text text_hologram;

	if (!font.loadFromFile(curr_path+"\\gothic.ttf"))
	{
		cout<<"Blad wczytywania czcionki"<<endl;
	}

	text_obiekt.setFont(font);
	text_obraz.setFont(font);
	text_widmo.setFont(font);
	text_hologram.setFont(font);

	if (tryb_b == true)
	{
		text_obiekt.setFillColor(Color::White);
		text_widmo.setFillColor(Color::White);
		text_obraz.setFillColor(Color::White);
	}
	else
	{
		text_obiekt.setFillColor(Color::Black);
		text_widmo.setFillColor(Color::Black);
		text_obraz.setFillColor(Color::Black);
	}

	text_hologram.setFillColor(Color::White);

	text_obiekt.setPosition(20, texture.getSize().y - 60);
	text_obraz.setPosition(20, texture.getSize().y - 60);
	text_widmo.setPosition(20, texture.getSize().y - 60);
	text_hologram.setPosition(20, texture.getSize().y - 60);

	RectangleShape siatka(Vector2f(45, 45));
	siatka.setOutlineColor(Color::Yellow);
	siatka.setOutlineThickness(1);
	siatka.setOrigin(siatka.getSize().x / 2, siatka.getSize().y / 2);

	RectangleShape prostokat(Vector2f(15, 45));
	prostokat.setOrigin(prostokat.getSize().x / 2, prostokat.getSize().y / 2);

	CircleShape kropka(1.875);
	kropka.setFillColor(Color::Red);
	kropka.setPointCount(100);
	kropka.setOrigin(1.875, 1.875);

	if (tryb_b == true)
	{
		prostokat.setFillColor(Color::White);
		siatka.setFillColor(Color::Black);
	}
	else
	{
		prostokat.setFillColor(Color::Black);
		siatka.setFillColor(Color::White);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tab_Ampl_old[i][j] = pow(tab_Ampl_old[i][j], 2);
		}
	}

	bool flaga1 = false;

	double max_amp = tab_Ampl_old[0][0];
	double max_amp2 = tab_Ampl[0][0];

	double calk_amp = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tab_Ampl_old[i][j] = log(tab_Ampl_old[i][j] + 1);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tab_Ampl_old[i][j] > max_amp)
			{
	
				max_amp = tab_Ampl_old[i][j];

			}

			calk_amp += tab_Ampl_old[i][j];

		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tab_Ampl[i][j] > max_amp2)
			{
				max_amp2 = tab_Ampl[i][j];
			}
		}
	}

	std::string text_obraz_comb = "Obraz - kwantowanie " + stopien_kwant(kwant_stopien) + ", PSI - " + psi_str + ", SNR - " + snr_str + ".";
	std::string text_widmo_comb = "Widmo - kwantowanie " + stopien_kwant(kwant_stopien) + ", maksymalne natezenie - " + to_string(max_amp) + ", calkowite natezenie - " + to_string(calk_amp) + ".";
	std::string text_holo_comb = "Hologram - kwantowanie " + stopien_kwant(kwant_stopien) + ", maksymalne natezenie - " + to_string(max_amp) + ", calkowite natezenie - " + to_string(calk_amp) + ".";

	text_obiekt.setString("Obiekt");
	text_obraz.setString(text_obraz_comb);
	text_widmo.setString(text_widmo_comb);
	text_hologram.setString(text_holo_comb);

	if (tryb_b == true)
	{
		texture.clear(Color::Black);
		texture2.clear(Color::Black);
		texture3.clear(Color::Black);
		texture4.clear(Color::Black);
	}
	else
	{
		texture.clear(Color::White);
		texture2.clear(Color::White);
		texture3.clear(Color::White);
		texture4.clear(Color::Black);
	}

	int offset_x = 30;
	int offset_y = 30;

	for (int f = 0; f < 4; f++)
	{
		// Pierwsze wykonanie petli -> f==0 -> widmo
		// Drugie   wykonanie petli -> f==1 -> obraz
		// Trzecie  wykonanie petli -> f==2 -> obiekt
		// Czwarte  wykonanie petli -> f==3 -> hologram

		offset_x = 30;
		offset_y = 30;

		for (int j = 0; j < N; j++)
		{

			for (int i = 0; i < N; i++)
			{

				float faza;
				float amplituda = 0;

				if (f == 0 || f == 3) 
				{
					faza = tab_Faza_old[j][i];
					amplituda = tab_Ampl_old[j][i];
				}
				else if (f == 1)
				{
					faza = tab_Faza[j][i];
					amplituda = tab_Ampl[j][i];
				}
				else
				{
					faza = tab_obiektF[j][i];
					amplituda = tab_obiektA[j][i];
				}

				if (faza > pi)
				{
					faza -= pi * 2;
				}

				float faza_p = (siatka.getSize().x * 2 / 3) / (pi * 2) * faza;

				if (f == 0)
				{
					prostokat.setSize(Vector2f(45 * amplituda / max_amp, 45 * amplituda / max_amp));
					prostokat.setPosition((offset_x - 15) + (45 - prostokat.getSize().x) / 2, offset_y + (45 - prostokat.getSize().y) / 2);
				}

				if (f == 1)
				{
					prostokat.setSize(Vector2f((45 * amplituda) / max_amp2, 45 * amplituda / max_amp2));
					prostokat.setPosition((offset_x - 15) + (45 - prostokat.getSize().x) / 2, offset_y + (45 - prostokat.getSize().y) / 2);
				}

				if (f == 2)
				{
					prostokat.setSize(Vector2f(45, 45 * amplituda));
					prostokat.setPosition(offset_x - 15, offset_y);
				}

				if (f == 3)
				{
					prostokat.setSize(Vector2f(15, (45 * amplituda) / max_amp));
					prostokat.setPosition(offset_x + faza_p, offset_y + (45 - prostokat.getSize().y) / 2);
					prostokat.setFillColor(Color::White);
					siatka.setFillColor(Color::Black);
				}

				siatka.setPosition(offset_x, offset_y);
				kropka.setPosition(offset_x, offset_y);

				if (f == 0)
				{
					texture.setActive(true);

					if (siatka_b == true) {
						texture.draw(siatka);
					}

					texture.draw(prostokat);

					if (siatka_b == true) {
						texture.draw(kropka);
					}
				}
				else if (f == 1)
				{
					texture2.setActive(true);

					if (siatka_b == true) {
						texture2.draw(siatka);
					}

					texture2.draw(prostokat);

					if (siatka_b == true) {
						texture2.draw(kropka);
					}
				}
				else if (f == 2)
				{
					texture3.setActive(true);

					if (siatka_b == true)
					{
						texture3.draw(siatka);
					}

					texture3.draw(prostokat);

					if (siatka_b == true)
					{
						texture3.draw(kropka);
					}
				}
				else if (f == 3)
				{
					texture4.setActive(true);

					if (siatka_b == true) {
						texture4.draw(siatka);
					}

					texture4.draw(prostokat);

					if (siatka_b == true) {
						texture4.draw(kropka);
					}
				}

				offset_x += 45;

			}

			offset_y += 45;
			offset_x = 30;

			texture.draw(text_widmo);
			texture2.draw(text_obraz);
			texture3.draw(text_obiekt);
			texture4.draw(text_hologram);

			texture.display();
			texture2.display();
			texture3.display();
			texture4.display();

		}
	}

		///// Zapis wygenerowanych tekstur do plików /////

		if (flaga1 == false) 
		{
			texture.display();
			texture2.display();
			texture3.display();
			texture4.display();

			std::string sciezka = curr_path + "\\output\\widmo.png";
			std::string sciezka2 = curr_path + "\\output\\obraz.png";
			std::string sciezka3 = curr_path + "\\output\\obiekt.png";
			std::string sciezka4 = curr_path + "\\output\\widmo_hologram.png";

			cout << endl << "Zapisywanie tekstur: " << endl;

			cout << "Widmo... ";
			texture.getTexture().copyToImage().saveToFile(sciezka);
			cout << "Zakonczone." << endl << "Obraz... ";
			texture2.getTexture().copyToImage().saveToFile(sciezka2);
			cout << "Zakonczone." << endl << "Obiekt... ";
			texture3.getTexture().copyToImage().saveToFile(sciezka3);
			cout << "Zakonczone." << endl << "Hologram... ";
			texture4.getTexture().copyToImage().saveToFile(sciezka4);
			cout << "Zakonczone." << endl;

		//////////  Zapis danych do plików  ///////////

			std::string sciezka_out_SQ = curr_path + "\\output\\obraz\\tab_SQ_obraz.txt";
			ofstream zap1_1(sciezka_out_SQ.c_str(), ios::out | ios::trunc);

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{

					zap1_1 << tab_SQ[i][j];
					zap1_1 << " ";

				}

				zap1_1 << endl;
			}

			zap1_1.close();

			std::string sciezka_out_AM = curr_path + "\\output\\obraz\\tab_AM_obraz.txt";
			ofstream zap2_1(sciezka_out_AM.c_str(), ios::out | ios::trunc);

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{

					zap2_1 << tab_Ampl[i][j];
					zap2_1 << " ";

				}

				zap2_1 << endl;
			}

			zap2_1.close();

			std::string sciezka_out_FA = curr_path + "\\output\\obraz\\tab_FA_obraz.txt";
			ofstream zap3_1(sciezka_out_FA.c_str(), ios::trunc | ios::out);
			
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{

					zap3_1 << tab_Faza[i][j];
					zap3_1 << " ";

				}

				zap3_1 << endl;
			}

			zap3_1.close();

			cout << "Zapisywanie zakonczone" << endl;

			flaga1 = true;

		}
	
	system("pause");

	return 0;
}