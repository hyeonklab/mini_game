// mini_baseball.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
	// 1-9 ���� �Է�
	int number[ 9 ] = {};
	for( int i = 0; i < 9; ++i )
	{
		number[ i ] = i + 1;
	}

	// ���� ����
	srand( (unsigned int)time( 0 ) );	// ���� �ʱ�ȭ
	int temp, idx1, idx2;
	// 100�� ���� ����
	for( int i = 0; i < 100; ++i )
	{
		idx1 = rand() % 9;	// ���� �ε��� 2�� ���
		idx2 = rand() % 9;

		// ���� �ε��� �� swap
		temp = number[ idx1 ];
		number[ idx1 ] = number[ idx2 ];
		number[ idx2 ] = temp;
	}

	// ���� ��� ���
	//cout << number[ 0 ] << " " << number[ 1 ] << " " << number[ 2 ] << endl;
	cout << "���� ���߱� �߱������� �����մϴ�." << endl;
	cout << "��Ģ: 1���� ���ڸ� ���߸� 1 ball, �������� �����ϸ� 1 strike �Դϴ�." << endl;
	cout << "3 strike �� ���� Ŭ����! ���� 3���� ���ڸ� ���߽ʽÿ�!\n* * *\n" << endl;
	

	int strike = 0, ball = 0;
	int input[ 3 ] = {};
	int count = 1;

	// ���� �Է��̳�, ���� Ŭ���� ���� �ݺ�
	while( true )
	{
		cout << count << " ȸ" << endl;
		cout << "1-9 ���� ���� �� 3���� �Է��ϼ��� (����- 1 2 3 �Է�, 0 0 0: ���� ����)" << endl;
		cin >> input[ 0 ] >> input[ 1 ] >> input[ 2 ];

		if( input[ 0 ] == 0 || input[ 1 ] == 0 || input[ 2 ] == 0 )
		{
			break;		// �Է°� �߿� 0�� ���� ���, ����
		}
		else if( input[ 0 ] < 0 || input[ 0 ] > 9
			|| input[ 1 ] < 0 || input[ 1 ] > 9 || input[ 2 ] < 0 || input[ 2 ] > 9 )
		{
			// ���� �� ����ó��
			cout << "�Էµ� ���ڰ� �߸� �Ǿ����ϴ�. ���Է� �Ͻʽÿ�." << endl;
			continue;
		}
		else if( input[ 0 ] == input[ 1 ] || input[ 0 ] == input[ 2 ] || input[ 1 ] == input[ 2 ] )
		{	// �ߺ� ���� ����ó��
			cout << "�Էµ� ���ڰ� �ߺ��Ǿ����ϴ�. ���Է� �Ͻʽÿ�." << endl;
			continue;
		}

		strike = ball = 0;	// strike, ball ī��Ʈ �ʱ�ȭ

		// strike, ball ���� ī��Ʈ �Ǻ�
		for( int i = 0; i < 3; ++i )
		{
			for( int j = 0; j < 3; ++j )
			{
				if( input[ i ] == number[ j ] )
				{
					if( i == j )
					{	// �ڸ������� �����ϸ�, strike
						++strike;
					}
					else
					{	// ���� �����ϸ�, ball
						++ball;
					}

					break;		// ���� ����
				}
			}
		}
		
		if( strike == 3 )
		{
			cout << "3���� ���� ��� ��Ʈ����ũ�� �����Ͽ����ϴ�! ���� Ŭ����!" << endl;
			break;
		}
		else if( strike ==0 && ball == 0 )
		{
			cout << "Out! �ϳ��� �������� ���߽��ϴ�." << endl;
		}
		else
		{
			cout << strike << " strike, " << ball << " ball" << endl;
		}

		cout << endl;	// ȸ�� ���� �� ���� ����
		++count;
	}

	system( "pause" );

    return 0;
}

