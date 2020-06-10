# Calendar app

##Základní funkcionalita
Aplikace kalendář bude implementovat vložení, upravení, přesunutí a smazání událostí. K těmto událostem bude možné přidávat účastníky a místo konání

##Zobrazení
Uživateli si bude moci zobrazit události v režimu denního, týdenního a měsíčního zobrazení. Celé UI bude v konzoli a bude ovládáno pomocí příkazů do konzole.

##Pravidla událostí
V jeden čas bude moci probíhat vždy jen jedna událost. Pokud bude přidávána událost, v jejíž čas již probíhá jedna nebo více událostí, dá aplikace uživateli na výběr, zda vytváření události zrušit nebo vyhledat nejbližší možný termín a vytvořit ji v něm. 

Události půjdou upravovat, ovšem pouze pokud to událost bude povolovat (bude nastavena na upravitelnou událost). U opakujících se událostí bude na výběr upravit pouze jednu událost, všechny události nebo vybranou a všechny další události. 

##Jednorázové a opakující se události
Kalendář bude pracovat s jednorázovými a opakujícími se událostmi. Obě události budou definovány povinnými parametry `jméno události`, `začátek události` a `doba trvání` události. Opakující se událost bude navíc mít povinný parametr `čas mezi začátky události`, který určí, jak často se mají události opakovat a nepovinný parametr `opakovat do` který určí časový bod, po kterém už žádné události nebudou probíhat. Pokud tento parametr nebude zadán, bude se událost opakovat do nekonečna.

Opakující se událost bude uložena jako jedna událost, i přes to, že by jich mohlo být až nekonečno. Tato jedna událost bude generovat pod-události pouze pro časové rozmezí, které si uživatel zrovna zobrazuje.


##Vyhledávání
Pokud bude uživatel hledat konkrétní událost, bude ji moci vyhledat podle jména, místa nebo podle obojího.

##Export - Import,

Uživatel bude mít možnost exportovat a importovat události. Zároveň bude aplikace kalendář načítat události při spuštění a ukládat je při ukončení. 

#Polymorfismus

##Události
U zpracování událostí je využíván polymorfisumus u normálních a opakujících se událostí. Z třídy `Event` dědí třídy `SingleEvent` a `RecurringEvent`. Ze SingleEvent dále dědí `RecurringItemEvent`, což je _pod-událost_ vygenerována třídou `RecurringEvent`

Při návrhu aplikace jsem čelil rozhodnutí, zda chci  plně využívat polymorfismus třídy `Event` a všechny je uložit to jednoho kontejneru (využívám `std::set`), nebo je rozdělit do dvou kontejnerů. `SingleEvents` a `RecurringEvents`.

Nakonec jsem se rozhodl pro použití dvou kontejnerů, jeden pro normální a druhý pro opakující se události. Toto rozhodnutí jsem učinil proto, že při vyhledávání událostí podle času (což bude s nejvyšší pravědpodobností nejčastější způsob vyhledávání, protože se bude používat při zobrazování událostí) je v neopakujících se událostech možné vyhledávat s logaritmickou rychlostí zatímco opakující se události se musí lineárně procházet.

Toto rozdělení ale neznamená, že _podtřídy_ `Event` nevyužívají polymorfismus. `Event` předepisuje například funkce `getEvents`, `freeSelf`, `isInRange`,.., Děděné třídy tyto funkce různě implementují.

##Vykreslování
Polymorfismus je využíván i při vykreslování událostí. Třída `Draw` předepisuje třídy `DayDraw`, `WeekDraw`, `MonthDraw`. Tyto třídy budou pomocí funkce `draw` vykreslovat eventy různými způsoby.

##Commands
Celý program je ovládán pomocí tříd dědících z `Command`. Tato třída předepisuje funkci `executeCommand`, kterou pak dědící třídy různě implementují. Například pokud uživatel zadá klíčové slovo `create single`, vyhledá se v seznamu commandů command s názvem `create` a zavolá se funkce `executeCommand`. Slovo `single` bude do této funkce předáno jako parametr. Pomocí něj pak `Command create` zavolá další command, který získá potřebné parametry (jméno, začátek a doba události) a vytvoří novou událost.