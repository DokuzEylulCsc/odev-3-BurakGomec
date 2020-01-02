// Odev3.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//
#include <fstream> //Okuyucu kütüphanesi//
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector> //Dinanik veri yapısı
using namespace std;


int DogrularıBul(vector<string> cevapanahtari,vector<string> ogrencicevaplar,int sorusayisi) {
	int ogrencidogrular = 0;//Dogru cevapları bulma metodu
	for (int i = 0; i <cevapanahtari.size(); i++) {
		if ((ogrencicevaplar[i]==cevapanahtari[i])) {
			ogrencidogrular++;
		}
	}
	//cout << "Ogrencinin dogru sayisi=" << ogrencidogrular << "\n";//Debug kontrolü
	return ogrencidogrular;
}
int BoscevaplariBul(vector<string> ogrencicevaplar, int sorusayisi) {
	//Bos cevapları bulma metodu
	int ogrenciboslar = 0;
	for (int i = 0; i < sorusayisi; i++) {
		if (ogrencicevaplar[i] == "") {
			ogrenciboslar++;
		}
	}
	//cout <<"Ogrencinin bosu="<< ogrenciboslar<<"\n"; //Debug kontrolü
	return ogrenciboslar;
}

void BuyuktenkucugeSirala(double ogrencinotları[], int ogrencisayisi) {
	double temp;
	for (int i = 0; i < ogrencisayisi; i++) {
		for (int j = 0; j < ogrencisayisi; j++)
		{//Ogrenci notlarini büyükten küçüğe sıralama metodu
			if (ogrencinotları[j] < ogrencinotları[j + 1])
			{
				temp = ogrencinotları[j];
				ogrencinotları[j] = ogrencinotları[j + 1];
				ogrencinotları[j + 1] = temp;
			}
		}

	}

}
	int main() {
		int sorusayilari;
		string cevapanahtarii[100];//Her satırı okurken split etmeden ayrı ayrı dizilere atılıyor,daha sonra regex ile split ediliyor
		string ogrenci1cevapp[100];
		string ogrenci2cevapp[100];
		ifstream dosyaOku("dosya.txt");
		string satir = ",";
		int i = 0;
		if (dosyaOku.is_open()) {
			cout << "Dosya okunmaya baslandi\n";
			while (getline(dosyaOku, satir)) {
				if (i == 0) {
					sorusayilari = atoi(satir.c_str());
				}
				else if (i == 1) {
					cevapanahtarii[0] = satir;
				}
				else if (i == 2) {
					ogrenci1cevapp[0] = satir;
				}
				else if (i == 3) {
					ogrenci2cevapp[0] = satir;
				}
				i++;
				cout << satir << "\n";
			//Öğrenci sayisi sabit olarak ele alindi
			}

			dosyaOku.close();
		}
		else { cout << "Dosya bulunamadi"; }

		vector<string> cevapanahtari;//Dinamik dizi oluşturulup içine split edilen cevaplar atılıyor

		regex regex(",|:|-|\\s+");//Virgül ve bosluğa göre split et

		vector<string> out(
			sregex_token_iterator(cevapanahtarii[0].begin(), cevapanahtarii[0].end(), regex, -1),

			sregex_token_iterator()


		);

		//regex regex("\\,"); //Virgüle göre split etme


		for (auto& s : out) {
			cevapanahtari.push_back(s);//Dinamik diziye split edilmiş elemanlar ekleniyor
		}
		
		
		vector<string> out1(
			sregex_token_iterator(ogrenci1cevapp[0].begin(), ogrenci1cevapp[0].end(), regex, -1),

			sregex_token_iterator()


		);
		vector<string> ogrenci1cevap;
		vector<string> ogrencino1;
		for (auto& s : out1) {
			if (s == "A" || s == "B" || s == "C" || s == "D" || s == "E" || s == "F" || s == "") {
				ogrenci1cevap.push_back(s);//Dinamik diziye split edilmiş elemanlar ekleniyor
			}
			else {
				ogrencino1.push_back(s);
			}
		}
		
		
		vector<string> out2(
			sregex_token_iterator(ogrenci2cevapp[0].begin(), ogrenci2cevapp[0].end(), regex, -1),

			sregex_token_iterator()


		);
		vector<string> ogrenci2cevap;
		vector<string> ogrencino2;
		for (auto& s : out2) {
			if (s == "A" || s == "B" || s == "C" || s == "D" || s == "E" || s == "F" || s=="") {
				ogrenci2cevap.push_back(s);//Dinamik diziye split edilmiş elemanlar ekleniyor
			}
			else {
				ogrencino2.push_back(s);
			}
			
		}

		/*for (int k = 0; k < ogrenci2cevap.size(); k++) {
			cout << ogrenci2cevap[k] << "\n"; //Debug kontrolü
		}*/


	//Dosya okunurken öğrenci sayısı 2 olarak ele alındı
	double ogrencinotları[100];//İstenen durum max 100 öğrenci
	double ogrenci1dogrular = 0; double ogrenci1yanlıslar = 0; double ogrenci1boslar = 0;
	double ogrenci2dogrular = 0; double ogrenci2yanlıslar = 0; double ogrenci2boslar = 0;

	ogrenci1dogrular=DogrularıBul(cevapanahtari,ogrenci1cevap,sorusayilari);
	ogrenci1boslar = BoscevaplariBul(ogrenci1cevap, sorusayilari);
	
	ogrenci2dogrular=DogrularıBul(cevapanahtari, ogrenci2cevap,sorusayilari);
	ogrenci2boslar = BoscevaplariBul(ogrenci2cevap, sorusayilari);

	
	ogrenci1yanlıslar = sorusayilari - (ogrenci1dogrular + ogrenci1boslar);//Yanlışların sayısını buluyoruz
	ogrenci2yanlıslar = sorusayilari - (ogrenci2dogrular + ogrenci2boslar);


	int ogrenci1notu = (4 * ogrenci1dogrular) + (-1 * ogrenci1yanlıslar);
	int ogrenci2notu= (4 * ogrenci2dogrular) + (-1 * ogrenci2yanlıslar);

	if (ogrenci1notu < 0 || ogrenci2notu < 0) {
		if (ogrenci1notu < 0) {
			ogrenci1notu = 0;
		}
		else if (ogrenci2notu < 0) {
			ogrenci2notu = 0;
		}
	}
	double tampuan = (sorusayilari * 4); //5*4=20
	double tampuanyap = 100/tampuan ;//Herkesin notu bu sayi ile carpılıp 100'e normalize edilecek

	ogrenci1notu *= tampuanyap;
	ogrenci2notu *= tampuanyap;
	//cout << ogrenci1notu;
	ogrencinotları[0] = ogrenci1notu;
	//cout << "\n";
	//cout << ogrenci2notu;
	ogrencinotları[1] = ogrenci2notu;
	//cout << "\n";
	BuyuktenkucugeSirala(ogrencinotları, 2);

	
	
	double endusuknot = 0;
	double enyukseknot = 0; double ortalama = 0; double medyan=0; double aciklik =0 ;
	enyukseknot = ogrencinotları[0];
	int elemansayisi = 2;
	endusuknot = ogrencinotları[elemansayisi-1];
	for (int i = 0; i < 2; i++) {
		ortalama += ogrencinotları[i];
	}
	ortalama = ortalama / 2;
	aciklik = enyukseknot - endusuknot;
	//Medyan Hesaplama
	if (elemansayisi % 2 == 0) {
		int ciftindis1 = (elemansayisi / 2);
		int ciftindis2=(elemansayisi / 2)+1;
		medyan += ogrencinotları[ciftindis1-1];
		medyan += ogrencinotları[ciftindis2-1];
		medyan = medyan / 2;
	}
	else {
		int tekindis = (elemansayisi + 1) / 2;
		medyan = ogrencinotları[tekindis-1];
	}
	cout << "En dusuk not= " << endusuknot << "\n";
	cout << "En yuksek not= " <<enyukseknot << "\n";
	cout << "Ortalama= " <<ortalama << "\n";
	cout << "Aciklik= " <<aciklik << "\n";
	cout << "Medyan= " <<medyan << "\n";
	//Odev3\Odev3=> icinde Output adında bir txt yaratılıyor ve veriler içine yazılıyor
	ofstream dosya; //Dosya yazımı bir sınıf 
	dosya.open("Output.txt"); //Output.txt isimli txt dosyası yaratılıyor,dosya açılma şartı
	dosya <<ogrencino1[0]<<","<<ogrenci1notu<<"\n";
	dosya << ogrencino2[0] << "," << ogrenci2notu<<"\n";
	dosya << "En dusuk not="<< endusuknot<<"\n";
	dosya <<"En yuksek not=" << enyukseknot<<"\n";
	dosya << "Ortalama=" << ortalama<<"\n";
	dosya << "Aciklik=" << aciklik<<"\n";
	dosya << "Medyan=" << medyan<<"\n";
	dosya.close();//Dosya kapanma şartı
	cout << "Dosya basariyla yazdirildi!";

}




// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
