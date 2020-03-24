// bingo_game.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "bingo_game.h"

int main()
{
	srand( (unsigned int)time( 0 ) );

	array<int, BINGO_NUMBERS> player_numbers = {};
	array<int, BINGO_NUMBERS> com_numbers = {};

	// 1-25 ���� ����
	set_numbers( player_numbers );
	set_numbers( com_numbers );

	// ����
	shuffle( player_numbers );
	shuffle( com_numbers );

	int bingo = 0, com_bingo = 0;	// ���� ����

	// computer ���̵��� �����Ѵ�
	COM_LEVEL com_level = select_difficulty_level();

	while( true )
	{
		system( "cls" );

		if( com_level == COM_LEVEL::COM_EASY )
			cout << "������ ���̵�: Easy" << endl;
		else
			cout << "������ ���̵�: Hard" << endl;

		// 5x5 ���
		cout << "============ Player ============" << endl;
		print_numbers( player_numbers );

		cout << "============ Computer ============" << endl;
		print_numbers( com_numbers );

		cout << "\n���� ������ �����մϴ�." << endl;
		cout << "Player bingo line: " << bingo << endl;
		cout << "Computer bingo line: " << com_bingo << endl;
		cout << "���ڸ� �Է��ϼ���. (0: ����)\n" << endl;

		if( bingo >= 5 && com_bingo < 5 )
		{
			cout << "Player�� 5���� ���� ���߾����ϴ�. Player �¸�!" << endl;
			break;
		}
		else if( com_bingo >= 5 && bingo < 5 )
		{
			cout << "Computer�� 5���� ���� ���߾����ϴ�. Computer �¸�..�Ф�" << endl;
			break;
		}
		else if( bingo >= 5 && com_bingo >= 5 )
		{
			if( bingo > com_bingo )
				cout << "���ÿ� 5���� �޼�, Player�� �� ���� ���� ���߾� �¸��Ͽ����ϴ�!" << endl;
			else if( bingo < com_bingo )
				cout << "���ÿ� 5���� �޼�, ������ ���̷� Computer�� �¸��Ͽ����ϴ�.. �Ф�" << endl;
			else if( bingo == com_bingo )
				cout << "�Ϳ�! �ں��� �ºθ� ���Ƴ׿�, ���º� �Դϴ�. �������� �� �̰ܺ��ô�!" << endl;

			break;
		}

		// ���ڸ� �Է� �޴´�.
		int input = 0;
		cin >> input;

		if( input == 0 )
			break;		// ���� ó��
		else if( input < 1 || input > BINGO_NUMBERS )
		{	// �߸��� �Է��� ���Է� ó��
			//cout << "�߸��� ������ �����Դϴ�. ���Է� �Ͻʽÿ�." << endl;
			continue;
		}

		// �ߺ� �Է� üũ ����
		bool duplicated = true;
		// player - ���ڸ� ���� �ٲٱ�
		duplicated = change_number( player_numbers, input );

		// �ߺ� �Է��̸� ���Է� ó���Ѵ�.
		if( duplicated )
		{
			continue;
		}

		// �ߺ��� �ƴϸ�, computer - ���ڵ� ã�� ���� �ٲٱ�
		change_number( com_numbers, input );

		// easy ����, computer�� ���� ���� ���þȵ� ���� ��� �� �ϳ��� �����ϰ� �����ϵ��� �Ѵ�.
		// ������ computer�� ������ ���ʴ�. ���̵��� ���� ����� �ٸ��� �����Ѵ�.
		switch( com_level )
		{
		case COM_LEVEL::COM_EASY:
			// easy ����, ��ǻ���� ���� ���� ���� �� �� ���� ��� �� �ϳ��� �����ϰ� �����ϵ��� �Ѵ�.
			// ���� �� �� ���� ��� �����
			// ���� �� �� ���� ������, ����� ���鶧 ī���� �Ѵ�.
			input = select_number_by_com( com_numbers );	// ���� ���� �Է°����� �Ѵ�.
			break;
		case COM_LEVEL::COM_HARD:
			// ���� ���� ���� �� ���� ���� ���� ���� ã�Ƴ���.
			// ���� 5���� ���� �̹� �����̹Ƿ� �����Ѵ�. (4���� ���� ���� ���ɼ��� ����)
			//line_number = 0;
			//star_count = save_count = 0;
			int line_number = search_bingo_line( com_numbers );

			// ���� line_number�� ���� ���� Ȯ�� ���� �� ��ȣ�� ����Ǿ� �ִ�.
			// ã�� ���� ���� input�� �����Ѵ�.
			input = search_bingo_value( com_numbers, line_number );
			break;
		}

		// ��ǻ�Ͱ� ������ ���ڷ�, �÷��̾�� ��ǻ���� ���ڸ� ��(��)�� �����Ѵ�.
		change_number( player_numbers, input );
		change_number( com_numbers, input );

		// ���� �� ���� �Է½ø��� üũ�ϹǷ�, ī��Ʈ �ʱ�ȭ �� �� üũ�Ѵ�.
		bingo = com_bingo = 0;

		// ����, ���� ���� �� ���� ���Ѵ�.
		bingo = counting_bingo_HV( player_numbers );
		com_bingo = counting_bingo_HV( com_numbers );
		// �밢�� ���� �� ���� ���Ѵ�.
		bingo += counting_bingo_diagonal( player_numbers );
		com_bingo += counting_bingo_diagonal( com_numbers );
	}

	system( "pause" );

	return 0;
}

