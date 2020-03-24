// bingo_game.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "bingo_game.h"

int main()
{
	srand( (unsigned int)time( 0 ) );

	array<int, BINGO_NUMBERS> player_numbers = {};
	array<int, BINGO_NUMBERS> com_numbers = {};

	// 1-25 숫자 삽입
	set_numbers( player_numbers );
	set_numbers( com_numbers );

	// 셔플
	shuffle( player_numbers );
	shuffle( com_numbers );

	int bingo = 0, com_bingo = 0;	// 빙고 개수

	// computer 난이도를 선택한다
	COM_LEVEL com_level = select_difficulty_level();

	while( true )
	{
		system( "cls" );

		if( com_level == COM_LEVEL::COM_EASY )
			cout << "선택한 난이도: Easy" << endl;
		else
			cout << "선택한 난이도: Hard" << endl;

		// 5x5 출력
		cout << "============ Player ============" << endl;
		print_numbers( player_numbers );

		cout << "============ Computer ============" << endl;
		print_numbers( com_numbers );

		cout << "\n빙고 게임을 시작합니다." << endl;
		cout << "Player bingo line: " << bingo << endl;
		cout << "Computer bingo line: " << com_bingo << endl;
		cout << "숫자를 입력하세요. (0: 종료)\n" << endl;

		if( bingo >= 5 && com_bingo < 5 )
		{
			cout << "Player가 5개의 빙고를 맞추었습니다. Player 승리!" << endl;
			break;
		}
		else if( com_bingo >= 5 && bingo < 5 )
		{
			cout << "Computer가 5개의 빙고를 맞추었습니다. Computer 승리..ㅠㅠ" << endl;
			break;
		}
		else if( bingo >= 5 && com_bingo >= 5 )
		{
			if( bingo > com_bingo )
				cout << "동시에 5개를 달성, Player가 더 많은 빙고를 맞추어 승리하였습니다!" << endl;
			else if( bingo < com_bingo )
				cout << "동시에 5개를 달성, 간발의 차이로 Computer가 승리하였습니다.. ㅠㅠ" << endl;
			else if( bingo == com_bingo )
				cout << "와우! 박빙의 승부를 펼쳤네요, 무승부 입니다. 다음번엔 꼭 이겨봅시다!" << endl;

			break;
		}

		// 숫자를 입력 받는다.
		int input = 0;
		cin >> input;

		if( input == 0 )
			break;		// 종료 처리
		else if( input < 1 || input > BINGO_NUMBERS )
		{	// 잘못된 입력을 재입력 처리
			//cout << "잘못된 범위의 숫자입니다. 재입력 하십시오." << endl;
			continue;
		}

		// 중복 입력 체크 변수
		bool duplicated = true;
		// player - 숫자를 별로 바꾸기
		duplicated = change_number( player_numbers, input );

		// 중복 입력이면 재입력 처리한다.
		if( duplicated )
		{
			continue;
		}

		// 중복이 아니면, computer - 숫자도 찾아 별로 바꾸기
		change_number( com_numbers, input );

		// easy 모드는, computer의 현재 아직 선택안된 숫자 목록 중 하나를 랜덤하게 선택하도록 한다.
		// 이제는 computer가 선택할 차례다. 난이도에 따라 방식을 다르게 선택한다.
		switch( com_level )
		{
		case COM_LEVEL::COM_EASY:
			// easy 모드는, 컴퓨터의 현재 아직 선택 안 된 숫자 목록 중 하나를 랜덤하게 선택하도록 한다.
			// 선택 안 된 숫자 목록 만들기
			// 선택 안 된 숫자 개수는, 목록을 만들때 카운팅 한다.
			input = select_number_by_com( com_numbers );	// 얻어온 값을 입력값으로 한다.
			break;
		case COM_LEVEL::COM_HARD:
			// 가로 세로 라인 중 가장 별이 많은 줄을 찾아낸다.
			// 별이 5개인 줄은 이미 빙고이므로 제외한다. (4개인 줄이 가장 가능성이 높다)
			//line_number = 0;
			//star_count = save_count = 0;
			int line_number = search_bingo_line( com_numbers );

			// 이제 line_number에 가장 빙고 확률 높은 줄 번호가 저장되어 있다.
			// 찾은 줄의 값을 input에 저장한다.
			input = search_bingo_value( com_numbers, line_number );
			break;
		}

		// 컴퓨터가 선택한 숫자로, 플레이어와 컴퓨터의 숫자를 별(★)로 변경한다.
		change_number( player_numbers, input );
		change_number( com_numbers, input );

		// 빙고 줄 수는 입력시마다 체크하므로, 카운트 초기화 한 후 체크한다.
		bingo = com_bingo = 0;

		// 가로, 세로 빙고 줄 수를 구한다.
		bingo = counting_bingo_HV( player_numbers );
		com_bingo = counting_bingo_HV( com_numbers );
		// 대각선 빙고 줄 수를 구한다.
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
		arr[ i ] = i + 1;	// 1-25 숫자 삽입
	}
}

