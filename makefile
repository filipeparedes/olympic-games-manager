default:
	gcc -Wall -o prog main.c "./Input/input.c" "./ADTList/listArrayList.c" "./ADTList/listElem.c" "./ADTMap/mapSeparateChaining.c" "./ADTMap/mapElem.c" "./Medal/medal.c" "./Host/host.c" "./Athlete/athlete.c" "./Date/date.c" "./StringWrap/stringWrap.c" "./Load/load.c"
debug:
	gcc -Wall -o prog -g main.c "./Input/input.c" "./ADTList/listArrayList.c" "./ADTList/listElem.c" "./ADTMap/mapSeparateChaining.c" "./ADTMap/mapElem.c" "./Medal/medal.c" "./Host/host.c" "./Athlete/athlete.c" "./Date/date.c" "./StringWrap/stringWrap.c" "./Load/load.c"
clean:
	rm -f prog
