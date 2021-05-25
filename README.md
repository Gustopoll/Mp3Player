# Projekt do predmetu MUL
Vypracoval: Dominik Švač

## Zadanie:
Vytvořte program pro inteligentní přehrávání skladeb ve formátu MP3 uložených na CD-ROM nebo na disku. Program by měl umožnit setřídit skladby dle umístění na médiu, podle alb, autorů apod. Program by měl zobrazovat (i během přehrávání) dodatečné informace získané z tagů ID3, obrázky alb, texty, apod. Program musí přehrávaný zvuk vhodně vizualizovat (FFT, indikátory vybuzení, grafické efekty apod.)

## Popis riešenia
Projekt som vypracoval v jazyku c++ s použitím multiplatformovej knižnice Qt. Program môže prehrávať pesničky, ktoré sú uložené kdekoľvek na disku, usb, cd ... Podporuje formáty MP3, WMA a WAV. Na prehrávanie piesní a získavanie tagov je využitá vstavaná knižnica Qt Multimédia, ktorá umožňuje prácu s multimédiami.

## Spustenie:
```
 ./make compile - preloží sa aplikácia
 ./make run - preloží sa a spustí sa aplikácia
 ./make update
 ./make clean
```