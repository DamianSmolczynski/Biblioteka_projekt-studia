#include <iostream>
#include <string>					//biblioteka do ˆ¥czenia string-ow
#include <fstream>					//biblioteka do obslugi plikow tekstowych
#include <cstdlib>					//biblioteka do obslugi exit()
#include <windows.h>				//biblioteka do pobierania czasu
#include <winbase.h>				//biblioteka do pobierania czasu
#include <conio.h>					//biblioteka do getch()

using namespace std;
									//funkcje do wyswietlania naglowkow
void naglowek_biblioteka()
{	cout<<"_______________________________BIBLIOTEKA______________________________\n";	}

void naglowek_wyszukiwanie_ksiazki()
{	cout<<"__________________________WYSZUKIWANIE KSI¤½KI_________________________\n";	}

void naglowek_wyszukiwanie_uzytkownika()
{	cout<<"________________________WYSZUKIWANIE U½YTKOWNIKA_______________________\n";  }

void naglowek_spis_ksiazek()
{	cout<<"______________________________SPIS KSI¤½EK______________________________\n"; }

struct ksiazka						//struktura ksiazki
{
	string nazwa,autor,ISBN;
	int liczba, nominalna;
};


struct uzytkownik					// struktura uzytkownika
{
	string imie, nazwisko, index, wypozyczenia;
	int kara;
};

	int nr_linii=1,nr=0;
	string linia;

ksiazka spis[10];					//deklaracja tablicy ksiazek

uzytkownik user[5];					//deklaracja tablicy user
string data_zwrotu,data_d;			//zmienne string do funkcji data(), czas_zwrotu()
string search;                		//string do wpisywania szukanej zmiennej
int n=-1,u=-1;						//zmienne uzywane do funkcji szukaj_ISBN() i szukaj_index()
bool running=true;					//bool running do sterowania wyjsciem z programu
bool error=false;					//bool error do sterowania wychodzenia z sekwencji w przypadku wystapienia problemu w wpisywaniu
bool check=false;					//bool check do sterowania poprawnoscia wyszukiwanej frazy
bool mozliwosc_wypozyczenia;		//bool mozliwosc_wypozyczenia do sterowania ta mozliwoscia	
bool mozliwosc_oddania;				//bool mozliwosc_oddania do sterowania ta mozliwoscia


void wczytanie_ksiazki();

void wczytanie_uzytkownikow();	

void ilosc_fizyczna_ksiazek();

void menu();
	void szukaj_ISBN();		void mozliwosc_wypozyczenia_oddania();		void menu_wyp_odd_stan();
																			void szukaj_index()	;
																			void wypozyczenie();
																				void czas_zwrotu();
																			void zwrot();
	void wypozyczenia_i_kary();				

void zapis_ksiazek();
	
void zapis_uzytkownikow();



main()
{
	wczytanie_ksiazki();
	wczytanie_uzytkownikow();
	czas_zwrotu();
	ilosc_fizyczna_ksiazek();
	while(running)
		{
			menu();
		}
	zapis_ksiazek();
	zapis_uzytkownikow();
	return 0;	
}

void zapis_uzytkownikow()					//funkcja zapisujaca zaaktualizowane dane na temat uzytkownikow po zakonczeniu pracy programu
{
	fstream plik_user1;
	plik_user1.open("index.txt",fstream::out);
	
	for(int i=0;i<5;i++)
	{
		plik_user1<<user[i].imie<<"\n";
		plik_user1<<user[i].nazwisko<<"\n";
		plik_user1<<user[i].index<<"\n";
		plik_user1<<user[i].wypozyczenia<<"\n";
		plik_user1<<user[i].kara<<"\n";
	
	}
	
	plik_user1.close();		
}

