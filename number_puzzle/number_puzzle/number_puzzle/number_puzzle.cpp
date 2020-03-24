// number_puzzle.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <conio.h>	// console input/output header

using namespace std;

int main()
{
	srand( (unsigned int)time( 0 ) );

	int number[ 25 ] = {};
	for( int i = 0; i < 24; ++i )
	{
		number[ i ] = i + 1;
	}
	
	// 마지막 배열값에는 공백의 의미로 INT_MAX를 넣기로 한다.
	number[ 24 ] = INT_MAX;		// 이 값은 별 (★) 모양으로 출력하기로 한다.

	unsigned int idx_star = 24;	// 별의 위치 저장

	// 1-24까지 숫자만 셔플한다. 즉, 0-23까지의 인덱스를 섞는다.
	int temp, idx1, idx2;
	for( int i = 0; i < 100; ++i )
	{
		idx1 = rand() % 24;		// 랜덤 인덱스 얻기
		idx2 = rand() % 24;

		// 랜덤 인덱스 끼리 swap
		temp = number[ idx1 ];
		number[ idx1 ] = number[ idx2 ];
		number[ idx2 ] = temp;
	}

	// 셔플결과 테스트 출력
	/*//
	for( int i = 0; i < 25; ++i )
	{
		cout << number[ i ] << " ";
	}
	//*/

	while( true )
	{
		system( "cls" );	// 다시 그리기 위해, 화면 초기화

		// 2차원 형태로 출력 5x5
		for( int i = 0; i < 5; ++i )
		{
			for( int j = 0; j < 5; ++j )
			{	// i가 0일때는 0-4 인덱스, 1 이상이면 5, 10, 15, 20 으로 시작해서 j 루프 5회 반복
				// 1차원 배열을 2차원 배열처럼 출력하는 방식
				// 줄 번호 * 가로 개수 + 칸 번호
				if( number[ i * 5 + j ] == INT_MAX )
				{
					cout << "★\t";
					//idx_star = i * 5 + j;	// 현재의 별 위치 저장
				}
				else
				{
					cout << number[ i * 5 + j ] << "\t";
				}
			}
			cout << endl;	// 5개씩 한 행이 끝날때마다 개행
		}

		bool win = true;		// 숫자를 모두 맞춘 여부
		for( int i = 0; i < 24; ++i )
		{
			if( number[ i ] != i + 1 )
			{
				win = false;
				break;
			}
		}

		if( win )
		{
			cout << "숫자 퍼즐을 모두 맞추었습니다. 게임 클리어!" << endl;
			break;
		}

		cout << "\n모든 숫자 퍼즐을 순서대로 맞추면 클리어되는 게임입니다." << endl;
		cout << "조작 - w: 위, s: 아래, a: 왼쪽, d: 오른쪽, q: 종료" << endl;
		// 문자 하나 입력 함수. 엔터 없이도 입력 가능.
		char input = _getch();

		// 별 위치 조작 동작 구현
		switch( input )
		{
		case 'q':	// 종료
		case 'Q':
			cout << "게임을 종료합니다." << endl;
			system( "pause" );
			return 0;
			break;
		case 'w':	// 위
		case 'W':
			// 별 위치 swap
			if( idx_star < 5 )		// 현재 첫 줄이면, 동작하지 않는다.
				break;
			number[ idx_star ] = number[ idx_star - 5 ];	// 별을 바로 위 값으로 변경하고,
			number[ idx_star - 5 ] = INT_MAX;	// 위 값은 별로 변경하여 서로 교체한다.
			idx_star -= 5;		// 위 값의 위치로 별 인덱스 조정
			break;
		case 's':	// 아래
		case 'S':
			// 별 위치 swap
			if( idx_star > 19 )	// 마지막 줄이면, 동작하지 않는다.
				break;
			number[ idx_star ] = number[ idx_star + 5 ];
			number[ idx_star + 5 ] = INT_MAX;
			idx_star += 5;
			break;
		case 'a':	// 왼쪽
		case 'A':
			// 별 위치 swap
			if( idx_star % 5 == 0 )	// 각 줄의 맨 왼쪽이면 동작하지 않는다.
				break;
			number[ idx_star ] = number[ idx_star - 1 ];
			number[ idx_star - 1 ] = INT_MAX;
			--idx_star;
			break;
		case 'd':	// 오른쪽
		case 'D':
			// 별 위치 swap
			if( idx_star % 5 == 4 )	// 각 줄의 맨 오른쪽이면 동작하지 않는다.
				break;
			number[ idx_star ] = number[ idx_star + 1 ];
			number[ idx_star + 1 ] = INT_MAX;
			++idx_star;
			break;
		default:
			break;
		}
	}

	cout << "게임을 종료합니다." << endl;
	system( "pause" );

    return 0;
}

