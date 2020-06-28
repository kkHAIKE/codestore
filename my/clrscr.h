#pragma once

 inline void MyCls(HANDLE hConsole) 
 {
 	COORD   coordScreen={0,0};//设置清屏后光标返回的屏幕左上角坐标
 	BOOL   bSuccess;   
 	DWORD   cCharsWritten;   
 	CONSOLE_SCREEN_BUFFER_INFO   csbi;//保存缓冲区信息   
 
 	DWORD   dwConSize;//当前缓冲区可容纳的字符数   
 
 	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//获得缓冲区信息     
 	dwConSize=csbi.dwSize.X*csbi.dwSize.Y;//缓冲区容纳字符数目   
 
 	//用空格填充缓冲区   
 	bSuccess=FillConsoleOutputCharacter(hConsole,_T(' '),dwConSize,coordScreen,&cCharsWritten);   
 
 	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//获得缓冲区信息   
 
 	//填充缓冲区属性   
 	bSuccess=FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);   
 
 	//光标返回屏幕左上角坐标   
 	bSuccess=SetConsoleCursorPosition(hConsole,coordScreen);     
 	return;   
 }
 inline void clrscr(void) 
 {   
 	HANDLE   hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
 	MyCls(hStdOut);
 	return;
 }