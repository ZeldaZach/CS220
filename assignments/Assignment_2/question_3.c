/**
* @author: Zachary Halpern
* @date: 9/16/16
*/
int swap_bytes(int n)
{
	unsigned char bytes[4];
	unsigned char tmp;
	
	bytes[0] = (n >> (8*0)) & 0xff;
	bytes[1] = (n >> (8*1)) & 0xff;
	bytes[2] = (n >> (8*2)) & 0xff;
	bytes[3] = (n >> (8*3)) & 0xff;
	
	tmp = bytes[0];
	bytes[0] = bytes[1];
	bytes[1] = tmp;
	
	tmp = bytes[2];
	bytes[2] = bytes[3];
	bytes[3] = tmp;
	
	return *(int*)(bytes);
}