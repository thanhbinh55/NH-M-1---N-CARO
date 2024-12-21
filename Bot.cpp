#include "Bot.h"


const int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };  // Hướng: ngang, dọc, chéo chính, chéo phụ

// Hàm đếm số quân liền nhau trong một hướng (dx, dy)
int countInLine(int x, int y, int dx, int dy, int player) {
	int count = 0;
	while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && _A[x][y].c == player) {
		count++;
		x += dx;
		y += dy;
	}
	return count;
}

// Hàm kiểm tra và chặn chuỗi quân cờ nguy hiểm của đối thủ
bool blockOpponent(int& pX, int& pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c == -1) {  // Nếu ô này là quân của đối thủ
				for (auto dir : directions) {
					int count = 1;  // Đếm quân cờ liên tiếp
					int emptyFrontX = -1, emptyFrontY = -1;
					int emptyBackX = -1, emptyBackY = -1;

					// Đi xuôi theo hướng
					for (int step = 1; step <= 4; step++) {
						int nx = i + dir[0] * step;
						int ny = j + dir[1] * step;

						if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE) {
							if (_A[nx][ny].c == -1) count++;  // Đếm quân đối thủ
							else if (_A[nx][ny].c == 0 && emptyFrontX == -1) {
								emptyFrontX = nx;
								emptyFrontY = ny;
							}
							else break;
						}
					}

					// Đi ngược theo hướng
					for (int step = 1; step <= 4; step++) {
						int nx = i - dir[0] * step;
						int ny = j - dir[1] * step;

						if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE) {
							if (_A[nx][ny].c == -1) count++;
							else if (_A[nx][ny].c == 0 && emptyBackX == -1) {
								emptyBackX = nx;
								emptyBackY = ny;
							}
							else break;
						}
					}

					// Nếu có 4 quân liên tiếp và 1 đầu trống -> chặn ngay
					if (count == 4) {
						if (emptyFrontX != -1) {
							pX = emptyFrontX;
							pY = emptyFrontY;
							return true;
						}
						if (emptyBackX != -1) {
							pX = emptyBackX;
							pY = emptyBackY;
							return true;
						}
					}

					// Nếu có 3 quân liên tiếp và 2 đầu trống -> chặn ngay
					if (count == 3 && emptyFrontX != -1 && emptyBackX != -1) {
						pX = emptyFrontX;
						pY = emptyFrontY;
						return true;
					}
				}
			}
		}
	}
	return false;
}

// Hàm đánh giá điểm số cho nước đi
int evaluate(int x, int y, int player) {
	int score = 0;
	for (auto dir : directions) {
		score += countInLine(x, y, dir[0], dir[1], player);
	}
	return score;
}

// Thuật toán Minimax với Alpha-Beta Pruning
int minimax(int depth, int alpha, int beta, bool isMaximizingPlayer) {
	if (depth == MAX_DEPTH) {  // Điểm đánh giá tại độ sâu tối đa
		int score = 0;
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				if (_A[i][j].c == 1) score += evaluate(i, j, 1);   // Bot
				else if (_A[i][j].c == -1) score -= evaluate(i, j, -1);  // Đối thủ
		return score;
	}

	if (isMaximizingPlayer) {  // Lượt của Bot
		int maxEval = -10000;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == 0) {  // Nếu ô này trống
					_A[i][j].c = 1;  // Đặt quân của Bot
					int eval = minimax(depth + 1, alpha, beta, false);
					_A[i][j].c = 0;  // Xóa quân của Bot
					maxEval = max(maxEval, eval);
					alpha = max(alpha, eval);
					if (beta <= alpha) break;  // Cắt tỉa
				}
			}
		}
		return maxEval;
	}
	else {  // Lượt của đối thủ
		int minEval = 10000;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (_A[i][j].c == 0) {  // Nếu ô này trống
					_A[i][j].c = -1;  // Đặt quân của đối thủ
					int eval = minimax(depth + 1, alpha, beta, true);
					_A[i][j].c = 0;  // Xóa quân của đối thủ
					minEval = min(minEval, eval);
					beta = min(beta, eval);
					if (beta <= alpha) break;  // Cắt tỉa
				}
			}
		}
		return minEval;
	}
}

// Bot tìm nước đi tối ưu
void improvedBot(int _X, int _Y, int& pX, int& pY) {

	int m, n;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == _X && _A[i][j].y == _Y) {
				_A[i][j].c = 0;  // Xóa ký tự trong bảng
				m = i;
				n = j;
			}
		}
	}
	_A[m][n].c = -1;  // Đặt nước đi của đối thủ

	// 1. Kiểm tra nếu Bot có thể tạo chuỗi 4 quân liên tiếp
	bool canWin = false;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c == 1) {  // Nếu ô này là quân của Bot
				for (auto dir : directions) {
					int count = countInLine(i, j, dir[0], dir[1], 1);  // Đếm số quân liên tiếp của Bot

					// Nếu Bot có đủ 3 quân liên tiếp
					if (count == 3) {
						int emptyFrontX = i + dir[0] * count;
						int emptyFrontY = j + dir[1] * count;
						int emptyBackX = i - dir[0] * count;
						int emptyBackY = j - dir[1] * count;

						// Kiểm tra nếu đầu trống và có thể đánh vào
						if (emptyFrontX >= 0 && emptyFrontX < BOARD_SIZE && emptyFrontY >= 0 && emptyFrontY < BOARD_SIZE && _A[emptyFrontX][emptyFrontY].c == 0) {
							pX = emptyFrontX;
							pY = emptyFrontY;
							canWin = true;
							break;
						}
						if (emptyBackX >= 0 && emptyBackX < BOARD_SIZE && emptyBackY >= 0 && emptyBackY < BOARD_SIZE && _A[emptyBackX][emptyBackY].c == 0) {
							pX = emptyBackX;
							pY = emptyBackY;
							canWin = true;
							break;
						}
					}
				}
			}
			if (canWin) break;
		}
		if (canWin) break;
	}

	if (!canWin) {
		// 2. Kiểm tra và chặn đối thủ nếu không có nước đi tạo chuỗi 4
		if (blockOpponent(pX, pY)) {
			_A[pX][pY].c = 1;  // Bot đánh vào ô đó
			return;
		}
	}

	// 3. Nếu không thể chiến thắng, dùng Minimax để tìm nước đi tốt nhất
	int bestScore = -10000;
	pX = -1;
	pY = -1;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c == 0) {  // Nếu ô này trống
				_A[i][j].c = 1;  // Đặt quân của Bot
				int score = minimax(0, -10000, 10000, false);
				_A[i][j].c = 0;  // Xóa quân của Bot
				if (score > bestScore) {
					bestScore = score;
					pX = i;
					pY = j;
				}
			}
		}
	}

	_A[pX][pY].c = 1;  // Đặt quân của Bot
}


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