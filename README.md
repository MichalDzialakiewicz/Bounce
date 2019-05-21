# Bounce

**Opis i zasady gry**

Bounce to gra zręcznościowa polegająca na poruszaniu się kulą w taki sposób, by, omijając przeszkody, przejść przez wszystkie obręcze i dojść do mety. Plansza gry składa się z następujących elementów:
- sterowana kula posiadająca pewną liczbę żyć,
- ściany definujące zakres ruchu kuli,
- obręcze, z którymi zetknięcie jest konieczne do ukończenia poziomu,
- kolczaste słupki stanowiące przeszkodę odbierającą jeden punkt życia kuli,
- bonusowe punkty, których zebranie jest opcjonalne,
- dodatkowe punkty życia kuli.

Sterowanie:
- W - skok,
- A - ruch w lewo,
- D - ruch w prawo.


**Klasy i ich funkcjonalność**

Do wykonania gry potrzebne będą klasy:
- **cKula** \- możliwość poruszania kulą w lewo i prawo oraz wykonywania skoku z zastosowaniem grawitacji. Ponadto posiada punkty życia.
- **cSciana** \- kwadrat ograniczający ruch, z nim będzie odbywać się kolizja kuli.
- **cObrecz** \- element bezkolizyjny, w którego obrębie będzie naliczany punkt do ukończenia planszy.
- **cSlupek** \- element kolizyjny odejmujący punkt życia kuli.
- **cBonus** \- obiekt dodający dodatkowe punkty dla gracza.
- **cZycie** \- obiekt zwiększający punkty życia kuli o jeden.
- **cScena** \- wyświetlanie planszy i ustalenie zasad gry.
- **cFizyka** \- symulacja grawitacji podczas skakanią kulą.

**Szkic planszy**

![Bez tytułu](https://user-images.githubusercontent.com/50639678/58133678-b347ba00-7c24-11e9-9d7f-982cac3641ba.png)
