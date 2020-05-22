void rotation(Block *block,int director){
	//向左旋转
	if(director==0){
		int value=block->shape[0][0];
		block->shape[0][0]=block->shape[0][2];
		block->shape[0][2]=block->shape[2][2];
		block->shape[2][2]=block->shape[2][0];
		block->shape[2][0]=value;
		value=block->shape[0][1];
		block->shape[0][1]=block->shape[1][2];
		block->shape[1][2]=block->shape[2][1];
		block->shape[2][1]=block->shape[1][0];
		block->shape[1][0]=value;
	} 
	else if(director==1){
		int value=block->shape[0][0];
		block->shape[0][0]=block->shape[2][0];
		block->shape[2][0]=block->shape[2][2];
		block->shape[2][2]=block->shape[0][2];
		block->shape[0][2]=value;
		value=block->shape[0][1];
		block->shape[0][1]=block->shape[1][0];
		block->shape[1][0]=block->shape[2][1];
		block->shape[2][1]=block->shape[1][2];
		block->shape[1][2]=value;
	}
	//特殊情况
	if(block->type==1){
		if(block->shape[1][3]==1){
			block->shape[1][3]=0;
			block->shape[3][1]=1;
		}
		else{
			block->shape[1][3]=1;
			block->shape[3][1]=0;
		}
	} 
}
void _transfer(int **map, Block *block, int sign){
	int director = block->director;
	cleanBlock(*block);	 // 擦除旋转前的block 
	switch(sign){
		case 0:
			rotation(block, director);
			// 碰撞的检查
			if(checkCrash(map, block) == 1){
				rotation(block, director^1);
			}
			break;
		case 1:
			rotation(block, director);
			block->director = block->director ^ 1;
			// 旋转后进行碰撞检查
			if(checkCrash(map, block) == 1){
				rotation(block, director ^ 1);
				block->director = block->director ^ 1;
			}
			break;
	}
	
	drawBlock(*block);  // 重新绘制旋转后的block 
}
/* 旋转 */
void transfer(int **map, Block *block){
    int sign = block->type;
	//sign： 什么类型的方块， 不同类型的方块的旋转策略不同 
	if(sign == 2 || sign == 3 || sign == 4){ // 在左上角的三格内旋转 
		_transfer(map, block, 0);
	}
	else if(sign == 1 || sign == 6 || sign == 7){	// 处理棍子,Z
		_transfer(map, block, 1);
	}
	else if(sign == 0 || sign == 5){	// 不需要处理的 
		return;
	}
}