void zapis_ksiazek()						//funkcja zapisujaca zaaktualizowane dane na temat ksiazki po zakonczeniu pracy programu
{
	fstream plik_ksiazki1;			
	plik_ksiazki1.open("ksiazki.txt",fstream::out);
	
	for(int i=0;i<10;i++)
	{
		plik_ksiazki1<<spis[i].nazwa<<"\n";
		plik_ksiazki1<<spis[i].autor<<"\n";
		plik_ksiazki1<<spis[i].ISBN<<"\n";
		plik_ksiazki1<<spis[i].liczba<<"\n";
	}
	
	plik_ksiazki1.close();	
}

void wypozyczenia_i_kary()						//funkcja sterujaca algorytmem wyswietlajacym informacje na temat wypozyczen uzytkownika
{
	if(error==false)							//Warunek chroniacy przed przypadkiem krancowym(wyporzyczenie je¾eli poprzednie kroki posiadaly blad)
	{
	char a;
	cout<<user[u].index<<user[u].imie<<user[u].nazwisko<<"\n";
	cout<<"\n1.WY—WIETL INFORMACJE O WYPO½YCZENIACH\n";
	cout<<"0.POWRàT DO MENU\n";
	a=getch();
	system("cls");

		switch(a)								//swtich sterujacy wyswietlaniem w przypadku braku jak i dostepnosci wypozyczen na koncie uzytkownika
		{
			case '1':	
			{
				 if(user[u].wypozyczenia=="; ")
				 	{	naglowek_wyszukiwanie_uzytkownika();
						cout<<user[u].index<<user[u].imie<<user[u].nazwisko<<"\n\n"<<"BRAK WYPO½YCZONYCH KSI¤½EK\n";
						system("pause"); system("cls");
						break;
					}
				else
					{		
						naglowek_wyszukiwanie_uzytkownika();	cout<<user[u].index<<user[u].imie<<user[u].nazwisko<<"\n\n";
						cout<<"; WYPO½YCZENIE  DATA ZWROTU: \n"<<user[u].wypozyczenia<<"\n\n";	
						cout<<"KARA W PRZYPADKU ZWRàCENIA PO CZASIE: "<<user[u].kara<<"zl\n\n\n";
						system("pause"); system("cls");
						break;
					}
			}
			case '0':	{	break;	}
		
		}
	}
	
	else;										// W przypadku wczesniejszej deklaracji error=true, program przeleci przez funkcj© bez dzialan
}

void szukaj_index()						//Funkcja szukajaca indexu user-a
{
	if(error==false)
	{
	check=false;						//Reset bool check oraz int u
	u=-1;

	cout<<"INDEX: "; cin>>search;
	search=search+"; ";
	
	for(int i=0;i<5;i++)				//petla szukajaca tego samego ISBN i zapisujaca numer tablicy szukanej ksiaazki
	{
		
		int pozycja=(user[i].index).find(search);
		
		if(pozycja!=string::npos) 		//jesli znaleziono fraze 
			{
				u=i;					//przypisanie i do numeru indexu uzytkownika	
				check=true;
			}
		else{}	
	}

	if(check==true)
	{}
	else								// Warunek kt¢ry komunikuje zle wpisany index
		{
			error=true;					// Zmiana bool error na true (kolejne kroki zostana wylaczone, program powroci do menu bez wprowadzania zmian
			cout<<"PODANO NIEPRAWIDOWY INDEX\n";
			system("pause");
		}
	}
	else;								// W przypadku wczesniejszej deklaracji error=true, program przeleci przez funkcj© bez dzialan
	
}

