file=p1

main:$(file).o
	g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -o main $(file).o -g

$(file).o:$(file).cpp
	g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -c $(file).cpp -g 

clean:
	rm -f main *.o