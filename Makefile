all: basic

basic:
	clang++ -std=c++11 -c business_simulator/simulator/simulator.cpp -o business_simulator/simulator.o
	clang++ -std=c++11 -c business_simulator/simulator/business.cpp -o business_simulator/business.o
	clang++ -std=c++11 -c business_simulator/simulator/event.cpp -o business_simulator/event.o
	clang++ -lstdc++ -o simulator business_simulator/simulator.o business_simulator/business.o business_simulator/event.o

address:
	clang++ -std=c++11 -c -g -fsanitize=address business_simulator/simulator/simulator.cpp -o business_simulator/simulator.o
	clang++ -std=c++11 -c -g -fsanitize=address business_simulator/simulator/business.cpp -o business_simulator/business.o
	clang++ -std=c++11 -c -g -fsanitize=address business_simulator/simulator/event.cpp -o business_simulator/event.o
	clang++ -lstdc++ -g -fsanitize=address -o simulator business_simulator/simulator.o business_simulator/business.o business_simulator/event.o

graph_data:
	./graph_data