void czas_zwrotu()
{
    int dni_miesiaca[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};	//Deklarowanie tablicy z iloscia dni w kazdym miesiacu
    
	SYSTEMTIME st;													// Pobieranie czasu przy uzyciu biblioteki <windows.h> i <winbase.h>
    GetSystemTime(&st);
    int dzien_1=st.wDay, miesiac_1=st.wMonth, rok_1=st.wYear;
																	//Kilka warunkow tworzacych dokladne daty oddania ksiazki
    if(dni_miesiaca[miesiac_1]%15==1 && dzien_1<=17)
    	{
        	dzien_1+=14;

    	}
    else if(dni_miesiaca[miesiac_1]%15==1 && dzien_1>17)
    	{
        	miesiac_1++;
        	dzien_1-=17;
    	}

    else if(dni_miesiaca[miesiac_1]%15==0 && dzien_1<=16)
    	{
    	    dzien_1+=14;
  	 	}
    else if(dni_miesiaca[miesiac_1]%15==0 && dzien_1>16)
		{
        	miesiac_1++;
        	dzien_1-=16;
    	}
    else if(dni_miesiaca[miesiac_1]==28 && dzien_1<=14)
    	{
        	dzien_1+=14;
    	}
    else if(dni_miesiaca[miesiac_1]==28 && dzien_1<=14)
    	{
        	dzien_1+=14;
    	}
																//Warunki kt¢re pomagaja tworzyc daty zwrotu ksiazki jednakowej dlugosci
	if(dzien_1<10 && miesiac_1<10)
		{
    		string dzien  =  to_string(dzien_1),	miesiac  =  to_string(miesiac_1),	rok  =  to_string(rok_1);
    		data_zwrotu	=	"0" +  dzien  +  ".0"  +  miesiac  +  "."  +  rok  +  "; ";
    	}
	else if(dzien_1<10)
		{
    		string dzien  =  to_string(dzien_1),	 miesiac  =  to_string(miesiac_1),	rok  =  to_string(rok_1);
    		data_zwrotu="0"+ dzien +"."+miesiac+"."+rok+"; ";
   		}
	else if(miesiac_1<10)
		{
    		string dzien  =  to_string(dzien_1),	 miesiac  =  to_string(miesiac_1),	rok=to_string(rok_1);
    		data_zwrotu  =  dzien  +  ".0"  +  miesiac  +  "."  +  rok  +  "; ";
		}

}

void wypozyczenie()						//Funckja wypozyczenia, ktora zmienia wymagane dane
{
	if(error==false)					//Warunek chroniacy przed przypadkiem krancowym(wyporzyczenie je¾eli poprzednie kroki posiadaly(blad)
		{                                          
			user[u].wypozyczenia  =  (user[u].wypozyczenia)  +  (spis[n].ISBN)  +  data_zwrotu;
			(spis[n].liczba)  =  (spis[n].liczba)  -  1;
			user[u].kara  +=  5;
			system("cls");
		}
		else;

}

void zwrot()							//Funckja wypozyczenia, ktora zmienia wymagane dane
{
	if(error==false)					//Warunek chroniacy przed przypadkiem krancowym(wyporzyczenie je¾eli poprzednie kroki posiadaly(blad)
	{
		string search=spis[n].ISBN;
	
		int pozycja=(user[u].wypozyczenia).find(search);
		
		if(pozycja!=string::npos) 		//jesli znaleziono fraze ISBN[n] w user[u].wypozyczenia
			{
				user[u].wypozyczenia.erase(pozycja,27);
				(spis[n].liczba)++;
				user[u].kara-=5;
				system("cls");
			}
		else{
				cout << "\n\nNIE UDAO SI¨ ZWRàCI KSI¤½KI. SPRAWD, CZY U½YTKOWNIK NA PEWNO J¤ WYPO½YCZY. \n\n";		system("pause"); system("cls");
			}
	}
	else;								// W przypadku wczesniejszej deklaracji error=true, program przeleci przez funkcj© bez dzialan
}

