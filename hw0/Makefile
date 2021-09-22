all: pi_calculation.cpp
	g++ pi_calculation.cpp -o run -Wall -Werror -pthread

test:
	g++ pi_calculation.cpp -o run -Wall -Werror -pthread -fsanitize=address
	sh test.sh
