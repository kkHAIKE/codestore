#pragma once

 inline void MyCls(HANDLE hConsole) 
 {
 	COORD   coordScreen={0,0};//�����������귵�ص���Ļ���Ͻ�����
 	BOOL   bSuccess;   
 	DWORD   cCharsWritten;   
 	CONSOLE_SCREEN_BUFFER_INFO   csbi;//���滺������Ϣ   
 
 	DWORD   dwConSize;//��ǰ�����������ɵ��ַ���   
 
 	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//��û�������Ϣ     
 	dwConSize=csbi.dwSize.X*csbi.dwSize.Y;//�����������ַ���Ŀ   
 
 	//�ÿո���仺����   
 	bSuccess=FillConsoleOutputCharacter(hConsole,_T(' '),dwConSize,coordScreen,&cCharsWritten);   
 
 	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//��û�������Ϣ   
 
 	//��仺��������   
 	bSuccess=FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);   
 
 	//��귵����Ļ���Ͻ�����   
 	bSuccess=SetConsoleCursorPosition(hConsole,coordScreen);     
 	return;   
 }
 inline void clrscr(void) 
 {   
 	HANDLE   hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
 	MyCls(hStdOut);
 	return;
 }