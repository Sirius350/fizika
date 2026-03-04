Fiziki szimulació pozitív és negatív töltésekre és ezek mozgására

A program kiszámolja azt hogy különböző töltesek hogyan hatnak egymásra es megjeleníti azt hogy ezek hogy mozognak egymáshoz képest.
A program c++ nyelvben az SFML segéd könyvtárak használatával készült Clion ban.
A program egy main.cpp, tavolsag.h, toltesek.h és egy toltesek.cpp böl áll.

A main.cpp ben van megvalósítása a program főb része az ablakmegjelenítés, a billentyűzet használata, a fizikai számolások, a töltések mozgatása és ha 2 ellentétes töltés találkozik azoknak az összeolvadását.

A tavolsag.h ban vannak a hosszab segéd fügvények 2 pont távolságának a számitása, a checkbox megjelenítésére használt fügvény, a fálj beolvasás és egy szinkiválasztó hozzá és a háttérben lévő rácsok megjelenítése.

A toltesek.h ebben található a toltesek osztály definiálása a fügvényeié is.

A toltesek.cpp ebben található a töltések osztály tagfügvényeinek a megvalósítása.

Miután ellet indítva a program kilehet választani hogy melyik induljon el.
Alapbol piros, ha rákkattintunk zöld lesz.
Ha piros állapotba enterrel továb lép akkor az adatok.txt böl olvassa ki a pontokat a billentyűzet funkcióinak a legtöbb sége kivan kapcsolva.
Ha zöld ként akkor az egér 
ballklik = pozitív piros 
jobbklik = negatív kék
h gomb lenyomásával és oda ahol az egér van = semleges sárga
Pontokat lerakni csak a rácsos hátterűre lehet és akkor lesz csak pontos ha alaphelyzetben van
Mind kettő funkcióba van
k gomb = törlés
esc = kilépés
nyilak = kamera mozgás
"+" és "-" = a t növelés és csökkentése
space-t nyomva tartva lehet az időt elindítani

Ha githubrol frissen fordítva let akkor a a cmake-build-debug ba kell
egy adatok.txt ami 1;0.01;960;540;0;0;Green ilyen sorrend ben tartalmazz az adatokat q_töltése;tömege;pozíció.x;pozíció.y;sebesség.x;sebesség.y;egy_alapszin
meg egy ARIAL.ttf nek is kell ott lennie
amennyiben nincsenek ott akkor hibásan fut le a program

A programban ha kettő ellentétes töltés találkozik akkor egy sárgává válnak ez a kettő közti terület közepén jön létre. Emiatt pár fizikai rész lehet hogy hibásan működik, de ez csak néhány esetben jönn elő.
Van 2 azonos egyenlő távolságra a közötte lévő sárgátol akkor az fog egyé válni vele amelyik hamarabb szerepel a listában.
Ha kettő azonos töltés teljesen egymáson van amikor elindítjuk akkor a program hibásan fog működni és vagy az egyik vagy mindegyik amelyek egymáson kezdtek ezok hibásak lesznek.
Ha a t nagyon nagyra vagy - ra  állítjuk akkor is megtud a program hibásodni, mert a prgoram nem lessz képes elég gyorsan számolni igy össze tudnak keveredni az adatok benne.

cmake_minimum_required az 4.1
c++ 20
sfml 3.0.2 
ezekben a verziókban készült

Készítette : Sümegi Zsombor és Schultz Márton
Készült: 2026.02.28