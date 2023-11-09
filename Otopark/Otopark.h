#pragma once
#include <iostream>
#include <string>
#include <thread> // std::this_thread::sleep_for için
#include <chrono> // std::chrono::milliseconds için
/*
* list fonksiyonunda yapýlabilecekler menüsü açýlýr. Seçime göre iþlemi gerçekleþtirecek fonksiyona gidilir.
* araç çýkýþý için öncelikle þifre doðrulamasý istenir. 3 kez deneme hakkýna sahiptir.
*/
class Otopark
{
public:
	std::string userID = "suheda";
	std::string password = "bngl";
	std::string plaka;
	int counter = 0;
	int floor[5] = { 0,1,2,3,4 };	//Kat numaralarý
	int space[10] = { 1,2,3,4,5,6,7,8,9,10 };	//Alan numaralarý
	int option = 0;

	void menu();

	inline void vehicleList();
	inline void vehicleIn();
	inline void vehicleOut();
	bool passwordCheck();

	std::string passwordRegister[5][10];
	std::string parkingSpot[5][10];	//otopark katlarý
};

void Otopark::menu()
{
	
	std::cout << std::endl;

	std::cout << "Yapmak istediginiz islemi seciniz:" << std::endl;
	std::cout << "1 - Otopark arac listeleme" << std::endl;
	std::cout << "2 - Otopark arac girisi" << std::endl;
	std::cout << "3 - Otopark arac cikisi" << std::endl;
	std::cout << "4 - Cikis" << std::endl;
	std::cout << std::endl;
	std::cin >> option;

	switch (option)
	{
	case 1:
		std::cout << std::endl;
		vehicleList();
		break;
	case 2:
		std::cout << std::endl;
		vehicleIn();
		break;
	case 3:
		std::cout << std::endl;
		vehicleOut();
		break;
	case 4:
		std::cout << std::endl;
		std::cout << "Sistem kapandi.";
		break;
	}

}
// araç listesini ekrana yazdýrýr.
inline void Otopark::vehicleList() {

	std::cout << "Otopark arac listeleme" << std::endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (!parkingSpot[i][j].empty()) {
				std::cout << "Park yeri: " << "Kat " << i << "/ Alan " << j + 1 << std::endl;
				std::cout << "Plaka: " << parkingSpot[i][j] << std::endl;
			}
		}
	}
	// 5 saniye gecikme
	std::this_thread::sleep_for(std::chrono::seconds(5));
	
}
inline void Otopark::vehicleIn() {
	std::cout << "Otopark arac girisi" << std::endl << std::endl;
	int req = 0;

	std::cout << "Kat: ";	//kat numarasý istenir
	std::cin >> req;


	for (int j = 0; j < 10; j++) {
		if (parkingSpot[floor[req]][j].empty()) // istenilen katta boþ olan alanlar yazdýrýlýr
		{
			std::cout << floor[req] << ". kat " << j + 1 << ". alan bostur." << std::endl;
			std::cout << "Arac Plaka: ";		// kayýt edilecek araba plakasý giriþi
			std::cin >> plaka;
			parkingSpot[floor[req]][j] = plaka;	//boþ olan ilk alana kayýt yapýlýr.
			break;
		}
		else {
			continue;
			if (j == 9)
			{
				std::cout << "Bu katta bos alan yoktur. Yeniden deneyiniz." << std::endl;
			}
		}
	}

	menu();
}

// kullanýcý þifresi doðru girilmiþse sil
inline void Otopark::vehicleOut() {
	vehicleList();

	std::cout << "Arac cikisi yapilacak plakayi giriniz: ";
	std::cin >> plaka;
	std::cout << std::endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {

			if (plaka == parkingSpot[i][j]) {
				parkingSpot[i][j].clear();	// plaka eþleþiyorsa araç çýkýþý verilir.
				if (parkingSpot[i][j].empty())	//araç çýkýþý yapýldý mý? 
				{
					std::cout << "Park yeri bosaltilmistir." << std::endl;
					break;
				}					
			}
		}
	}

	menu();
}

bool Otopark::passwordCheck() {
	std::string passw;
	std::string id;

	std::cout << "Kullanici Adi:  ";
	std::cin >> id;

	std::cout << "Sifre giriniz:  ";
	std::cin >> passw;
	std::cout << std::endl;
	
	int passcheck = 1;

	while (passcheck != 3) {
		for (int i = 0; i < 5; i++) {
				for (int j = 1; j <= 10; j++) {
					if (passw == password || id == userID) {
						return 1;
					}
					else {
						passcheck++;
						return 0;
					}
				}
			}
	}
	if (passcheck == 3) {
		std::cout << "Sifreyi 3 kez yanlis girdiniz!" << std::endl;
	}
	
}

