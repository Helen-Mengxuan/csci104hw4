all: floorplan

floorplan: fpmap.cpp avlbst.h bst.h print_bst.h
	g++ -g -Wall fpmap.cpp -o floorplan

clean:
	-@rm floorplan