void shuffle( array<int, BINGO_NUMBERS >& arr )
{
	// 셔플
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
		cout << "computer 난이도를 선택 해 주세요." << endl;
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
			// INT_MAX 값이면 별 (★)로 출력한다.
			if( arr[ i * 5 + j ] == INT_MAX )
				cout << "★" << "\t";
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
		// 같은 값을 찾으면 중복이 아님
		if( arr[ i ] == input )
		{
			//duplicated = false;
			// 해당 값을 별 (★)로 바꾸기 위해 INT_MAX로 변경하고, 반복문 탈출한다.
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
			++none_selection_count;	// 미선택 숫자 개수 카운팅
		}
	}
	// 이제 미선택 목록과, 개수가 얻어졌다.
	// 선택 할 숫자의 인덱스를 랜덤하게 얻어온다.
	return com_none_selection[ rand() % none_selection_count ];	// 얻어온 값을 입력값으로 한다.
}

int search_bingo_line( const array<int, BINGO_NUMBERS>& arr )
{
	// 줄을 순회하며, 빙고 가능성을 검사한다
	// 먼저 가로 줄에서 별이 많은 줄을 찾는다.
	int line_number = 0;	// 현재 줄이 어떤 줄인지
	int star_count = 0, save_count = 0;	// 별 개수, 이전의 별 개수 (비교용)
	for( int i = 0; i < 5; ++i )
	{
		star_count = 0;
		for( int j = 0; j < 5; ++j )
		{
			//line_number = LINE_H1;
			if( arr[ i * 5 + j ] == INT_MAX )
				++star_count;
		}

		// 별이 5보다 작으며, 저장된 최고 개수보다 크면 변수로 저장한다.
		if( star_count < 5 && star_count > save_count )
		{
			line_number = i;		// 현재 가로 줄 라인 (0~4)
			save_count = star_count;	// 별의 개수
		}
	}

	// 구해진 별이 많은 가로 라인 정보와
	// 세로 라인 비교하여, 제일 가능성 높은 세로 줄을 구한다.
	for( int i = 0; i < 5; ++i )
	{
		star_count = 0;
		for( int j = 0; j < 5; ++j )
		{
			if( arr[ j * 5 + i ] == INT_MAX )
				++star_count;
		}

		// 별이 5보다 작으며, 저장된 최고 개수보다 크면 변수로 저장한다.
		if( star_count < 5 && star_count > save_count )
		{
			line_number = i + 5;		// 현재 세로 줄 라인은 5~9로 하기로 한다.
			save_count = star_count;	// 별의 개수
		}
	}

	// 대각선 줄에서 별이 많은 줄을 찾는다.
	star_count = 0;
	for( int i = 0; i < 25; i += 6 )	// 좌상단 대각선
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
	for( int i = 4; i <= 20; i += 4 )	// 우상단 대각선
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
	// 가로 줄 빙고 가능성 높은 줄에서, 별(★)로 설정 할 값 검색
	if( line_number >= LINE_H1 && line_number <= LINE_H5 )
	{
		for( int i = 0; i < 5; ++i )
		{
			if( arr[ line_number * 5 + i ] != INT_MAX )
			{
				input = arr[ line_number * 5 + i ];	// 찾으면 input에 저장
				break;
			}
		}
	}
	// 세로 줄 빙고 가능성 높은 줄에서, 별(★)로 설정 할 값 검색
	else if( line_number >= LINE_V1 && line_number <= LINE_V5 )
	{
		for( int i = 0; i < 5; ++i )
		{
			if( arr[ i * 5 + (line_number - 5) ] != INT_MAX )
			{
				input = arr[ i * 5 + (line_number - 5) ];	// 찾으면 저장
				break;
			}
		}
	}
	// 대각선 줄 빙고 가능성 높은 줄에서, 별(★)로 설정 할 값 검색 - 좌상단
	else if( line_number == LINE_LTOP )
	{
		for( int i = 0; i < BINGO_NUMBERS; i += 6 )
		{	// 좌상단 대각선 루프
			if( arr[ i ] != INT_MAX )
			{
				input = arr[ i ];	// 찾으면 저장
				break;
			}
		}
	}
	// 대각선 줄 빙고 가능성 높은 줄에서, 별(★)로 설정 할 값 검색 - 우상단
	else if( line_number == LINE_RTOP )
	{
		for( int i = 4; i <= 20; i += 4 )
		{	// 우상단 대각선 루프
			if( arr[ i ] != INT_MAX )
			{
				input = arr[ i ];	// 찾으면 저장
				break;
			}
		}
	}

	return input;
}

