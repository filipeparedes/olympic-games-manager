default:
	gcc -Wall -o prog main.c "./Input/input.c" "./ADTList/listArrayList.c" "./ADTList/listElem.c" "./ADTMap/mapSeparateChaining.c" "./ADTMap/mapElem.c" "./ADTSet/setLinkedList.c" "./ADTSet/setElem.c" "./Medal/medal.c" "./Host/host.c" "./Athlete/athlete.c" "./DisciplineStats/disciplinestats.c" "./Date/date.c" "./StringWrap/stringWrap.c" "./Load/load.c" "./Logic/logic.c" "./Listings/listings.c"
debug:
	gcc -Wall -o prog -g main.c "./Input/input.c" "./ADTList/listArrayList.c" "./ADTList/listElem.c" "./ADTMap/mapSeparateChaining.c" "./ADTMap/mapElem.c" "./ADTSet/setLinkedList.c" "./ADTSet/setElem.c" "./Host/host.c" "./Athlete/athlete.c" "./Date/date.c" "./DisciplineStats/disciplinestats.c" "./StringWrap/stringWrap.c" "./Load/load.c" "./Logic/logic.c" "./Listings/listings.c"
clean:
	rm -f prog
