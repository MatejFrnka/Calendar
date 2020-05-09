#POLYMOFISMUS
##Události
Polymorfismus je nejvíce využíván u práce s událostmi. Je dána abstraktní třída `Eventu` ze které dědí třídy `SingleEvent` a `RecurringEvent`. Ze SingleEvent dále dědí `RecurringItemEvent`, což je _pod-událost_ vygenerována třídou `RecurringEvent`

Při návrhu aplikace jsem čelil rozhodnutí, zda chci  plně využívat polymorfismus třídy `Event` a všechny je uložit to jednoho kontejneru (využívám `std::set`), nebo je rozdělit do dvou kontejnerů. `SingleEvents` a `RecurringEvents`.

Nakonec jsem se rozhodl pro použití dvou kontejnerů, jeden pro normální a druhý pro opakující se události. Toto rozhodnutí jsem učinil proto, že při vyhledávání událostí podle času (což bude s nejvyšší pravědpodobností nejčastější způsob vyhledávání, protože se bude používat při zobrazování událostí) je v neopakujících se událostech možné vyhledávat binárně, zatímco opakující-se události se musí lineárně procházet.

Toto rozdělení ale neznamená, že _podtřídy_ `Event` nevyužívají polymorfismus. `Event` například předepisuje funkce `getEvents`, `freeSelf`, `isInRange`,.., Děděné třídy tyto funkce různě implementují.
##Vykreslování
Polymorfismus bude využíván i při vykreslování událostí. Třída `Draw` bude předepisovat třídy `DayDraw`, `WeekDraw`, `MonthDraw`. Tyto třídy budou funkce `draw` vykreslovat eventy různými způsoby.

##Commands
Celý program bude ovládán pomocí tříd dědících z `Command`. Tato třída bude předepisovat funkci `executeCommand`, kterou budou dědící třídy různě implementovat. Například pokud uživatel zadá klíčové slovo `create single`, vyhledá se v seznamu commandů command s názvem `create` a zavolá se funkce `executeCommand`. Slovo `single` bude do této funkce předáno jako parametr.