// 가로, 세로 - horizon, vertical
int counting_bingo_HV( const array<int, BINGO_NUMBERS>& arr )
{
	// 별 카운트 초기화
	int star_horizontal = 0, star_vertical = 0;
	int bingo = 0;
	for( int i = 0; i < 5; ++i )
	{
		star_horizontal = star_vertical = 0;
		for( int j = 0; j < 5; ++j )
		{
			// 플레이어 가로, 세로 별 카운트
			if( arr[ i * 5 + j ] == INT_MAX )
				++star_horizontal;

			if( arr[ j * 5 + i ] == INT_MAX )
				++star_vertical;
		}

		// 플레이어 - 가로, 세로 별 한줄 빙고 카운트 증가
		if( star_horizontal == 5 )
			++bingo;

		if( star_vertical == 5 )
			++bingo;
	}

	return bingo;
}

// 대각선
int counting_bingo_diagonal( array<int, BINGO_NUMBERS>& arr )
{
	// 대각선 빙고 줄 수를 구한다.
	int star_diagonal_left = 0, star_diagonal_right = 0;
	int bingo = 0;
	// 좌측 상단 - 우측 하단 대각선 별 카운트
	// 점점 우측 끝으로 가야하니, 5보다 1씩 증가시킨 6씩 이동한다.
	for( int i = 0; i < 25; i += 6 )
	{
		if( arr[ i ] == INT_MAX )
			++star_diagonal_left;
	}

	// 우측 상단 - 좌측 하단 대각선 별 카운트
	// 점점 좌측 끝으로 가야하니, 5보다 1씩 감소시킨 4씩 이동한다.
	for( int i = 4; i <= 20; i += 4 )
	{
		if( arr[ i ] == INT_MAX )
			++star_diagonal_right;
	}

	// 좌측 상단 - 우측 하단 대각선 빙고 카운트
	if( star_diagonal_left == 5 )
		++bingo;
	// 우측 상단 - 좌측 하단 대각선 빙고 카운트
	if( star_diagonal_right == 5 )
		++bingo;

	return bingo;
}