# -block-
int _move(int **map, Block *block, int x, int y, int sign){
	// sign： 1表示向下移动， 0表示左右移动 
	/* 消除所有属于block的块 */
	/* 重新定位block的位置，生成新的block */
	cleanBlock(*block);
	block->set(block->x + x, block->y + y, -1);
	if(checkCrash(map, block) == 1){
		block->set(block->x - x, block->y - y, -1);
		drawBlock(*block);
		if(sign == 1)
			addBlock(map, *block);
		return 1;
	}
	drawBlock(*block);
	return 0;
}
