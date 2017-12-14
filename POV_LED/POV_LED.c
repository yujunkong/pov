/*
 * POV_LED.c
 *
 *  Created on: 2017. 12. 5.
 *      Author: JS
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"

// 7 segments
#define cSegmentPortDir		DDRD // 매크로 상수 정의
#define cSegmentPortData	PORTD

char str[3]; //  전역변수 선언
char time[7];

char key_input;

void GetString(void) {
	unsigned char i = 0;
	unsigned char temp = 0;

	do {
		key_input = getchar();
		printf("%c", key_input);
		str[i] = key_input;
		i++; // -> Skip ?
		if (i >= 2)
			break;
	} while (key_input != 0x0D);  // Enter  getch의 경우 0x0D(버퍼를 사용하지 않음) 0x0A??
	printf("\n");

	if (str[1] == 0x0D) {
		temp = str[0];
		str[1] = temp;
		str[0] = 0x30;
	}
	return;
}

int Clock_Setting(void) {

	do {
		printf("Enter Hour : ");
		GetString();
		time[0] = str[0];
		time[1] = str[1];
	} while (time[0] < 0x30 || time[0] > 0x32 || time[1] < 0x30
			|| time[1] > 0x39 || (time[0]==0x32 && time[1]>0x33) );

	do {
		printf("Enter Minute : ");
		GetString();
		time[2] = str[0];
		time[3] = str[1];
	} while (time[2] < 0x30 || time[2] > 0x35 || time[3] < 0x30
			|| time[3] > 0x39);

	do {
		printf("Enter Second : ");
		GetString();
		time[4] = str[0];
		time[5] = str[1];
	} while (time[4] < 0x30 || time[4] > 0x35 || time[5] < 0x30
			|| time[5] > 0x39);

	printf("if you want to reset press 'r' : ");
	key_input = getchar();
	printf("%c\n", key_input);
	if (key_input == 'r')  // 입력받은 값이 q일 경우 실행
		return 0; // 1 반환
	else
		return 1;
	return 0; // 0 반환
}

int POV_Globe_LED(void) {

	printf("Enter your number [press 'q' to upper menu]: ");
	key_input = getchar(); // 입력 받은 값을 key_input 변수에 저장
	printf("%c\n", key_input); // 입력받은 값 출력
	_delay_ms(200);
	if (key_input == 'q') { // 입력받은 값이 q일 경우 실행
		puts("Goodbye ADC\n");
		return 1; // 1 반환
	}
	return 0; // 0 반환
}

void menu(void) {
	puts("\n==================="); // 문자열 출력 (자동으로 줄바꿈)
	puts("     Main Menu     ");
	puts("-------------------");
	puts("1. Clock Setting");
	puts("2. POV Globe LED");
	puts("\nQ. Exit");
}

int main(void) {
	uart_init(9600UL); // UART 통신 초기화 (9600bps)

	cSegmentPortDir &= 0xF0; // 포트D 하위 4비트 입력으로 설정 (마스크 연산)
	cSegmentPortData = 0x4 << 4;
	// 포트D 상위 4비트 1111 (7-segment의 LED Off)

	stdout = &uart_output; // 표준 출력 설정 (printf 함수로 시리얼 포트 콘솔에 출력)
	stdin = &uart_input; // 표준 입력 설정 (scanf 함수로 시리얼 포트 콘솔에서 입력)

	printf("Hello POV LED!");
	while (1) { // 무한 반복문 실행
		menu(); // menu 함수 호출
		printf("Choose menu : ");
		key_input = uart_getch(); // 입력 받은 값을 key_input 변수에 저장
		printf("%c\n", key_input); // 입력 받은 값 출력
		switch (key_input) {
		case '1': // key_input 값이 1일 경우 실행
			while (!Clock_Setting()){}
			printf("Time : ");
			puts(time);
				;
			break;
		case '2': // key_input 값이 2일 경우 실행
			while (!POV_Globe_LED())
				;
			break;
		case 'q':
			// key_input 값이 q일 경우 break를 만날 때까지 모든 문장들을 실행
		case 'Q': // key_input 값이 Q일 경우 실행
			puts("\nGood Main\n");
			return 0; //  main 함수 종료
		default: // key_input 값이 만족하는 정수값이 없을 경우 실행
			printf("\n"); // 줄바꿈
		}
	}
	return 0;
}
