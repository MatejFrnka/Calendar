# Calendar app

##Základní funkcionalita
Aplikace kalendář bude implementovat vložení, upravení, přesunutí a smazání událostí. K těmto událostem bude možné přidávat účastníky a místo konání.

##Jednorázové a opakující se události
Kalendář bude pracovat s jednorázovými a opakujícími se událostmi. Obě události budou definovány povinnými parametry `jméno události`, `začátek události` a `doba trvání` události. Opakující se událost bude navíc mít povinný parametr `čas mezi začátky události`, který určí, jak často se mají události opakovat a nepovinný parametr `opakovat do` který určí časový bod, po kterém už žádné události nebudou probíhat. Pokud tento parametr nebude zadán, bude se událost opakovat do nekonečna.

Opakující se událost bude uložena jako jedna událost, i přes to, že by jich mohlo být až nekonečno. Tato jedna událost bude generovat pod-události pouze pro časové rozmezí, které si uživatel zrovna zobrazuje.

##Pravidla událostí
V jeden čas bude moci probíhat vždy jen jedna událost. Pokud bude přidávána událost, v jejíž čas již probíhá jedna nebo více událostí, dá aplikace uživateli na výběr, zda vytvářenou událost nevytvořit nebo ji přesunout na nejbližší volný termín. 

Události půjdou upravovat, ovšem pouze pokud to událost bude povolovat (bude nastavena na upravitelnou událost). U opakujících se událostí bude na výběr upravit pouze jednu událost, všechny události nebo vybranou a všechny další události. 

##Vyhledávání
Pokud bude uživatel hledat konkrétní událost, bude ji moci vyhledat podle jména, místa nebo podle obojího.

##Zobrazení
Uživateli si bude si moci zobrazit události v režimu denní zobrazení, týdenní zobrazení a měsíční zobrazení. Celé UI bude v konzoli

##Export - Import,

Uživatel bude mít možnost exportovat a importovat události. Zároveň bude aplikace kalendář načítat události při spuštění a ukládat je při ukončení. 
