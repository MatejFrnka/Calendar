POLYMOFISMUS

Polymorfismus je využíván hlavně v případě třídy Event. Z Eventu dědí třídy SingleEvent a RecurringEvent. Ze SingleEvent dědí RecurringItemEvent, což je SingleEvent vygenerovaný třídou RecurringEvent.
Při návrhu aplikace jsem čelil rozhodnutí, zda chci ve třídě EventManager, což je třída, která provádí operace se Eventy, plně využívat polymorfismus třídy Event a všechny je uložit to jednoho kontejneru (využívám std::set), nebo je rozdělit do kontejneru s SingleEvents a RecurringEvents.
Nakonec jsem se rozhodl pro použití dvou kontejnerů, jeden pro opakující se Eventy a jeden pro Neopakující se eventy. Toto rozhodnutí jsem učinil proto, že při získávání eventů v zadaném časovém rozmezí je v neopakujících se eventech možné binárně vyhledávat podle začátku události, zatímco opakující události se musí lineárně procházet. To je proto, že opakující událost může začínat před začátkem požadovaného rozmezí ale i přes to může generovat události dějící se v požadovaném časovém rozmezí.
Vzhledem k tomu, že očekávám, že větší množství událostí bude neopakujících se, si myslím, že tato optimalizace bude mít znatelný dopad na rychlost programu.
Toto rozdělení ale neznamená, že podtřídy Event nevyužívají polymorfismus. Ve většině operací se s nimi pracuje jako s třídou Event.
Polymorfismus bude využíván i při vykreslování událostí. Třída Draw bude předepisovat třídy DayDraw, WeekDraw, MonthDraw. Tyto třídy budou vykreslovat eventy různými způsoby. V případě pokračujícího vývoje bude velmi jednoduché přidat třídy typu Draw, které budou vykreslovat například do pdf, nebo jako webovou stránku.
Poslední využítí polymorfismu je ve třídě Action. Tato třída bude předepisovat možnost akcí. Například MoveAction, která event přesune, AttributeEditAction která upraví atribut nebo DeleteAction, která event smaže. EventManager bude ke každému eventu vracet list těchto akcí, které se poté zobrazí uživateli jako možnosti akcí, které může provést nad zvoleným eventem.
V této složce pod názvem class_diagram naleznete obrázek class diagramu tohoto programu.

