# HONI-19-20

Arhiva radnog repozitorija za [Hrvatsko otvoreno natjecanje u informatici](https://hsin.hr/honi/sto_je.html), sezona 2019/2020.



## Bug bounty program
Neki zadaci na informatičkim natjecanjima nemaju jedinstven točan izlaz na svaki primjer. 
Kako bi bodovali natjecateljsko rješenje, prije natjecanja treba napisati *checker*, koji provjerava točnost izlaza.

Checker datoteke možete prepoznati po nazivima "checker_{en, hr}.{cpp, py}". 
Svi .cpp checkeri prate isti generični predložak, te je za očekivati da vrlo slični checkeri budu u upotrebi i iduće sezone.

Za uspješnu provedbu natjecanja bitno je da checkeri budu točni. 
Koliko je sastavljačima zadataka poznato, protekle sezone su se svi checkeri ponašali u skladu s očekivanjem.

Međutim, to ne znači da bugovi ne postoje. Štoviše, nijedne od prošlih sezona *izvorni kod checkera nije bio javan*. 
HONI komisija je svjesna da loši akteri od sada mogu pokušati iskoristiti mane checkera kako bi si neopravdano priskrbili bodove ili srušili sustav. 

Pokušaj hakiranja checkera za vrijeme službenog HONI/COCI kola smatra se varanjem i može rezultirati diskvalifikacijom.
Kako bi si ljudi mogli na legalan način udovoljiti znatiželji, otvaramo bug bounty program.

### Bounty:
Jedno pivo/topla čokolada (za maloljetne) za svaki bug gdje se checker ne ponaša očekivano, te bi loš akter time mogao kompromitirati bodovno stanje ili provedbu natjecanja.
(Na primjer, checker crasha, ili rješenje dobije manje bodova nego što bi mu ispravan checker dao.)
Bug koji utječe na više zadataka istovremeno ne dobiva više bountya. Dva buga koji se poprave na isti način se računaju samo za jedan bounty.

### Posebni bounty:
Za pronađen bug u generičnom dijelu checkera, koji uzrokuje da natjecateljsko rješenje dobije previše bodova bez prethodnog znanja ulaznih podataka,
dodijelit će se posebna nagrada nevelike novčane vrijednosti.

### Pravila
Prvih 10 bountya pokriva Daniel Paleka. Procjena zaslužuje li bug bounty je na HONI komisiji, te ništa ovdje napisano nije obvezujuće ni za koju stranu.


### Način prijave:
Otvorite issue na Githubu, stavite izvorni kod rješenja i opišite kako reproducirati bug.

