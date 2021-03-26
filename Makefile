all: floorplan

floorplan: floorplan.cpp avlbst.h bst.h print_bst.h
	g++ -g -Wall floorplan.cpp -o floorplan

clean:
	-@rm floorplan