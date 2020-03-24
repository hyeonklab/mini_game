// lotto_number.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	for( unsigned int i = 0; i < 100; ++i )	// �ݺ� ����
	{
		// ���� �ε��� 2��
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		// �� �ε����� �����ϸ� �����
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

	// 1-45 �Է�
	for( int i = 0; i < 45; ++i )
	{
		lotto_num[ i ] = i + 1;
	}

	int temp;
	// shuffle
	/*//
	for( unsigned int i = 0; i < 100; ++i )	// �ݺ� ����
	{
		// ���� �ε��� 2��
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		// �� �ε����� �����ϸ� �����
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

	// ���� �� �� Ȯ��
	/*//
	for( int i = 0; i < 45; ++i )
	{
		cout << lotto_num[ i ] << endl;
	}
	//*/

	// ��÷ ��ȣ, ���ʽ� ��ȣ
	int winning_num[ 6 ] = {};
	int bonus;

	// 6���� ��ȣ ��÷
	//cout << "winning number + bonus number: ";
	cout << "��÷��ȣ + ���ʽ�: ";
	for( int i = 0; i < 6; ++i )
	{
		winning_num[ i ] = lotto_num[ i ];
		//cout << lotto_num[ i ] << " ";
	}

	// ���ʽ� ��ȣ ��÷
	bonus = lotto_num[ 6 ];
	//cout << "+ " << lotto_num[ 6 ] << endl;

	// ��÷��ȣ �������� ����
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

	// ��÷��ȣ, ���ʽ� ���
	for( int i = 0; i < 6; ++i )
	{
		//winning_num[ i ] = lotto_num[ i ];
		cout << winning_num[ i ] << " ";
	}
	cout << "+ " << bonus << endl;

	system( "pause" );

    return 0;
}

