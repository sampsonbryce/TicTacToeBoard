/**
 * Unit Tests for TicTacToeBoard
**/

#include <gtest/gtest.h>
#include "TicTacToeBoard.h"
 
class TicTacToeBoardTest : public ::testing::Test
{
	protected:
		TicTacToeBoardTest(){} //constructor runs before each test
		virtual ~TicTacToeBoardTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(TicTacToeBoardTest, toggleTurn)
{
	TicTacToeBoard * board = new TicTacToeBoard();	
	Piece current_player = board->getTurn();	
		
	// assert that we start with X
	ASSERT_EQ(current_player, X);

	// switch player	
	board->toggleTurn();
	
	// assert that we have switched the player
	
	current_player = board->getTurn();	
	ASSERT_EQ(current_player, O);
	
	// switch player	
	board->toggleTurn();
	
	// assert that the player is switched back
	current_player = board->getTurn();	
	ASSERT_EQ(current_player, X);
	
	
	delete board;
}

TEST(TicTacToeBoardTest, getPiece)
{
	TicTacToeBoard * board = new TicTacToeBoard();	
	
	// check for default pieces	
	ASSERT_EQ(board->getPiece(0,0), Blank);
	ASSERT_EQ(board->getPiece(1,2), Blank);
	
	board->placePiece(1,1);
	ASSERT_EQ(board->getPiece(1,1), X);
	
	board->placePiece(1,2);
	ASSERT_EQ(board->getPiece(1,2), O);
	
	// check out of bounds positions	
	ASSERT_EQ(board->getPiece(-1,1), Invalid);
	ASSERT_EQ(board->getPiece(1,-4), Invalid);
	ASSERT_EQ(board->getPiece(3,3), Invalid);
	ASSERT_EQ(board->getPiece(5,6), Invalid);
	
	delete board;
}

TEST(TicTacToeBoardTest, placePiece)
{
	TicTacToeBoard * board = new TicTacToeBoard();	
	
	// assert place piece is swithching turns	
	ASSERT_EQ(board->placePiece(1,1), X);
	ASSERT_EQ(board->placePiece(1,2), O);
	ASSERT_EQ(board->placePiece(2,2), X);
	ASSERT_EQ(board->getTurn(), O);
	
	// its O's turn but we are placing in a spot already occupied by X
	ASSERT_EQ(board->placePiece(1,1), X);
	// ensure its still O's turn
	ASSERT_EQ(board->getTurn(), O);
	
	// assert out of bounds	returns invalid
	ASSERT_EQ(board->placePiece(-1,2), Invalid);
	ASSERT_EQ(board->placePiece(-1,-4), Invalid);
	ASSERT_EQ(board->placePiece(1,4), Invalid);
	
	delete board;
}


TEST(TicTacToeBoardTest, no_winner)
{
	TicTacToeBoard * board = new TicTacToeBoard();	
	ASSERT_EQ(board->getWinner(), Invalid);
	
	delete board;
}


TEST(TicTacToeBoardTest, winner)
{
	TicTacToeBoard * board = new TicTacToeBoard();	
	
	// check first diagonal win condition	
	board->placePiece(0,0); // X
	board->placePiece(1,2); // O
	board->placePiece(1,1); // X
	board->placePiece(2,1); // O
	board->placePiece(2,2); // X
	
	ASSERT_EQ(board->getWinner(), X);
	
	delete board;
	
	// check second diagonal win condition	
	board = new TicTacToeBoard();
	board->placePiece(0,2); // X
	board->placePiece(1,2); // O
	board->placePiece(1,1); // X
	board->placePiece(2,1); // O
	board->placePiece(2,0); // X
	
	ASSERT_EQ(board->getWinner(), X);
	
	delete board;
	
	// check row win
	board = new TicTacToeBoard();
	// . . X
	// O O O
	// X X .
	board->placePiece(0,2); // X
	board->placePiece(1,0); // O
	board->placePiece(2,1); // X
	board->placePiece(1,1); // O
	board->placePiece(2,0); // X
	board->placePiece(1,2); // O
	
	ASSERT_EQ(board->getWinner(), O);
	
	delete board;
	
	// check column win
	board = new TicTacToeBoard();
	board->placePiece(0,1); // X
	board->placePiece(0,2); // O
	board->placePiece(1,1); // X
	board->placePiece(1,2); // O
	board->placePiece(2,0); // X
	board->placePiece(2,2); // O
	
	ASSERT_EQ(board->getWinner(), O);
	
	delete board;
}