void set_numbers( array<int, BINGO_NUMBERS >& arr )
{
	for( int i = 0; i < BINGO_NUMBERS; ++i )
	{
		arr[ i ] = i + 1;	// 1-25 ���� ����
	}
}

void shuffle( array<int, BINGO_NUMBERS >& arr )
{
	// ����
	int temp = 0, idx1 = 0, idx2 = 0;
	for( int i = 0; i < 100; ++i )
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = arr[ idx1 ];
		arr[ idx1 ] = arr[ idx2 ];
		arr[ idx2 ] = temp;
	}
}

COM_LEVEL select_difficulty_level()
{
	int input = 0;
	COM_LEVEL com_level;
	while( true )
	{
		system( "cls" );
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "computer ���̵��� ���� �� �ּ���." << endl;
		cin >> input;

		com_level = static_cast<COM_LEVEL>(input);
		if( com_level >= COM_LEVEL::COM_EASY && com_level <= COM_LEVEL::COM_HARD )
			break;

		// cin clear
		cin.clear();
		cin.ignore();
	}

	return com_level;
}

void print_numbers( const array<int, BINGO_NUMBERS > arr )
{
	for( int i = 0; i < 5; ++i )
	{
		for( int j = 0; j < 5; ++j )
		{
			// INT_MAX ���̸� �� (��)�� ����Ѵ�.
			if( arr[ i * 5 + j ] == INT_MAX )
				cout << "��" << "\t";
			else
				cout << arr[ i * 5 + j ] << "\t";
		}
		cout << endl;
	}
}

bool change_number( array<int, BINGO_NUMBERS>& arr, int input )
{
	for( int i = 0; i < BINGO_NUMBERS; ++i )
	{
		// ���� ���� ã���� �ߺ��� �ƴ�
		if( arr[ i ] == input )
		{
			//duplicated = false;
			// �ش� ���� �� (��)�� �ٲٱ� ���� INT_MAX�� �����ϰ�, �ݺ��� Ż���Ѵ�.
			arr[ i ] = INT_MAX;
			//break;
			return false;
		}
	}

	return true;
}

int select_number_by_com( const array<int, BINGO_NUMBERS>& number )
{
	array<int, BINGO_NUMBERS> com_none_selection;
	int none_selection_count = 0;
	for( int i = 0; i < BINGO_NUMBERS; ++i )
	{
		if( number[ i ] != INT_MAX )
		{
			com_none_selection[ none_selection_count ] = number[ i ];
			++none_selection_count;	// �̼��� ���� ���� ī����
		}
	}
	// ���� �̼��� ��ϰ�, ������ �������.
	// ���� �� ������ �ε����� �����ϰ� ���´�.
	return com_none_selection[ rand() % none_selection_count ];	// ���� ���� �Է°����� �Ѵ�.
}

int search_bingo_line( const array<int, BINGO_NUMBERS>& arr )
{
	// ���� ��ȸ�ϸ�, ���� ���ɼ��� �˻��Ѵ�
	// ���� ���� �ٿ��� ���� ���� ���� ã�´�.
	int line_number = 0;	// ���� ���� � ������
	int star_count = 0, save_count = 0;	// �� ����, ������ �� ���� (�񱳿�)
	for( int i = 0; i < 5; ++i )
	{
		star_count = 0;
		for( int j = 0; j < 5; ++j )
		{
			//line_number = LINE_H1;
			if( arr[ i * 5 + j ] == INT_MAX )
				++star_count;
		}

		// ���� 5���� ������, ����� �ְ� �������� ũ�� ������ �����Ѵ�.
		if( star_count < 5 && star_count > save_count )
		{
			line_number = i;		// ���� ���� �� ���� (0~4)
			save_count = star_count;	// ���� ����
		}
	}

	// ������ ���� ���� ���� ���� ������
	// ���� ���� ���Ͽ�, ���� ���ɼ� ���� ���� ���� ���Ѵ�.
	for( int i = 0; i < 5; ++i )
	{
		star_count = 0;
		for( int j = 0; j < 5; ++j )
		{
			if( arr[ j * 5 + i ] == INT_MAX )
				++star_count;
		}

		// ���� 5���� ������, ����� �ְ� �������� ũ�� ������ �����Ѵ�.
		if( star_count < 5 && star_count > save_count )
		{
			line_number = i + 5;		// ���� ���� �� ������ 5~9�� �ϱ�� �Ѵ�.
			save_count = star_count;	// ���� ����
		}
	}

	// �밢�� �ٿ��� ���� ���� ���� ã�´�.
	star_count = 0;
	for( int i = 0; i < 25; i += 6 )	// �»�� �밢��
	{
		if( arr[ i ] == INT_MAX )
			++star_count;
	}

	if( star_count < 5 && star_count > save_count )
	{
		line_number = LINE_LTOP;
		save_count = star_count;
	}

	star_count = 0;
	for( int i = 4; i <= 20; i += 4 )	// ���� �밢��
	{
		if( arr[ i ] == INT_MAX )
			++star_count;
	}

	if( star_count < 5 && star_count > save_count )
	{
		line_number = LINE_RTOP;
		save_count = star_count;
	}

	return line_number;
}

