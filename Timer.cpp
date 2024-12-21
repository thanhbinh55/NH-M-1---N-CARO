#include "Timer.h"
#include "Game.h"
#include "LanguageText.h"

//#include <mutex>

// Biến toàn cục (dùng chung)
std::atomic<bool> keeprunning(true);// Điều khiển vòng lặp đồng hồ
std::atomic<bool> isTurnSkipped(false); // Đánh dấu chuyển lượt khi hết thời gian
int turnTimer = MAXTIMETURN;// Thời gian cho mỗi lượt chơi
int gameTimer = MAXTIMEGAME;// Thời gian cho toàn ván đấu
std::mutex timerMutex;// Bảo vệ các biến thời gian
std::mutex screenMutex;
std::thread timerThread;


// Hàm đếm ngược thời gian
void CountdownTimer() {
    while (keeprunning) {
        // Lưu vị trí hiện tại của con trỏ trên màn hình
        int currentX = _X;
        int currentY = _Y;

        // Cập nhật thời gian
        {
            timerMutex.lock();
            if (gameTimer > 0) gameTimer--;
            if (turnTimer > 0) turnTimer--;
            timerMutex.unlock();
        }   

        {
            screenMutex.lock();
            GotoXY(97, 4); 
            SetColor(0, 15); // Đặt màu sắc cho văn bản
            std::cout << text.gametime; SetColor(4, 14);cout << gameTimer << " s" ; SetColor(0, 15); cout << "  "<< text.turntime; SetColor(4, 14); cout << turnTimer << "s";
            screenMutex.unlock();
        }


        // Khôi phục con trỏ về vị trí ban đầu
        GotoXY(currentX, currentY);

        // Xử lý khi hết thời gian lượt
        if (turnTimer == 0) {
            isTurnSkipped = true;  // Đánh dấu chuyển lượt
            turnTimer = 5;         // Reset thời gian cho lượt tiếp theo
        }

        // Dừng timer khi hết thời gian game
        if (gameTimer == 0) {
            keeprunning = false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Tạm dừng 1 giây
    }
}

// Bắt đầu timer
void StartTimer(int gameTime, int turnTime) {
    keeprunning = true;
    gameTimer = gameTime;
    turnTimer = turnTime;
    isTurnSkipped = false;
    timerThread = std::thread(CountdownTimer); // Bắt đầu luồng
}

// Dừng timer
void StopTimer() {
    keeprunning = false;
    if (timerThread.joinable()) {
        timerThread.join(); // Kết thúc luồng
    }
}