void menu_wyp_odd_stan()       	     	//funckja kt¢ra przy spelnionych warunkach prowadzi do wypozyczenia lub oddania ksiazki
{
	
	if(error==false)					//Warunek chroniacy przed przypadkiem krancowym(wyporzyczenie je¾eli poprzednie kroki posiadaly(blad)
	{
		char b;
		cout<<endl<<"\n";
		if(mozliwosc_wypozyczenia==true)		//*1*warunek sprawdzajacy czy ilosc egzemplarzy danej ksiazki nie jest rowna 0
			{	
				cout << "1.WYPO½YCZ" << "\n";
			}
		if(mozliwosc_oddania==true)				//*2*warunek sprawdzajacy czy ilosc egzemplarzy danej ksiazki jest mniejsza od calkowitej ilosci egzemlarzy w bibliotece 
			{
				cout << "2.ODDAJ" << "\n";
			}

	
		b=getch();
		system("cls");
	
		switch(b)
			{
				case '1':
				{
					if(mozliwosc_wypozyczenia==true) //*1*
						{	
							naglowek_wyszukiwanie_ksiazki();	szukaj_index();wypozyczenie(); break;
						}	
					else  { break; }	
				}
				case '2':
				{
					if(mozliwosc_oddania==true)	//*2*
						{
							naglowek_wyszukiwanie_ksiazki(); 	szukaj_index(); 	zwrot(); 	break;
						}
					else  { break; }
				}
				default: break;
			}
	}
	
	else;									// W przypadku wczesniejszej deklaracji error=true, program przeleci przez funkcj© bez dzialan
}

void mozliwosc_wypozyczenia_oddania()		//funkcja do sterowania mozliwoscia wypozyczenia i zwrotu
{
	if(spis[n].liczba==spis[n].nominalna)
		{	
			mozliwosc_oddania=false;
		} 
	else
		{
			mozliwosc_oddania=true;
		}
	
	if(spis[n].liczba<=spis[n].nominalna && spis[n].liczba>0)
		{
			mozliwosc_wypozyczenia=true;
		} 
	else
		{
			mozliwosc_wypozyczenia=false;
		}
}

void szukaj_ISBN()						//funkcja szukajaca numer tablicy
{	
	n=-1;								//reset n
	cout<<"WPISZ ISBN: "; cin>>search;
	search=search+"; ";					//dodanie 2 ostatnich znakow, dla unikcniecia bledow
	
	for(int i=0;i<10;i++)				//petla szukajaca tego samego ISBN i zapisujaca numer tablicy szukanej ksiaazki
	{
		int pozycja=(spis[i].ISBN).find(search);
		
		if(pozycja!=string::npos) 		//jesli znaleziono fraze ISBN
		{
			n=i;						//przypisanie i do numeru indexu uzytkownika
			check=true;						
		}
		else{}
	}
	if(check==true)
	{
	system("cls");
	naglowek_wyszukiwanie_ksiazki();
	cout<<"ISBN: "<<
	spis[n].ISBN<<"\nNazwa: "<<spis[n].nazwa<<"\nAutor: "<<spis[n].autor<<"\nDost©pne egzemplarze: "<<spis[n].liczba;
	
	}
	else								// Warunek kt¢ry komunikuje zle wpisany index
		{
			error=true;					// Zmiana bool error na true (kolejne kroki zostana wylaczone, program powroci do menu bez wprowadzania zmian
			cout<<"PODANO NIEPRAWIDOWY ISBN\n";
			system("pause"); system("cls");
		}
}

void menu()
{
	error=false; check=false;
	char a;
	naglowek_biblioteka();
	cout<<"1.WYSZUKAJ KSI¤½KE\n";
	cout<<"2.WYSZUKAJ U½YTKOWNIKA\n";
	cout<<"3.WYSWIETL SPIS KSI¤½EK\n";
	cout<<"4.WYJ—CIE\n";

	
	
	a=getch();
	system("cls");
	
	switch(a)
	{
		case '1':							//sekwencja umozliwiajaca wyszukanie, oddawanie i wypozyczanie ksiazki
					{	
						naglowek_wyszukiwanie_ksiazki(); 
						szukaj_ISBN();	mozliwosc_wypozyczenia_oddania();	menu_wyp_odd_stan();	 break;
					}	

		case '2':							//sekwencja umozliwiajaca 
					{
						naglowek_wyszukiwanie_uzytkownika();	szukaj_index();		system("cls");
						naglowek_wyszukiwanie_uzytkownika();	wypozyczenia_i_kary();		break;
					}

		case '3':	{
						naglowek_spis_ksiazek();
						for(int i=0;i<10;i++)						//sprawdzenie poprawnosci zapisu
							{
								cout<<spis[i].ISBN<<spis[i].nazwa<<spis[i].autor<<spis[i].liczba<<"\n";
							} 
						system("pause"); system("cls");	break;
					}	
		case '4':	{
						running=false;	break;
					}
		default: break;	

	}
	

}