int search_bingo_value( array<int, BINGO_NUMBERS>& arr, int line_number )
{
	int input = 0;
	// ���� �� ���� ���ɼ� ���� �ٿ���, ��(��)�� ���� �� �� �˻�
	if( line_number >= LINE_H1 && line_number <= LINE_H5 )
	{
		for( int i = 0; i < 5; ++i )
		{
			if( arr[ line_number * 5 + i ] != INT_MAX )
			{
				input = arr[ line_number * 5 + i ];	// ã���� input�� ����
				break;
			}
		}
	}
	// ���� �� ���� ���ɼ� ���� �ٿ���, ��(��)�� ���� �� �� �˻�
	else if( line_number >= LINE_V1 && line_number <= LINE_V5 )
	{
		for( int i = 0; i < 5; ++i )
		{
			if( arr[ i * 5 + (line_number - 5) ] != INT_MAX )
			{
				input = arr[ i * 5 + (line_number - 5) ];	// ã���� ����
				break;
			}
		}
	}
	// �밢�� �� ���� ���ɼ� ���� �ٿ���, ��(��)�� ���� �� �� �˻� - �»��
	else if( line_number == LINE_LTOP )
	{
		for( int i = 0; i < BINGO_NUMBERS; i += 6 )
		{	// �»�� �밢�� ����
			if( arr[ i ] != INT_MAX )
			{
				input = arr[ i ];	// ã���� ����
				break;
			}
		}
	}
	// �밢�� �� ���� ���ɼ� ���� �ٿ���, ��(��)�� ���� �� �� �˻� - ����
	else if( line_number == LINE_RTOP )
	{
		for( int i = 4; i <= 20; i += 4 )
		{	// ���� �밢�� ����
			if( arr[ i ] != INT_MAX )
			{
				input = arr[ i ];	// ã���� ����
				break;
			}
		}
	}

	return input;
}

// ����, ���� - horizon, vertical
int counting_bingo_HV( const array<int, BINGO_NUMBERS>& arr )
{
	// �� ī��Ʈ �ʱ�ȭ
	int star_horizontal = 0, star_vertical = 0;
	int bingo = 0;
	for( int i = 0; i < 5; ++i )
	{
		star_horizontal = star_vertical = 0;
		for( int j = 0; j < 5; ++j )
		{
			// �÷��̾� ����, ���� �� ī��Ʈ
			if( arr[ i * 5 + j ] == INT_MAX )
				++star_horizontal;

			if( arr[ j * 5 + i ] == INT_MAX )
				++star_vertical;
		}

		// �÷��̾� - ����, ���� �� ���� ���� ī��Ʈ ����
		if( star_horizontal == 5 )
			++bingo;

		if( star_vertical == 5 )
			++bingo;
	}

	return bingo;
}

// �밢��
int counting_bingo_diagonal( array<int, BINGO_NUMBERS>& arr )
{
	// �밢�� ���� �� ���� ���Ѵ�.
	int star_diagonal_left = 0, star_diagonal_right = 0;
	int bingo = 0;
	// ���� ��� - ���� �ϴ� �밢�� �� ī��Ʈ
	// ���� ���� ������ �����ϴ�, 5���� 1�� ������Ų 6�� �̵��Ѵ�.
	for( int i = 0; i < 25; i += 6 )
	{
		if( arr[ i ] == INT_MAX )
			++star_diagonal_left;
	}

	// ���� ��� - ���� �ϴ� �밢�� �� ī��Ʈ
	// ���� ���� ������ �����ϴ�, 5���� 1�� ���ҽ�Ų 4�� �̵��Ѵ�.
	for( int i = 4; i <= 20; i += 4 )
	{
		if( arr[ i ] == INT_MAX )
			++star_diagonal_right;
	}

	// ���� ��� - ���� �ϴ� �밢�� ���� ī��Ʈ
	if( star_diagonal_left == 5 )
		++bingo;
	// ���� ��� - ���� �ϴ� �밢�� ���� ī��Ʈ
	if( star_diagonal_right == 5 )
		++bingo;

	return bingo;
}