#include "Bot.h"

int searchAddressOfBoard(int pX, int pY, int& row, int& col) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == pX && _A[i][j].y == pY)
			{
				row = i;
				col = j;
				return 1;
			}
		}
	}
	return 0;
}
int MediumBot(int _X, int _Y, int& pX, int& pY) {
	srand(static_cast<unsigned int>(time(NULL)));

	int row, col;
	searchAddressOfBoard(_X, _Y, row, col);

	// Kiểm tra nước đi có hợp lệ không
	auto isValid = [](int r, int c) {
		return r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE;
		};

	// Kiểm tra xem nước đi có thắng hoặc chặn đối thủ không
	auto checkWinOrBlock = [&](int r, int c, int player) {
		int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
		for (auto& dir : directions) {
			int consecutive = 1;
			for (int i = 1; i <= 4; ++i) { // Kiểm tra 4 ô liên tiếp
				int nr = r + i * dir[0];
				int nc = c + i * dir[1];
				if (isValid(nr, nc) && _A[nr][nc].c == player) {
					consecutive++;
				}
				else {
					break;
				}
			}
			for (int i = 1; i <= 4; ++i) { // Kiểm tra 4 ô ngược lại
				int nr = r - i * dir[0];
				int nc = c - i * dir[1];
				if (isValid(nr, nc) && _A[nr][nc].c == player) {
					consecutive++;
				}
				else {
					break;
				}
			}
			if (consecutive >= 5) return true; // Đủ 5 ô liên tiếp
		}
		return false;
		};

	// Thử thắng
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			if (_A[r][c].c == 0 && checkWinOrBlock(r, c, 1)) { // Nếu đặt 'O' tại đây sẽ thắng
				pX = r;
				pY = c;
				_A[r][c].c = 1;
				return 1;
			}
		}
	}

	// Chặn đối thủ thắng
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			if (_A[r][c].c == 0 && checkWinOrBlock(r, c, -1)) { // Nếu đặt 'O' tại đây sẽ chặn 'X'
				pX = r;
				pY = c;
				_A[r][c].c = 1;
				return 1;
			}
		}
	}

	// Hàm đánh giá điểm cho mỗi ô trống
	auto evaluatePosition = [&](int r, int c) {
		int score = 0;
		int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
		for (auto& dir : directions) {
			int countO = 0, countX = 0;
			for (int i = 1; i <= 4; ++i) {
				int nr = r + i * dir[0];
				int nc = c + i * dir[1];
				if (isValid(nr, nc)) {
					if (_A[nr][nc].c == 1) countO++;
					else if (_A[nr][nc].c == -1) countX++;
				}
				nr = r - i * dir[0];
				nc = c - i * dir[1];
				if (isValid(nr, nc)) {
					if (_A[nr][nc].c == 1) countO++;
					else if (_A[nr][nc].c == -1) countX++;
				}
			}
			if (countO == 2) score += 10;  // Có 2 'O' liên tiếp
			if (countO == 3) score += 50;  // Có 3 'O' liên tiếp
			if (countO == 4) score += 200; // Có 4 'O' liên tiếp
			if (countX == 2) score += 5;   // Có 2 'X' liên tiếp (chặn đối thủ)
			if (countX == 3) score += 25;  // Có 3 'X' liên tiếp
			if (countX == 4) score += 100; // Có 4 'X' liên tiếp (ưu tiên chặn)
		}
		return score;
		};

	// Tìm nước đi tốt nhất dựa trên điểm đánh giá
	int maxScore = -1;
	int bestRow = -1, bestCol = -1;
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			if (_A[r][c].c == 0) { // Ô trống
				int score = evaluatePosition(r, c);
				if (score > maxScore) {
					maxScore = score;
					bestRow = r;
					bestCol = c;
				}
			}
		}
	}

	// Đánh tại ô có điểm cao nhất
	if (bestRow != -1 && bestCol != -1) {
		pX = bestRow;
		pY = bestCol;
		_A[bestRow][bestCol].c = 1;
		return 1;
	}

	// Trường hợp không tìm thấy nước đi tối ưu, đánh ngẫu nhiên
	for (int attempt = 0; attempt < 10; attempt++) {
		int randRow = rand() % BOARD_SIZE;
		int randCol = rand() % BOARD_SIZE;
		if (_A[randRow][randCol].c == 0) {
			pX = randRow;
			pY = randCol;
			_A[randRow][randCol].c = 1;
			return 1;
		}
	}

	return 0; // Không có nước đi hợp lệ
}

int EasyBot(int _X, int _Y, int& pX, int& pY) {
	srand(static_cast<unsigned int>(time(NULL)));

	int row, col;
	searchAddressOfBoard(_X, _Y, row, col);

	// Trường hợp đánh nhiều ô liên tiếp
	// Hàng
	for (int offset = -3; offset <= 3; offset++) {
		if (offset == 0) continue; // Bỏ qua ô hiện tại
		int count = 0;
		for (int i = -2; i <= 2; i++) {
			if (col + offset + i >= 0 && col + offset + i < BOARD_SIZE && _A[row][col + offset + i].c == -1) {
				count++;
			}
		}
		if (count >= 3) {
			int targetCol = col + offset + (count > 2 ? 2 : -2);
			if (targetCol >= 0 && targetCol < BOARD_SIZE && _A[row][targetCol].c == 0) {
				pX = row;
				pY = targetCol;
				_A[row][targetCol].c = 1;
				return 1;
			}
		}
	}

	// Cột
	for (int offset = -3; offset <= 3; offset++) {
		if (offset == 0) continue; // Bỏ qua ô hiện tại
		int count = 0;
		for (int i = -2; i <= 2; i++) {
			if (row + offset + i >= 0 && row + offset + i < BOARD_SIZE && _A[row + offset + i][col].c == -1) {
				count++;
			}
		}
		if (count >= 3) {
			int targetRow = row + offset + (count > 2 ? 2 : -2);
			if (targetRow >= 0 && targetRow < BOARD_SIZE && _A[targetRow][col].c == 0) {
				pX = targetRow;
				pY = col;
				_A[targetRow][col].c = 1;
				return 1;
			}
		}
	}

	// Chéo
	for (int direction = -1; direction <= 1; direction++) {
		for (int offset = -3; offset <= 3; offset++) {
			if (offset == 0) continue; // Bỏ qua ô hiện tại
			int count = 0;
			for (int i = -2; i <= 2; i++) {
				int r = row + direction * (offset + i);
				int c = col + (direction == 1 ? i : -i);
				if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && _A[r][c].c == -1) {
					count++;
				}
			}
			if (count >= 3) {
				int targetRow = row + direction * (offset + (count > 2 ? 2 : -2));
				int targetCol = col + (direction == 1 ? (count > 2 ? 2 : -2) : -(count > 2 ? 2 : -2));
				if (targetRow >= 0 && targetRow < BOARD_SIZE && targetCol >= 0 && targetCol < BOARD_SIZE && _A[targetRow][targetCol].c == 0) {
					pX = targetRow;
					pY = targetCol;
					_A[targetRow][targetCol].c = 1;
					return 1;
				}
			}
		}
	}

	// Trường hợp đánh rời rạc
	for (int attempt = 0; attempt < 10; attempt++) {
		int randRow = rand() % BOARD_SIZE;
		int randCol = rand() % BOARD_SIZE;
		if (_A[randRow][randCol].c == 0) {
			pX = randRow;
			pY = randCol;
			_A[randRow][randCol].c = 1;
			return 1;
		}
	}

	return 0; // Không tìm thấy nước đi
}