// lotto_number.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

void get_shuffle_num( int lotto_num[] )
{
	//int shuffled_num[ 45 ] = {};
	//int test = _msize( lotto_num );
	//cout << test << endl;

	// shuffle
	int temp, idx1, idx2;
	for( unsigned int i = 0; i < 100; ++i )	// 반복 섞기
	{
		// 랜덤 인덱스 2개
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		// 두 인덱스가 동일하면 재수행
		if( idx1 == idx2 )
		{
			//cout << "duplicated loop idx: " << i << endl;
			i--;
			continue;
		}

		// swap
		temp = lotto_num[ idx1 ];
		lotto_num[ idx1 ] = lotto_num[ idx2 ];
		lotto_num[ idx2 ] = temp;
	}

	//return shuffled_num;
}

int main()
{
	srand( (unsigned int) time( NULL ) );

	int lotto_num[45] = {};

	/*
	for( int i = 0; i < 6; i++ )
	{
		cout << ( rand() % 45 + 1 ) << endl;
	}
	*/

	// 1-45 입력
	for( int i = 0; i < 45; ++i )
	{
		lotto_num[ i ] = i + 1;
	}

	int temp;
	// shuffle
	/*//
	for( unsigned int i = 0; i < 100; ++i )	// 반복 섞기
	{
		// 랜덤 인덱스 2개
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		// 두 인덱스가 동일하면 재수행
		if( idx1 == idx2 )
		{
			//cout << "duplicated loop idx: " << i << endl;
			i--;
			continue;
		}

		// swap
		temp = lotto_num[ idx1 ];
		lotto_num[ idx1 ]= lotto_num[ idx2 ];
		lotto_num[ idx2 ] = temp;
	}
	//*/

	get_shuffle_num( lotto_num );
	//get_shuffle_num( lotto_num );

	// 셔플 된 값 확인
	/*//
	for( int i = 0; i < 45; ++i )
	{
		cout << lotto_num[ i ] << endl;
	}
	//*/

	// 당첨 번호, 보너스 번호
	int winning_num[ 6 ] = {};
	int bonus;

	// 6개의 번호 추첨
	//cout << "winning number + bonus number: ";
	cout << "당첨번호 + 보너스: ";
	for( int i = 0; i < 6; ++i )
	{
		winning_num[ i ] = lotto_num[ i ];
		//cout << lotto_num[ i ] << " ";
	}

	// 보너스 번호 추첨
	bonus = lotto_num[ 6 ];
	//cout << "+ " << lotto_num[ 6 ] << endl;

	// 당첨번호 오름차순 정렬
	for( int i = 0; i < 5; ++i )
		for( int j = i + 1; j < 6; ++j )
		{
			if( winning_num[ i ] > winning_num[ j ] )
			{
				temp = winning_num[ i ];
				winning_num[ i ] = winning_num[ j ];
				winning_num[ j ] = temp;
			}
		}

	// 당첨번호, 보너스 출력
	for( int i = 0; i < 6; ++i )
	{
		//winning_num[ i ] = lotto_num[ i ];
		cout << winning_num[ i ] << " ";
	}
	cout << "+ " << bonus << endl;

	system( "pause" );

    return 0;
}

