// number_puzzle.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	
	// ������ �迭������ ������ �ǹ̷� INT_MAX�� �ֱ�� �Ѵ�.
	number[ 24 ] = INT_MAX;		// �� ���� �� (��) ������� ����ϱ�� �Ѵ�.

	unsigned int idx_star = 24;	// ���� ��ġ ����

	// 1-24���� ���ڸ� �����Ѵ�. ��, 0-23������ �ε����� ���´�.
	int temp, idx1, idx2;
	for( int i = 0; i < 100; ++i )
	{
		idx1 = rand() % 24;		// ���� �ε��� ���
		idx2 = rand() % 24;

		// ���� �ε��� ���� swap
		temp = number[ idx1 ];
		number[ idx1 ] = number[ idx2 ];
		number[ idx2 ] = temp;
	}

	// ���ð�� �׽�Ʈ ���
	/*//
	for( int i = 0; i < 25; ++i )
	{
		cout << number[ i ] << " ";
	}
	//*/

	while( true )
	{
		system( "cls" );	// �ٽ� �׸��� ����, ȭ�� �ʱ�ȭ

		// 2���� ���·� ��� 5x5
		for( int i = 0; i < 5; ++i )
		{
			for( int j = 0; j < 5; ++j )
			{	// i�� 0�϶��� 0-4 �ε���, 1 �̻��̸� 5, 10, 15, 20 ���� �����ؼ� j ���� 5ȸ �ݺ�
				// 1���� �迭�� 2���� �迭ó�� ����ϴ� ���
				// �� ��ȣ * ���� ���� + ĭ ��ȣ
				if( number[ i * 5 + j ] == INT_MAX )
				{
					cout << "��\t";
					//idx_star = i * 5 + j;	// ������ �� ��ġ ����
				}
				else
				{
					cout << number[ i * 5 + j ] << "\t";
				}
			}
			cout << endl;	// 5���� �� ���� ���������� ����
		}

		bool win = true;		// ���ڸ� ��� ���� ����
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
			cout << "���� ������ ��� ���߾����ϴ�. ���� Ŭ����!" << endl;
			break;
		}

		cout << "\n��� ���� ������ ������� ���߸� Ŭ����Ǵ� �����Դϴ�." << endl;
		cout << "���� - w: ��, s: �Ʒ�, a: ����, d: ������, q: ����" << endl;
		// ���� �ϳ� �Է� �Լ�. ���� ���̵� �Է� ����.
		char input = _getch();

		// �� ��ġ ���� ���� ����
		switch( input )
		{
		case 'q':	// ����
		case 'Q':
			cout << "������ �����մϴ�." << endl;
			system( "pause" );
			return 0;
			break;
		case 'w':	// ��
		case 'W':
			// �� ��ġ swap
			if( idx_star < 5 )		// ���� ù ���̸�, �������� �ʴ´�.
				break;
			number[ idx_star ] = number[ idx_star - 5 ];	// ���� �ٷ� �� ������ �����ϰ�,
			number[ idx_star - 5 ] = INT_MAX;	// �� ���� ���� �����Ͽ� ���� ��ü�Ѵ�.
			idx_star -= 5;		// �� ���� ��ġ�� �� �ε��� ����
			break;
		case 's':	// �Ʒ�
		case 'S':
			// �� ��ġ swap
			if( idx_star > 19 )	// ������ ���̸�, �������� �ʴ´�.
				break;
			number[ idx_star ] = number[ idx_star + 5 ];
			number[ idx_star + 5 ] = INT_MAX;
			idx_star += 5;
			break;
		case 'a':	// ����
		case 'A':
			// �� ��ġ swap
			if( idx_star % 5 == 0 )	// �� ���� �� �����̸� �������� �ʴ´�.
				break;
			number[ idx_star ] = number[ idx_star - 1 ];
			number[ idx_star - 1 ] = INT_MAX;
			--idx_star;
			break;
		case 'd':	// ������
		case 'D':
			// �� ��ġ swap
			if( idx_star % 5 == 4 )	// �� ���� �� �������̸� �������� �ʴ´�.
				break;
			number[ idx_star ] = number[ idx_star + 1 ];
			number[ idx_star + 1 ] = INT_MAX;
			++idx_star;
			break;
		default:
			break;
		}
	}

	cout << "������ �����մϴ�." << endl;
	system( "pause" );

    return 0;
}