void ilosc_fizyczna_ksiazek()					//funkcja wczytujaca ilosc magazynowa ksiazek
{
	fstream plik_fizyczna("ilosc_fizyczna_ksiazek.txt",fstream::in);
	
	if(plik_fizyczna.good()==false)				//sprawdzenie poprawnosci pliku
		{
			cout<<"PROGRAM NAPOTKA PROBLEM Z PLIKIEM ILOSC_FIZYCZNA_KSIAZEK.TXT, SPRAWD PLIK I URUCHOM BIBLIOTEK¨ PONOWNIE";
			exit(0);
		}
	
	int nr_linii=1,nr=0;
	string linia;
	
	while(getline(plik_fizyczna,linia))			//zapis wartosci w spis[i].nominalna
	{
		 spis[nr].nominalna=atoi(linia.c_str());	nr++;
	}
	
	plik_fizyczna.close();						//zamkniecie pliku po zakonczeniu uzywania
	nr_linii=1;nr=0;

}

void wczytanie_uzytkownikow()				//Funkcja sterujaca wczytaniem informacji o poszczegolnych uzytkownikach	
{
	fstream plik_user;
	
	plik_user.open("index.txt",fstream::in);
	
	if(plik_user.good()==false)				//sprawdzenie poprawnosci pliku
		{
			cout<<"PROGRAM NAPOTKA PROBLEM Z PLIKIEM INDEX.TXT, SPRAWD PLIK I URUCHOM BIBLIOTEK¨ PONOWNIE";
			exit(0);
		}
	while(getline(plik_user,linia))			//wczytanie wartosci w 	user[i].imie;	user[i].nazwisko;	user[i].index;	user[i].wypozyczenia;  user[i].kara;
		{
			switch(nr_linii)
				{	
					case 1: user[nr].imie=linia;						break;
					case 2: user[nr].nazwisko=linia;					break;
					case 3:	user[nr].index=linia;						break;
					case 4:	user[nr].wypozyczenia=linia;				break;
					case 5:	user[nr].kara=atoi(linia.c_str());	break;
				}
					nr_linii++;
						
					if(nr_linii==6)
						{
							nr_linii=1;nr++;
						}
		}

	plik_user.close();						//zamkniecie pliku po zakonczeniu uzywania
	nr_linii=1;nr=0;
				
}
void wczytanie_ksiazki()						//Funkcja sterujaca wczytaniem informacji o poszczegolnych ksiazkach
{
	fstream plik_ksiazki("ksiazki.txt",fstream::in);						
	
	
	
	if(plik_ksiazki.good()==false)				//sprawdzenie poprawnosci pliku
		{
			cout<<"PROGRAM NAPOTKA PROBLEM Z PLIKIEM KSIAZKI.TXT, SPRAWD PLIK I URUCHOM BIBLIOTEK¨ PONOWNIE";
			exit(0);
		}
	
	int nr_linii=1,nr=0;
	string linia;
	
	
	while(getline(plik_ksiazki,linia))			//wczytanie wartosci w 	spis[i].nazwa;	spis[i].autor;	spis[i].ISBN;	spis[i].liczba;
	{
			
						
						switch(nr_linii)
							{	
								case 1: spis[nr].nazwa=linia;					break;
								case 2: spis[nr].autor=linia;					break;
								case 3: spis[nr].ISBN=linia;					break;
								case 4:	spis[nr].liczba=atoi(linia.c_str());	break;
								
							}
						
						nr_linii++;
						
					
					if(nr_linii==5)
						{
						
							nr_linii=1;nr++;
							
						}
						
	}
	
	plik_ksiazki.close();					//zamkniecie pliku po zakonczeniu uzywania
	nr_linii=1;nr=0;
}