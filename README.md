This is an implementation of ChunkList  
Works like std::list  
Allocates memory for elements in blocks.  
When inserting, it tries to insert into existing blocks, if it cannot, adds a new one.  
When deleting an element, if the block becomes empty, it deletes it, otherwise it shifts all the elements inside the block, that is, each chunk may not be completely filled.  
Сode is covered by google tests (gtest).
