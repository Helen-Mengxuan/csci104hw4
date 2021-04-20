To compile, type make.
To run: ./floorplan input.txt output.txt

floorplan.cpp is implemented using my AVLTree.

In floorplan.cpp, I have output.insert() after calling the recursive function.
So the rectangle IDs and the coordinates are only inserted into the "output"
when all lower level calls return true (and the current position is valid for the current rectangle).
Hence I did not use output.erase() in my floorplan.cpp, and did not use AVLTree's remove().

In bst.h, I added two helper functions: (1)clear_helper() -- Recursively delete all nodes in the tree and
is called by clear(); (2) check_height() -- Recursively check height of the nodes and also check if a subtree
is balanced. It is called by isBalance() and returns -1 if the tree/subtree is not balanced;(3) successor() --
similar to the predessor function but finds the successor of a certain node. Returns NULL if no successor found.

In avlbst.h, I added six helper functions: (1,2) left_rotate() and right_rotate() -- Deal with the nodes' pointers
and perform all the rotations; (3) update_height() -- Called by left_rotate() and right_rotate() to update the height
of the two nodes involved in the rotation; (4) pre_rotate() -- Check the zig-zig or zig-zag, then decide which type(s)
of rotations should be applied; (5, 6) insert_fix() and remove_fix() -- Called by insert() and remove(). Recursively
check the height and balance of the relavent nodes, then call pre_rotate if a node is not balanced. 

