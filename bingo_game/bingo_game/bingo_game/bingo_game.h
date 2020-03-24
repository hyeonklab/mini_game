#pragma once

#include <iostream>
#include <time.h>
#include <array>

using namespace std;

#define BINGO_NUMBERS	25

enum class COM_LEVEL
{
	COM_EASY = 1,
	COM_HARD
};

enum LINE_NUMBER
{
	LINE_H1,	// 가로 줄 5개 (0-4)
	LINE_H2,
	LINE_H3,
	LINE_H4,
	LINE_H5,
	LINE_V1,	// 세로 줄 5개 (5-9)
	LINE_V2,
	LINE_V3,
	LINE_V4,
	LINE_V5,
	LINE_LTOP,	// 대각선 - 좌상단
	LINE_RTOP	// 대각선	- 우상단
};


void set_numbers( array<int, BINGO_NUMBERS>& arr );

void shuffle( array<int, BINGO_NUMBERS>& arr );

COM_LEVEL select_difficulty_level();

void print_numbers( const array<int, BINGO_NUMBERS> arr );

bool change_number( array<int, BINGO_NUMBERS>& arr, int input );

int select_number_by_com( const array<int, BINGO_NUMBERS>& number );

int search_bingo_line( const array<int, BINGO_NUMBERS>& arr );

int search_bingo_value( array<int, BINGO_NUMBERS>& arr, int line_number );

int counting_bingo_HV( const array<int, BINGO_NUMBERS>& arr );

int counting_bingo_diagonal( array<int, BINGO_NUMBERS>& arr );
