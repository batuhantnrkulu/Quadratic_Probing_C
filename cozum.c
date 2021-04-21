#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int M = 16673; // tablo uzunlugu - > asal sayi
//Global degisken erisilebilir
char **hash_table;
//Flag arrayi kurularak hangi degerlerin null oldugunu gorecegiz.
int *flag;


void insert_quad_prob(int key, char *str){
	//hash_table hash tablosunu temsil eden bir array, key eklenecek key, ve M de hash tablosunun buyuklugudur.
	//Mod Division metodu kullaniyoruz.
	int hashIndex = key % M;
	//Eger bulunan konum bos ise oraya keyi ekle
	
	if(flag[hashIndex] == 0){
		strcpy(hash_table[hashIndex], str);
		flag[hashIndex] = 1;
	}
	else{
		int count = 0;
		int index = hashIndex;
		//Bos yer gorene dek donguyu calistir.
		//Quadratik Probing Kullanilir.
		while(flag[hashIndex] != 0){
			count++;
			//h(key, i) = (h1(key) + i^2) % m
			hashIndex += count * count;
			//array icinde circular dongu olmasi icin modunu aliyoruz.
			hashIndex %= M; 
		}
		// yer bulunduysa keyi o lokasyona ekle.
		if(flag[hashIndex] == 0){
			strcpy(hash_table[hashIndex], str);
			flag[hashIndex] = 1;
		}
	}
	return;
}


void read_from_file(char file_name[]){
	char str[30];
	FILE *fptr;
	int length, key;
	
	int i;
	
	fptr = fopen(file_name, "r");
	//Dosya sonuna kadar stringleri sirasiyla oku.
	int j = 1;
	while(fscanf(fptr, "%s", &str) != EOF){
		length = strlen(str);
		
		for(i = key = 0; i < length; i++){
			if(isupper(str[i]))
				key += ('a' - str[i]) * 26 * i;
			else
				key += (str[i] - 'a') * 26 * i;
		}
		
		
		//key eklenmesi icin fonksiyona yollanir.
		insert_quad_prob(key, str);
		key = 0;
		j++;
	}
}

int search(int key, char *str){
	int hashIndex = key % M;
	//bulunursa true donder.
	if(strcmp(hash_table[hashIndex], str) == 0){
		return 1;
	}
	else{
		int count = 0;
		int index = hashIndex;
		//Bos yer gorene dek donguyu calistir.
		//Quadratik Probing Kullanilir.
		while(strcmp(hash_table[hashIndex], str) != 0 && count < M){
			count++;
			//h(key, i) = (h1(key) + i^2) % m
			hashIndex += count * count;
			//array icinde circular dongu olmasi icin modunu aliyoruz.
			hashIndex %= M; 
		}
		// yer bulunduysa keyi true donder.
		if(strcmp(hash_table[hashIndex], str) == 0){
			return 1;
		}
	}
	return 0;
}
 
int main(void)
{
    int M = 16673; // tablo uzunlugu - > asal sayi
    
	char str[30];
	int length, key;
	int i;
	
	
	//Kullanicinin Istemesine bagli olmaksizin her 2 durum icin de hash tablosunu olustururuz.
    
    hash_table = (char **) malloc(sizeof(char *) * M);
    
 	for(i = 0; i < M; i++){
 		// her bir tablo hücresi 30 harflik olsun.
 		hash_table[i] = (char *) malloc(sizeof(char) * 30);
	}  
	
	flag = (int *)malloc(sizeof(int) * M);
 
    //Tüm flag elemanlar baslangicta 0 olarak belirlenir bu NULL degerinin temsilcisi.
    for (i = 0; i < M; i++)
    {
        flag[i] = 0;
    }
	
	char dosya_adi[30];
	scanf("%s", dosya_adi);
	read_from_file(dosya_adi);
	
	
	
	/*Tüm Elemanlari Gormek Icin
	for(i = 0; i < M; i++){
		printf("%s\n", hash_table[i]);
	}*/
	
	//Arama yapilacak Kelime
	scanf("%s", &str);
	length = strlen(str);
	
	for(i = key = 0; i < length; i++){
		
		// gelen string buyuk harflerden olusuyorsa kucuge cevirilir.
		str[i] = tolower(str[i]);
		
		if(isupper(str[i]))
			key += ('a' - str[i]) * 26 * i;
		else
			key += (str[i] - 'a') * 26 * i;
	}
	if(search(key, str) == 1){
		printf("%s", "Bulundu.");
	}
	else{
		//Oneri Kısmı - Her harf 26 kere degiserek aranmali ve Oneriler yazilmalidir.
		int j, k;
		puts("Bunu mu demek Istediniz:");
		for(i = 0; i < length; i++){
			char temp = str[i];
			
			for(j = 0; j < 26; j++){
				//buna gore modulu alinarak circular halde isleyecek.
				//tek tek harfler degistiriliyor.
				str[i]++;
				str[i] = (str[i] - 'a') % 26 + 'a';
				
				for(k = key = 0; k < length; k++){
					if(isupper(str[i]))
						key += ('a' - str[k]) * 26 * k;
					else
						key += (str[k] - 'a') * 26 * k;
				}
				
				if(search(key, str) == 1){
					printf("%s\n", str);
				}
			}
			//Onceki harfi yerine koyuyoruz.
			str[i] = temp;
		}
	}
    return 0;
}
 