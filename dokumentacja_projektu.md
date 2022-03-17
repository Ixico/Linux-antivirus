
# Antywirus dla systemu z jądrem Linux

## Eryk Muchorowski

## Spis treści

- [Dynamiczna i statyczna linkowalność](#dynamiczna-i-statyczna-linkowalność)
- [Algorytm funkcji skrótu](#algorytm-funkcji-skrótu)
- [Uruchomienia i wyłączanie aplikacji](#uruchomienia-i-wyłączanie-aplikacji)
- [Uprawnienia uruchomieniowe aplikacji](#uprawnienia-uruchomieniowe-aplikacji)
- [Statystyki wydajnościowe działania](#statystyki-wydajnościowe-działania)
- [Przypadki użycia](#przypadki-użycia)
- [Mechanizm kwarantanny](#mechanizm-kwarantanny)
- [Czystość kodu i praktyki programistyczne](#czystość-kodu-i-praktyki-programistyczne)
- [Statyczna analiza kodu](#statyczna-analiza-kodu)
- [Testowanie aplikacji](#testowanie-aplikacji)
- [Unikanie błędów bezpieczeństwa](#unikanie-błędów-bezpieczeństwa)


### Dynamiczna i statyczna linkowalność
## Algorytm funkcji skrótu
Przy wyborze funkcji skrótu rozważono trzy kluczowe aspekty:
1. Standardowe wybory twórców baz danych
2. Wydajność programu  
3. Aspekty bezpieczeństwa  

### Standardowe wybory twórców baz danych
Większość baz danych open-source znajdujących się w Internecie, korzysta głównie z trzech funkcji skrótu:
- MD5
- SHA-1
- SHA-256

Główną część stanowiła jednak teoretycznie przestarzała już funkcja **MD5**.

Przykładowe popularne bazy skrótów złośliwych programów:
- [Team Cymru](https://team-cymru.com/community-services/mhr/) - SHA-1, SHA-256, MD5  
- [Github](https://github.com/CYB3RMX/MalwareHashDB) - MD5  
- [Virusshare](https://virusshare.com/hashes) - MD5  

### Wydajność programu
W kwestii wydajnościowej zdecydowano się na sprawdzenie wydajności trzech wcześniej wspomnianych funkcji.  

**Założenia dotyczące testowania:**
- Testy przeprowadzone były przy pomocy narzędzia **OpenSSL** z poziomu Linuxa (jest to ta sama biblioteka, która używana jest w implementacji Antywirusa).
- Sprzęt, na którym przeprowadzono testy:
  - Procesor Intel Core i5-1135G7 2.40GHz 11. generacji
  - 8GB ramu wydzielona na wirtualną maszynę w środowisku VirtualBox
- Wykorzystano komendę 'openssl speed'. Testuje ona funkcje skrótu poprzez liczenie przez 3 sekundy kolejno bloki coraz większych rozmiarów  

Wyniki przeprowadzonych testów przedstawione są w kB/s:

| funkcja\blok[B] | 16 | 64  | 256 | 1024 | 8192 | 16384 |
|-----------------|----|-----|-----|------|------|-------|
| MD5             |  72029.19k  |   178245.55k  |   302214.06k  |   372617.56k    |  409523.54k    |   416950.95k    |
| SHA-1           |  81141.97k  |   171779.63k   |  311560.13k   |   397080.58k    |   399493.80k    |  394575.87k     |
| SHA-256         |  37970.48k  |   82089.60k  |    128531.03k |   160539.65k   |     178978.82k |   170716.90k    |

Funkcje **SHA-1** oraz **MD5** cechują się podobną wydajnością, zaś **SHA-256** jest dwukrotnie wolniejsza pod względem przeliczonych bajtów na sekundę.

### Aspekty bezpieczeństwa
- **SHA-1** jak i **MD5** są już oficjalnie wycofane i nie powinny być używane w nowych aplikacjach
- **SHA-256** cały czas jest obowiązującym standardem
- W przypadku Antywirusa głównym celem funkcji skrótu jest identyfikacja pliku
- Kolizyjność funkcji w przypadku słabszego algorytmu, może prowadzić do tzw. False Positive, czyli sytuacji, w których teoretycznie bezpieczny plik zostanie uznany za niebezpieczny, gdyż jego skrót koliduje ze skrótem pewnego złośliwego oprogramowania.

### Decyzja projektowa - MD5
Biorąc pod uwagę wcześniej rozważone aspekty, w Antywirusie rolę funkcji skrótu będzie stanowić **MD5**. Wynika to z faktu, iż jest ona najbardziej powszechna w przypadku wykorzystania (dużo baz skrótów złośliwego oprogramowania open-source). Ponadto wypada ona bardzo
dobrze w testach wydajnościowych. Jej największą wadą jest kolizyjność, jednak poziom prawdopodobieństwa kolizji równy <img src="https://render.githubusercontent.com/render/math?math=1.47\cdot10^{-29}"> [(*Avira)](https://www.avira.com/en/blog/md5-the-broken-algorithm) jest zdecydowanie akceptowalny.

## Uruchomienia i wyłączanie aplikacji
## Uprawnienia uruchomieniowe aplikacji
## Statystyki wydajnościowe działania
## Przypadki użycia
## Mechanizm kwarantanny
## Czystość kodu i praktyki programistyczne
## Statyczna analiza kodu
## Testowanie aplikacji
## Unikanie błędów bezpieczeństwa