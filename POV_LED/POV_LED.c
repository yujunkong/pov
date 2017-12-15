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
#include "shift_register.h"

static uint8_t Number0[5] = { 0x0, 0xF8, 0x88, 0xF8, 0x0, }; // 잔상 숫자 설정
static uint8_t Number1[5] = { 0x0, 0x48, 0xF8, 0x08, 0x0, };
static uint8_t Number2[5] = { 0x0, 0xB8, 0xA8, 0xE8, 0x0, };
static uint8_t Number3[5] = { 0x0, 0xA8, 0xA8, 0xF8, 0x0, };
static uint8_t Number4[5] = { 0x0, 0xE0, 0x20, 0xF8, 0x20, };
static uint8_t Number5[5] = { 0x0, 0xE8, 0xA8, 0xB8, 0x0, };
static uint8_t Number6[5] = { 0x0, 0xF8, 0xA8, 0xB8, 0x0, };
static uint8_t Number7[5] = { 0x0, 0xC0, 0x80, 0xF8, 0x0, };
static uint8_t Number8[5] = { 0x0, 0xF8, 0xA8, 0xF8, 0x0, };
static uint8_t Number9[5] = { 0x0, 0xE8, 0xA8, 0xF8, 0x0, };
static uint8_t NumberC[5] = { 0x0, 0x0, 0x50, 0x0, 0x0, }; // :
volatile char str[3]; //  전역변수 선언
volatile char time[7]; // 시간값
volatile char key_input;

void Shift_Resister_Write(uint8_t *Number) {
	for (uint8_t i = 0; i < 5; i++) {
		HC595Write(Number[i]);   //Write the data to HC595
	}
}

void GetString(void) {  // 시간설정을 위해 문자열을 받는 함수
	unsigned char i = 0;
	unsigned char temp = 0;

	do { // 무조건 한번은 실행
		key_input = getchar(); // 입력받은 값을 key_input에 저장
		printf("%c", key_input); // 입력받은 값 출력
		str[i] = key_input; // 입력받은 값 배열에 저장
		i++; // -> Skip ?
		if (i >= 2) // 두 개의 입력이 받아졌으면 반복문 종료
			break;
	} while (key_input != 0x0D);  // Enter값이 들어오면 반복문 종료
	printf("\n");

	if (str[1] == 0x0D) { // Enter 값이 들어오면 순서를 바꿔 시간 형식에 맞춰줌
		temp = str[0];
		str[1] = temp;
		str[0] = 0x30;
	}
	return;
}

int Clock_Setting(void) {

	do {
		printf("Enter Hour : "); // 시간 설정
		GetString();
		time[0] = str[0]; // 받아온 값을 배열의 시간 부분에 저장
		time[1] = str[1];
	} while (time[0] < 0x30 || time[0] > 0x32 || time[1] < 0x30
			|| time[1] > 0x39 || (time[0] == 0x32 && time[1] > 0x33));
	// 시간 부분이 00~23 외에 값이 들어올 경우 반복

	do {
		printf("Enter Minute : "); // 분 설정
		GetString();
		time[2] = str[0];
		time[3] = str[1];
	} while (time[2] < 0x30 || time[2] > 0x35 || time[3] < 0x30
			|| time[3] > 0x39);
	// 분 부분이 00~59 외에 값이 들어올 경우 반복

	do {
		printf("Enter Second : ");
		GetString();
		time[4] = str[0];
		time[5] = str[1];
	} while (time[4] < 0x30 || time[4] > 0x35 || time[5] < 0x30
			|| time[5] > 0x39);
	// 초 부분이 00~59 외에 값이 들어올 경우 반복

	printf("if you want to reset, press 'r' : ");
	key_input = getchar();
	printf("%c\n", key_input);
	if (key_input == 'r')  // 입력받은 값이 r일 경우 실행
		return 0; // 1 반환
	else
		return 1; // 입력받은 값이 r이 아닐 경우 0 반환
	return 0; // 0 반환
}

int POV_Globe_LED(void) {
 // 작성 중
	return 1;
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
	HC595Init(); //Initialize HC595 system

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
			while (!Clock_Setting()) { // Clock_Setting 함수의 return 값이 0일 경우 계속 반복
			}
			printf("Time : %.2s:%.2s:%2s",time, &time[2], &time[4]); // 설정된 시간 출력
			;
			break;
		case '2': // key_input 값이 2일 경우 실행
			while (!POV_Globe_LED()) // POV_Globe_LED 함수의 return 값이 0일 경우 계속 반복
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
