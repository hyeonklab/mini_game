// mini_baseball.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
	// 1-9 숫자 입력
	int number[ 9 ] = {};
	for( int i = 0; i < 9; ++i )
	{
		number[ i ] = i + 1;
	}

	// 골고루 셔플
	srand( (unsigned int)time( 0 ) );	// 난수 초기화
	int temp, idx1, idx2;
	// 100번 정도 섞기
	for( int i = 0; i < 100; ++i )
	{
		idx1 = rand() % 9;	// 랜덤 인덱스 2개 얻기
		idx2 = rand() % 9;

		// 랜덤 인덱스 값 swap
		temp = number[ idx1 ];
		number[ idx1 ] = number[ idx2 ];
		number[ idx2 ] = temp;
	}

	// 셔플 결과 출력
	//cout << number[ 0 ] << " " << number[ 1 ] << " " << number[ 2 ] << endl;
	cout << "숫자 맞추기 야구게임을 시작합니다." << endl;
	cout << "규칙: 1개의 숫자를 맞추면 1 ball, 순서까지 적중하면 1 strike 입니다." << endl;
	cout << "3 strike 시 게임 클리어! 다음 3개의 숫자를 맞추십시오!\n* * *\n" << endl;
	

	int strike = 0, ball = 0;
	int input[ 3 ] = {};
	int count = 1;

	// 종료 입력이나, 게임 클리어 까지 반복
	while( true )
	{
		cout << count << " 회" << endl;
		cout << "1-9 사이 숫자 중 3개를 입력하세요 (예시- 1 2 3 입력, 0 0 0: 게임 종료)" << endl;
		cin >> input[ 0 ] >> input[ 1 ] >> input[ 2 ];

		if( input[ 0 ] == 0 || input[ 1 ] == 0 || input[ 2 ] == 0 )
		{
			break;		// 입력값 중에 0이 있을 경우, 종료
		}
		else if( input[ 0 ] < 0 || input[ 0 ] > 9
			|| input[ 1 ] < 0 || input[ 1 ] > 9 || input[ 2 ] < 0 || input[ 2 ] > 9 )
		{
			// 범위 밖 예외처리
			cout << "입력된 숫자가 잘못 되었습니다. 재입력 하십시오." << endl;
			continue;
		}
		else if( input[ 0 ] == input[ 1 ] || input[ 0 ] == input[ 2 ] || input[ 1 ] == input[ 2 ] )
		{	// 중복 숫자 예외처리
			cout << "입력된 숫자가 중복되었습니다. 재입력 하십시오." << endl;
			continue;
		}

		strike = ball = 0;	// strike, ball 카운트 초기화

		// strike, ball 적중 카운트 판별
		for( int i = 0; i < 3; ++i )
		{
			for( int j = 0; j < 3; ++j )
			{
				if( input[ i ] == number[ j ] )
				{
					if( i == j )
					{	// 자리수까지 적중하면, strike
						++strike;
					}
					else
					{	// 값만 적중하면, ball
						++ball;
					}

					break;		// 다음 루프
				}
			}
		}
		
		if( strike == 3 )
		{
			cout << "3개의 숫자 모두 스트라이크로 적중하였습니다! 게임 클리어!" << endl;
			break;
		}
		else if( strike ==0 && ball == 0 )
		{
			cout << "Out! 하나도 적중하지 못했습니다." << endl;
		}
		else
		{
			cout << strike << " strike, " << ball << " ball" << endl;
		}

		cout << endl;	// 회차 구분 줄 간격 띄우기
		++count;
	}

	system( "pause" );

    return 0;
}

